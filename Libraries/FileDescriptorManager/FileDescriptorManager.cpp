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

#include "FileDescriptorManager.h"

std::shared_ptr<FileDescriptor> FileDescriptorManager::add(int32_t fileDescriptor)
{
	try
	{
		if(fileDescriptor < 0) return std::shared_ptr<FileDescriptor>(new FileDescriptor());
		_descriptorsMutex.lock();
		if(_descriptors.find(fileDescriptor) != _descriptors.end())
		{
			Output::printInfo("Old file descriptor " + std::to_string(fileDescriptor) + " was invalidated.");
			_descriptors.at(fileDescriptor)->descriptor = -1;
		}
		std::shared_ptr<FileDescriptor> descriptor(new FileDescriptor());
		descriptor->id = _currentID++;
		descriptor->descriptor = fileDescriptor;
		_descriptors[fileDescriptor] = descriptor;
		_descriptorsMutex.unlock();
		return descriptor;
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
	_descriptorsMutex.unlock();
	return std::shared_ptr<FileDescriptor>(new FileDescriptor());
}

void FileDescriptorManager::remove(std::shared_ptr<FileDescriptor> descriptor)
{
	try
	{
		if(!descriptor || descriptor->descriptor < 0) return;
		_descriptorsMutex.lock();
		if(_descriptors.find(descriptor->descriptor) != _descriptors.end() && _descriptors.at(descriptor->descriptor)->id == descriptor->id)
		{
			descriptor->descriptor = -1;
			_descriptors.erase(descriptor->descriptor);
		}
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
	_descriptorsMutex.unlock();
}

void FileDescriptorManager::close(std::shared_ptr<FileDescriptor> descriptor)
{
	try
	{
		if(!descriptor || descriptor->descriptor < 0) return;
		_descriptorsMutex.lock();
		if(_descriptors.find(descriptor->descriptor) != _descriptors.end() && _descriptors.at(descriptor->descriptor)->id == descriptor->id)
		{
			_descriptors.erase(descriptor->descriptor);
			::close(descriptor->descriptor);
			descriptor->descriptor = -1;
		}
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
	_descriptorsMutex.unlock();
}

void FileDescriptorManager::shutdown(std::shared_ptr<FileDescriptor> descriptor)
{
	try
	{
		if(!descriptor || descriptor->descriptor < 0) return;
		_descriptorsMutex.lock();
		if(_descriptors.find(descriptor->descriptor) != _descriptors.end() && _descriptors.at(descriptor->descriptor)->id == descriptor->id)
		{
			_descriptors.erase(descriptor->descriptor);
			::shutdown(descriptor->descriptor, 0);
			::close(descriptor->descriptor);
			descriptor->descriptor = -1;
		}
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
	_descriptorsMutex.unlock();
}

std::shared_ptr<FileDescriptor> FileDescriptorManager::get(int32_t fileDescriptor)
{
	try
	{
		if(fileDescriptor < 0) return std::shared_ptr<FileDescriptor>();
		std::shared_ptr<FileDescriptor> descriptor;
		_descriptorsMutex.lock();
		if(_descriptors.find(fileDescriptor) != _descriptors.end()) descriptor = _descriptors.at(fileDescriptor);
		_descriptorsMutex.unlock();
		return descriptor;
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
	_descriptorsMutex.unlock();
	return std::shared_ptr<FileDescriptor>();
}

bool FileDescriptorManager::isValid(int32_t fileDescriptor, int32_t id)
{
	try
	{
		if(fileDescriptor < 0) return false;
		bool valid = false;
		_descriptorsMutex.lock();
		if(_descriptors.find(fileDescriptor) != _descriptors.end() && _descriptors.at(fileDescriptor)->id == id) valid = true;
		_descriptorsMutex.unlock();
		return valid;
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
	_descriptorsMutex.unlock();
	return false;
}

bool FileDescriptorManager::isValid(std::shared_ptr<FileDescriptor> descriptor)
{
	try
	{
		if(!descriptor || descriptor->descriptor < 0) return false;
		bool valid = false;
		_descriptorsMutex.lock();
		if(_descriptors.find(descriptor->descriptor) != _descriptors.end() && _descriptors.at(descriptor->descriptor)->id == descriptor->id) valid = true;
		_descriptorsMutex.unlock();
		return valid;
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
	_descriptorsMutex.unlock();
	return false;
}
