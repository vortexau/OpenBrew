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

#define RELAY_BOARD_1_ADDR 0x20
#define SEVENSEG_HLT_DISP  0x70
#define SEVENSEG_MLT_DISP  0x71

#define RELAY_ON    1
#define RELAY_OFF   0

#define RELAY_BOARD_1_8     0
#define RELAY_BOARD_1_7     1
#define RELAY_BOARD_1_6     2
#define RELAY_BOARD_1_5     3
#define RELAY_BOARD_1_4     4
#define RELAY_BOARD_1_3     5
#define RELAY_BOARD_1_2     6
#define RELAY_BOARD_1_1     7

#endif /* DEFINES_H_ */
