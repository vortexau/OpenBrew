/*
 * This file is part of OpenBrew.
 *
 * OpenBrew is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenBrew is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenBrew.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (c) 2012 James McLean <james.mclean@gmail.com>
 *
 */

#ifndef SENSOR_H_
#define SENSOR_H_

using namespace std;

#include <iostream>
#include <string>

#include "../defines.h"

#include "Sensor.h"

class Sensor {

	string sysfsPath;
	string sysfsTemperatureFile;
	string sensorDescription;

public:
	Sensor();
	virtual ~Sensor();

	const string& getSensorDescription() const {
		return sensorDescription;
	}

	void setSensorDescription(const string& sensorDescription) {
		this->sensorDescription = sensorDescription;
	}

	const string& getSysfsPath() const {
		return sysfsPath;
	}

	void setSysfsPath(const string& sysfsPath) {
		this->sysfsPath = sysfsPath;
	}

	const string& getSysfsTemperatureFile() const {
		return sysfsTemperatureFile;
	}

	void setSysfsTemperatureFile(const string& sysfsTemperatureFile) {
		this->sysfsTemperatureFile = sysfsTemperatureFile;
	}
};

#endif /* SENSOR_H_ */
