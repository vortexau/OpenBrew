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

#ifndef BATCH_H_
#define BATCH_H_

#include <iostream>
#include <string>

#include "../defines.h"

#include "../vessel/Vessel.h"
#include "../vessel/Hlt.h"
#include "../vessel/Mlt.h"
#include "../vessel/Kettle.h"

using namespace std;

class Batch {
protected:
	Vessel hlt;
	Vessel mlt;
	Vessel kettle;

	const char *recipeFullPath;

public:
	Batch();
	Batch(char *recipePath);
	virtual ~Batch();
	Vessel getVessel(int vessel);
	void addStep(Step step);
	void run();
	void runSteps(Vessel vessel);
	int parseRecipe();

	const char* getRecipeFullPath() const {
		return recipeFullPath;
	}

	void setRecipeFullPath(const char* recipeFullPath) {
		this->recipeFullPath = recipeFullPath;
	}
};

#endif /* BATCH_H_ */
