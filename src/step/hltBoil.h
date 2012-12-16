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

#ifndef HLTBOIL_H_
#define HLTBOIL_H_

#include "../defines.h"
#include "Step.h"

class hltBoil: public Step {
public:
	hltBoil();
	virtual ~hltBoil();
};

#endif /* HLTBOIL_H_ */
