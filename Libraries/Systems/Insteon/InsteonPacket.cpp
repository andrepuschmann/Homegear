/* Copyright 2013-2014 Sathya Laufer
 *
 * Homegear is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Homegear is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Homegear.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */

#include "InsteonPacket.h"

namespace Insteon
{
InsteonPacket::InsteonPacket()
{
	init();
}

InsteonPacket::InsteonPacket(std::string packet, int64_t timeReceived)
{
	init();
	_timeReceived = timeReceived;
	import(packet);
}

InsteonPacket::InsteonPacket(std::vector<char>& packet, uint32_t packetSize, int64_t timeReceived)
{
	init();
	_timeReceived = timeReceived;
	import(packet, packetSize);
}

InsteonPacket::~InsteonPacket()
{
}

void InsteonPacket::init()
{
}

void InsteonPacket::reset()
{
	_packet.clear();
	_senderAddress = 0;
	_destinationAddress = 0;
	_payload.clear();
}

void InsteonPacket::import(std::vector<char>& packet, uint32_t packetSize)
{
	try
	{
		reset();
		if(packet.empty()) return;
		_packet.insert(_packet.begin(), packet.begin(), packet.begin() + packetSize);
	}
	catch(const std::exception& ex)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

void InsteonPacket::import(std::string packetHex)
{
	try
	{
		if(packetHex.size() % 2 != 0)
		{
			Output::printWarning("Warning: Packet has invalid size.");
			return;
		}
		std::vector<char> packet(HelperFunctions::getBinary(packetHex));
		_packet = packet;
	}
	catch(const std::exception& ex)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

std::vector<char> InsteonPacket::byteArray()
{
	try
	{
		return _packet;
	}
	catch(const std::exception& ex)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
    return std::vector<char>();
}

std::string InsteonPacket::hexString()
{
	try
	{
		return HelperFunctions::getHexString(byteArray());
	}
	catch(const std::exception& ex)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(Exception& ex)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__, ex.what());
    }
    catch(...)
    {
    	Output::printEx(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
    return "";
}

} /* namespace HMWired */
