/*
 * HelperFunctions.cpp
 *
 *  Created on: May 23, 2013
 *      Author: sathya
 */

#include "HelperFunctions.h"
#include "GD.h"

HelperFunctions::~HelperFunctions() {

}

int32_t HelperFunctions::getRandomNumber(int32_t min, int32_t max)
{
	try
	{
		std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int32_t> distribution(min, max);
		return distribution(generator);
	}
	catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
    return 0;
}

void HelperFunctions::memcpyBigEndian(char* to, char* from, const uint32_t& length)
{
	try
	{
		if(GD::bigEndian) memcpy(to, from, length);
		else
		{
			uint32_t last = length - 1;
			for(uint32_t i = 0; i < length; i++)
			{
				to[i] = from[last - i];
			}
		}
	}
	catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

void HelperFunctions::memcpyBigEndian(uint8_t* to, uint8_t* from, const uint32_t& length)
{
	try
	{
		memcpyBigEndian((char*)to, (char*)from, length);
	}
	catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

void HelperFunctions::memcpyBigEndian(int32_t& to, std::vector<uint8_t>& from)
{
	try
	{
		to = 0; //Necessary if length is < 4
		if(from.empty()) return;
		uint32_t length = from.size();
		if(length > 4) length = 4;
		if(GD::bigEndian) memcpyBigEndian(((uint8_t*)&to) + (4 - length), &from.at(0), length);
		else memcpyBigEndian(((uint8_t*)&to), &from.at(0), length);
	}
	catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

void HelperFunctions::memcpyBigEndian(std::vector<uint8_t>& to, int32_t& from)
{
	try
	{
		if(!to.empty()) to.clear();
		int32_t length = 4;
		if(from < 0) length = 4;
		else if(from < 256) length = 1;
		else if(from < 65536) length = 2;
		else if(from < 16777216) length = 3;
		to.resize(length, 0);
		if(GD::bigEndian) memcpyBigEndian(&to.at(0), (uint8_t*)&from + (4 - length), length);
		else memcpyBigEndian(&to.at(0), (uint8_t*)&from, length);
	}
	catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

std::pair<std::string, std::string> HelperFunctions::split(std::string string, char delimiter)
{
	try
	{

		int32_t pos = string.find_last_of(delimiter);
		if(pos == -1) return std::pair<std::string, std::string>(string, "");
		if((unsigned)pos + 1 >= string.size()) return std::pair<std::string, std::string>(string.substr(0, pos), "");
		return std::pair<std::string, std::string>(string.substr(0, pos), string.substr(pos + 1));
	}
    catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
    return std::pair<std::string, std::string>();
}

void HelperFunctions::printBinary(std::shared_ptr<std::vector<char>> data)
{
	try
	{
		if(!data) return;
		std::ostringstream stringstream;
		stringstream << std::hex << std::setfill('0') << std::uppercase;
		for(std::vector<char>::iterator i = data->begin(); i != data->end(); ++i)
		{
			stringstream << std::setw(2) << (int32_t)((uint8_t)(*i));
		}
		stringstream << std::dec;
		std::cout << stringstream.str() << std::endl;
	}
	catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

std::string HelperFunctions::getHexString(const std::vector<uint8_t>& data)
{
	try
	{
		std::ostringstream stringstream;
		stringstream << std::hex << std::setfill('0') << std::uppercase;
		for(std::vector<uint8_t>::const_iterator i = data.begin(); i != data.end(); ++i)
		{
			stringstream << std::setw(2) << (int32_t)(*i);
		}
		stringstream << std::dec;
		return stringstream.str();
	}
	catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
    return "";
}

std::string HelperFunctions::getHexString(int32_t number)
{
	std::ostringstream stringstream;
	stringstream << std::hex << std::uppercase << number << std::dec;
	return stringstream.str();
}

void HelperFunctions::copyFile(std::string source, std::string dest)
{
	try
	{
		int in_fd = open(source.c_str(), O_RDONLY);
		if(in_fd == -1)
		{
			printError("Error copying file " + source + ": " + strerror(errno));
			return;
		}
		int out_fd = open(dest.c_str(), O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP);
		if(out_fd == -1)
		{
			printError("Error copying file " + source + ": " + strerror(errno));
			return;
		}
		char buf[8192];

		while (1) {
			ssize_t result = read(in_fd, &buf[0], sizeof(buf));
			if (!result) break;
			if(result == -1)
			{
				printError("Error reading file " + source + ": " + strerror(errno));
				return;
			}
			if(write(out_fd, &buf[0], result) != result)
			{
				printError("Error writing file " + dest + ": " + strerror(errno));
				return;
			}
		}
	}
	catch(const std::exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	HelperFunctions::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

void HelperFunctions::printEx(std::string file, uint32_t line, std::string function, std::string what)
{
	if(!what.empty()) std::cerr << getTimeString() << " Error in file " << file << " line " << line << " in function " << function <<": " << what << std::endl;
	else std::cerr << getTimeString() << " Unknown error in file " << file << " line " << line << " in function " << function << "." << std::endl;
}

void HelperFunctions::printCritical(std::string errorString)
{
	if(GD::debugLevel < 1) return;
	std::cerr << getTimeString() << " " << errorString << std::endl;
}

void HelperFunctions::printError(std::string errorString)
{
	if(GD::debugLevel < 2) return;
	std::cerr << getTimeString() << " " << errorString << std::endl;
}

void HelperFunctions::printWarning(std::string errorString)
{
	if(GD::debugLevel < 3) return;
	std::cerr << getTimeString() << " " << errorString << std::endl;
}

void HelperFunctions::printInfo(std::string message)
{
	if(GD::debugLevel < 4) return;
	std::cout << getTimeString() << " " << message << std::endl;
}

void HelperFunctions::printDebug(std::string message, int32_t minDebugLevel)
{
	if(GD::debugLevel < minDebugLevel) return;
	std::cout << getTimeString() << " " << message << std::endl;
}

void HelperFunctions::printMessage(std::string message, int32_t minDebugLevel)
{
	if(GD::debugLevel < minDebugLevel) return;
	std::cout << getTimeString() << " " << message << std::endl;
}
