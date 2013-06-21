#ifndef HOMEMATICDEVICES_H_
#define HOMEMATICDEVICES_H_

class HomeMaticDevice;

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Devices/HomeMaticCentral.h"

class HomeMaticDevices {
public:
	HomeMaticDevices();
	virtual ~HomeMaticDevices();
	void add(HomeMaticDevice* device);
	bool remove(int32_t address);
	std::shared_ptr<HomeMaticDevice> get(int32_t address);
	std::shared_ptr<HomeMaticDevice> get(std::string serialNumber);
	std::shared_ptr<HomeMaticCentral> getCentral() { return _central; }
	std::vector<std::shared_ptr<HomeMaticDevice>>* getDevices() { return &_devices; }
	void load();
	void save();
	void stopDutyCycles();
	void stopDutyCycle(std::shared_ptr<HomeMaticDevice> device);
private:
	std::vector<std::shared_ptr<HomeMaticDevice>> _devices;
	std::shared_ptr<HomeMaticCentral> _central;
};

#endif /* HOMEMATICDEVICES_H_ */