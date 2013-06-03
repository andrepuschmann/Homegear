#include "BidCoSPacket.h"
#include "GD.h"

//Properties
uint8_t BidCoSPacket::length()
{
    return _length;
}

uint8_t BidCoSPacket::messageCounter()
{
    return _messageCounter;
}

uint8_t BidCoSPacket::controlByte()
{
    return _controlByte;
}

uint8_t BidCoSPacket::messageType()
{
    return _messageType;
}

int32_t BidCoSPacket::messageSubtype()
{
	try
	{
		switch(_messageType)
		{
			case 0x01:
				return _payload.at(1);
			case 0x11:
				return _payload.at(0);
		}
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
	return -1;
}

int32_t BidCoSPacket::senderAddress()
{
    return _senderAddress;
}

int32_t BidCoSPacket::destinationAddress()
{
    return _destinationAddress;
}

int32_t BidCoSPacket::channel()
{
    switch(_messageType)
    {
        case 0x01:
            return _payload.at(0);
        default:
            return -1;
    }
}

vector<uint8_t>* BidCoSPacket::payload()
{
    return &_payload;
}

std::string BidCoSPacket::hexString()
{
	try
	{
		std::ostringstream stringStream;
		stringStream << std::hex << std::uppercase << std::setfill('0') << std::setw(2);
		stringStream << std::setw(2) << (int32_t)_length;
		stringStream << std::setw(2) << (int32_t)_messageCounter;
		stringStream << std::setw(2) << (int32_t)_controlByte;
		stringStream << std::setw(2) << (int32_t)_messageType;
		stringStream << std::setw(6) << _senderAddress;
		stringStream << std::setw(6) << _destinationAddress;
		std::for_each(_payload.begin(), _payload.end(), [&](uint8_t element) {stringStream << std::setw(2) << (int32_t)element;});
		return stringStream.str();
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
	return "";
}
//End of properties

BidCoSPacket::BidCoSPacket()
{
}

BidCoSPacket::BidCoSPacket(std::string packet)
{
    import(packet);
}

BidCoSPacket::BidCoSPacket(uint8_t messageCounter, uint8_t controlByte, uint8_t messageType, int32_t senderAddress, int32_t destinationAddress, vector<uint8_t> payload)
     : _messageCounter(messageCounter), _controlByte(controlByte), _messageType(messageType), _senderAddress(senderAddress), _destinationAddress(destinationAddress), _payload(payload)
{
    _length = 9 + _payload.size();
}

BidCoSPacket::~BidCoSPacket()
{
}

//Packet looks like A...DATA...\r\n
void BidCoSPacket::import(std::string packet, bool removeFirstCharacter)
{
	try
	{
		uint32_t startIndex = removeFirstCharacter ? 1 : 0;
		_length = getByte(packet.substr(startIndex, 2));
		_messageCounter = getByte(packet.substr(startIndex + 2, 2));
		_controlByte = getByte(packet.substr(startIndex + 4, 2));
		_messageType = getByte(packet.substr(startIndex + 6, 2));
		_senderAddress = getInt(packet.substr(startIndex + 8, 6));
		_destinationAddress = getInt(packet.substr(startIndex + 14, 6));

		uint32_t tailLength = 0;
		if(packet.back() == '\n') tailLength = 2;
		_payload.clear();
		for(int32_t i = startIndex + 20; i < (signed)packet.length() - tailLength; i+=2)
		{
			_payload.push_back(getByte(packet.substr(i, 2)));
		}
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<" (Packet: " << packet << "): " << ex.what() << '\n';
	}
}

uint8_t BidCoSPacket::getByte(std::string hexString)
{
	try
	{
		/*int32_t buffer;
		std::stringstream packetStream;
		packetStream << std::hex << hexString;
		packetStream >> buffer;*/
		return (uint8_t)std::stoi(hexString, 0, 16);
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
	return 0;
}

int32_t BidCoSPacket::getInt(std::string hexString)
{
	try
	{
		/*int32_t buffer;
		std::stringstream packetStream;
		packetStream << std::hex << hexString;
		packetStream >> buffer;*/
		return std::stoi(hexString, 0, 16);
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error in file " << __FILE__ " line " << __LINE__ << " in function " << __PRETTY_FUNCTION__ <<": " << ex.what() << '\n';
	}
	return 0;
}

int64_t BidCoSPacket::getPosition(double index, double size, bool isSigned)
{
	if(index < 9)
	{
		if(GD::debugLevel >= 2) cout << "Error: Packet index < 9 requested." << endl;
		return 0;
	}
	index -= 9;
	double byteIndex = std::floor(index);
	int64_t result = 0;
	if(byteIndex != index)
	{
		if(size > 1)
		{
			if(GD::debugLevel >= 2) cout << "Error: Partial byte index > 1 requested.";
			return result;
		}
		if(isSigned)
		{
			if(GD::debugLevel >= 2) cout << "Error: Signed partial byte index requested.";
			return result;
		}
		result = (_payload.at(byteIndex) >> (((uint32_t)(index * 10)) % 10)) & _bitmask[(uint32_t)(size * 10)];
	}
	else
	{
		uint32_t bytes = (uint32_t)std::ceil(size);
		result = (_payload.at(index) & _bitmask[((uint32_t)(size * 10)) % 10]) << ((bytes - 1) * 8);
		for(uint32_t i = 1; i < bytes; i++)
		{
			result += _payload.at(index + i) << ((bytes - i - 1) * 8);
		}
		if(isSigned)
		{
			uint32_t signPosition = ((uint32_t)(size * 10)) % 10;
			if(_payload.at(index) & (1 << signPosition)) //has sign?
			{
				uint32_t bits = (uint32_t)std::floor(size) * 8 + signPosition;
				result = (1 << bits) + result;
			}
		}
	}
	return result;
}
