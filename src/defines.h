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

#ifndef DEFINES_H_
#define DEFINES_H_

// Define an id for each of the steps
#define HLT_AUTO_FILL 0
#define HLT_BOIL 	  1
#define HLT_HOLD      2

#define MASH_IN 		   10
#define MASH_BETA_GLUCAN   11
#define MASH_PROTEIN 	   12
#define MASH_BETA_AMYLASE  13
#define MASH_ALPHA_AMYLASE 14
#define MASH_REST 		   15
#define MASH_VORLAUF 	   16
#define MASH_OUT		   17

#define MASH_BATCH_DRAIN 	20
#define MASH_BATCH_SPARGE 	21
#define MASH_FLY_SPARGE 	22

#define BOIL_STEP 		30
#define BOIL_ADDITION 	31
#define BOIL_FLAMEOUT 	39

#define WHIRLPOOL_START 40
#define WHIRLPOOL_RUN 	41
#define WHIRLPOOL_REST 	42
#define WHIRLPOOL_END 	49

#define CHILLER_START 	51
#define CHILLER_RUN 	52
#define CHILLER_END 	59

// Define some vessels here
#define VESSEL_NONE		0
#define VESSEL_HLT 		1
#define VESSEL_MLT 		2
#define VESSEL_KETTLE 	3

#define RELAY_BOARD_I2C_ADDR 0x20

#define BROWN_PUMP_RELAY_ADDR 	    "/sys/i2c/1234/something"
#define MARCH_PUMP_ONE_RELAY_ADDR   "/sys/i2c/2343/something"
#define MARCH_PUMP_TWO_RELAY_ADDR   "/sys/i2c/8763/something"
#define MARCH_PUMP_THREE_RELAY_ADDR "/sys/i2c/4234/something"

#define HLT_ELEMENT_RELAY_ADDR   "/sys/i2c/7642/something"
#define MLT_ELEMENT_RELAY_ADDR   "/sys/i2c/3423/something"
#define HERMS_ELEMENT_RELAY_ADDR "/sys/i2c/8733/something"

// that might be wrong. the jaycar i2c relay board may only present as a single device/path,
// we might need to send the bitwise codes to that single device to enable/disable the
// relays as required...

#endif /* DEFINES_H_ */
