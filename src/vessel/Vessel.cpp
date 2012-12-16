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

#include "../defines.h"
#include "Vessel.h"

Vessel::Vessel() {
	setVesselType(VESSEL_NONE);
}

Vessel::Vessel(int vesselType) {
	setVesselType(vesselType);
}

void Vessel::addStep(Step step) {
	Steps.push_back(step);
}

int Vessel::getNumSteps() {
	return Steps.size();
}

vector<Step> Vessel::getAllSteps() {
	return Steps;
}

int Vessel::getVesselType() {
	return vesselType;
}

string Vessel::getVesselName() {
    if(vesselType == VESSEL_HLT) {
        return "HLT";
    }
    if(vesselType == VESSEL_MLT) {
        return "MLT";
    }
    if(vesselType == VESSEL_KETTLE) {
        return "Kettle";
    }
}

void Vessel::setVesselType(int vesselType) {
	this->vesselType = vesselType;
}

void Vessel::addPump(Pump pump) {
	Pumps.push_back(pump);
}

void Vessel::addSensor(Sensor sensor) {
	Sensors.push_back(sensor);
}

Vessel::~Vessel() {
	// TODO Auto-generated destructor stub
}

