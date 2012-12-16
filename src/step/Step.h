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

#ifndef STEP_H_
#define STEP_H_

using namespace std;

#include <iostream>
#include <string>

#include "../defines.h"

class Step {
protected:
    signed int stepVessel;
    signed int stepNumber;
    signed int stepLength;
    signed int stepType;
    signed int stepRampTime;
    signed int infusionAmount; // water to add to the mashtun.
    signed int stepActive;
    float stepTemperature;
    float stepEndTemperature;
    bool  promptForGrain;
    string stepName;
public:
	Step();
	virtual ~Step();

	void stepActions();

	signed int getStepLength() const {
		return stepLength;
	}

	void setStepLength(signed int stepLength) {
		this->stepLength = stepLength;
	}

	signed int getStepNumber() const {
		return stepNumber;
	}

	void setStepNumber(signed int stepNumber) {
		this->stepNumber = stepNumber;
	}

	signed int getStepType() const {
		return stepType;
	}

	void setStepType(signed int stepType) {
		this->stepType = stepType;
	}

	signed int getVessel() const {
		return stepVessel;
	}

	void setVessel(signed int vessel) {
		this->stepVessel = vessel;
	}

	string getStepName() const {
		return stepName;
	}

	float getStepTemperature() const {
		return stepTemperature;
	}

	void setStepTemperature(float stepTemperature) {
		this->stepTemperature = stepTemperature;
	}

	bool getPromptForGrain() const {
		return promptForGrain;
	}

	void setPromptForGrain(bool promptForGrain) {
		this->promptForGrain = promptForGrain;
	}

	void setStepName(const string& stepName) {
		this->stepName = stepName;
	}
};

#endif /* STEP_H_ */
