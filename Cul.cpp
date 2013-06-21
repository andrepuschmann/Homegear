#include "Cul.h"
#include "GD.h"

Cul::Cul()
{

}

Cul::Cul(std::string culDevice)
{
    _culDevice = culDevice;
}

void Cul::init(std::string culDevice)
{
	_culDevice = culDevice;
}

Cul::~Cul()
{
    closeDevice();
}

void Cul::addHomeMaticDevice(HomeMaticDevice* device)
{
    _homeMaticDevices.push_back(device);
}

void Cul::removeHomeMaticDevice(HomeMaticDevice* device)
{
    _homeMaticDevices.remove(device);
}

void Cul::sendPacket(std::shared_ptr<BidCoSPacket> packet)
{
	try
	{
		if(packet == nullptr)
		{
			if(GD::debugLevel >= 3) std::cout << "Warning: Packet was nullptr." << std::endl;
			return;
		}
		bool deviceWasClosed = false;
		if(_fileDescriptor == -1)
		{
			deviceWasClosed = true;
			openDevice();
		}
		if(_fileDescriptor == -1) throw(Exception("Couldn't write to CUL device, because the file descriptor is not valid: " + _culDevice));

		writeToDevice("As" + packet->hexString() + "\r\n", true);

		if(deviceWasClosed) closeDevice();
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
}

void Cul::openDevice()
{
	try
	{
		if(_fileDescriptor != -1) closeDevice();

		_lockfile = "/var/lock/" + _culDevice.substr(_culDevice.find_last_of('/')) + ".lock";
		int lockfileDescriptor = open(_lockfile.c_str(), O_WRONLY | O_EXCL | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if(lockfileDescriptor == -1)
		{
			if(errno != EEXIST) throw(Exception("Couldn't create lockfile " + _lockfile));

			int processID = 0;
			std::ifstream lockfileStream(_lockfile.c_str());
			lockfileStream >> processID;
			if(kill(processID, 0) == 0) throw(Exception("CUL device is in use: " + _culDevice));
			unlink(_lockfile.c_str());
			lockfileDescriptor = open(_lockfile.c_str(), O_WRONLY | O_EXCL | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			if(lockfileDescriptor == -1) throw(Exception("Couldn't create lockfile " + _lockfile));
		}
		dprintf(lockfileDescriptor, "%10i", getpid());
		close(lockfileDescriptor);
		//std::string chmod("chmod 666 " + _lockfile);
		//system(chmod.c_str());

		_fileDescriptor = open(_culDevice.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

		if(_fileDescriptor == -1) throw(Exception("Couldn't open CUL device: " + _culDevice));

		setupDevice();
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
}

void Cul::closeDevice()
{
	try
	{
		if(_fileDescriptor == -1) return;
		close(_fileDescriptor);
		_fileDescriptor = -1;
		unlink(_lockfile.c_str());
	}
    catch(const std::exception& ex)
    {
    	std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
    }
}

void Cul::setupDevice()
{
	try
	{
		if(_fileDescriptor == -1) return;
		struct termios term;
		term.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
		term.c_iflag = IGNPAR;
		term.c_oflag = 0;
		term.c_lflag = 0;
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		cfsetispeed(&term, B9600);
		cfsetospeed(&term, B9600);
		if(tcflush(_fileDescriptor, TCIFLUSH) == -1) throw(Exception("Couldn't flush CUL device " + _culDevice));
		if(tcsetattr(_fileDescriptor, TCSANOW, &term) == -1) throw(Exception("Couldn't set CUL device settings: " + _culDevice));

		int flags = fcntl(_fileDescriptor, F_GETFL);
		if(!(flags & O_NONBLOCK))
		{
			if(fcntl(_fileDescriptor, F_SETFL, flags | O_NONBLOCK) == -1)
			{
				throw(Exception("Couldn't set CUL device to non blocking mode: " + _culDevice));
			}
		}
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
}

std::string Cul::readFromDevice()
{
	try
	{
		if(_fileDescriptor == -1) throw(Exception("Couldn't read from CUL device, because the file descriptor is not valid: " + _culDevice));
		std::string packet;
		int32_t i;
		char localBuffer[1];
		struct timeval timeout;
		timeout.tv_sec = 1200;
		timeout.tv_usec = 0;
		fd_set readFileDescriptor;
		FD_ZERO(&readFileDescriptor);
		FD_SET(_fileDescriptor, &readFileDescriptor);

		while(localBuffer[0] != '\n')
		{
			i = select(_fileDescriptor + 1, &readFileDescriptor, NULL, NULL, &timeout);
			switch(i)
			{
				case 0:
					if(GD::debugLevel >= 3) std::cout << "Warning: Reading from CUL device timed out: " + _culDevice << std::endl;
					break;
				case -1:
					throw(Exception("Error reading from CUL device: " + _culDevice));
					break;
				case 1:
					break;
				default:
					throw(Exception("Error reading from CUL device: " + _culDevice));

			}

			i = read(_fileDescriptor, localBuffer, 1);
			if(i == -1)
			{
				if(errno == EAGAIN) continue;
				throw(Exception("Error reading from CUL device: " + _culDevice));
			}
			packet.push_back(localBuffer[0]);
		}
		return packet;
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
	return "";
}

void Cul::writeToDevice(std::string data, bool printSending)
{
    try
    {
        if(_fileDescriptor == -1) throw(Exception("Couldn't write to CUL device, because the file descriptor is not valid: " + _culDevice));
        int32_t bytesWritten = 0;
        int32_t i;
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 200000;
        fd_set writeFileDescriptor;
        if(GD::debugLevel > 3 && printSending)
        {
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() << " Sending: " << data.substr(2, data.size() - 4) << std::endl;
        }
        _sendMutex.lock();
        FD_ZERO(&writeFileDescriptor);
        FD_SET(_fileDescriptor, &writeFileDescriptor);
        while(bytesWritten < (signed)data.length())
        {
            i = select(_fileDescriptor + 1, NULL, &writeFileDescriptor, NULL, &timeout);
            switch(i)
            {
                case 0:
                    if(GD::debugLevel >= 3) std::cout << "Warning: Writing to CUL device timed out: " + _culDevice << std::endl;
                    break;
                case -1:
                    throw(Exception("Error writing to CUL device (1): " + _culDevice));
                    break;
                case 1:
                    break;
                default:
                    throw(Exception("Error writing to CUL device (2): " + _culDevice));

            }
            i = write(_fileDescriptor, data.c_str() + bytesWritten, data.length() - bytesWritten);
            if(i == -1)
            {
                if(errno == EAGAIN) continue;
                throw(Exception("Error writing to CUL device (3, " + std::to_string(errno) + "): " + _culDevice));
            }
            bytesWritten += i;
        }

        _sendMutex.unlock();
    }
    catch(const std::exception& ex)
    {
    	_sendMutex.unlock();
    	std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << std::endl;
    }
    catch(const Exception& ex)
    {
    	_sendMutex.unlock();
    	std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << std::endl;
    }
    catch(...)
    {
    	_sendMutex.unlock();
    	std::cerr << "Unknown error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ << "." << std::endl;
    }
}

void Cul::startListening()
{
	try
	{
		stopListening();
		openDevice();
		if(_fileDescriptor == -1) throw(Exception("Couldn't listen to CUL device, because the file descriptor is not valid: " + _culDevice));
		writeToDevice("Ar\r\n", false);
		_listenThread = std::thread(&Cul::listen, this);
		_listenThread.detach();
	}
    catch(const std::exception& ex)
    {
    	std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
    }
}

void Cul::stopListening()
{
	try
	{
		if(_listenThread.joinable())
		{
			_stopCallbackThread = true;
			_listenThread.join();
		}
		_stopCallbackThread = false;
		if(_fileDescriptor != -1)
		{
			//Other X commands than 00 seem to slow down data processing
			writeToDevice("X00\r\n", false);
			writeToDevice("Ar\r\n", false);
			closeDevice();
		}
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
}

void Cul::callCallback(std::shared_ptr<BidCoSPacket> packet)
{
	try
	{
		for(std::list<HomeMaticDevice*>::const_iterator i = _homeMaticDevices.begin(); i != _homeMaticDevices.end(); ++i)
		{
			//Don't filter destination addresses here! Some devices need to receive packets not directed to them.
			std::thread received(&HomeMaticDevice::packetReceived, (*i), packet);
			received.detach();
		}
	}
    catch(const std::exception& ex)
    {
    	std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
    }
}

void Cul::listen()
{
    try
    {
        while(!_stopCallbackThread)
        {
        	std::string packetHex = readFromDevice();
        	if(packetHex.size() > 21) //21 is minimal packet length (=10 Byte + CUL "A")
        	{
				std::shared_ptr<BidCoSPacket> packet(new BidCoSPacket());
				packet->import(packetHex);
				std::thread t(&Cul::callCallback, this, packet);
				t.detach();
        	}
        }
    }
    catch(const std::exception& ex)
    {
    	std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
    }
}