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

#ifndef VESSEL_H_
#define VESSEL_H_

#include <vector>
#include "../defines.h"

#include "../pump/Pump.h"
#include "../pump/BrownPump.h"
#include "../pump/MarchPump.h"

#include "../sensor/Sensor.h"

#include "../step/Step.h"
#include "../step/hltAutoFill.h"
#include "../step/hltBoil.h"

using namespace std;
using std::vector;

class Vessel {
protected:
	int vesselType;
public:

	vector<Step> Steps;
	vector<Pump> Pumps;
	vector<Sensor> Sensors;

	Vessel();
	Vessel(int vesselType);
	virtual ~Vessel();
	void addStep(Step thisStep);
	int getVesselType();
	string getVesselName();
	void setVesselType(int vesselType);
	int getNumSteps();
	vector<Step> getAllSteps();

	void addSensor(Sensor sensor);
	void addPump(Pump pump);

//	vector<Sensor> getSensors();
//	void setSensors();
//
//	vector<Pump> getPumps();
//	void setPumps();
};

#endif /* VESSEL_H_ */
