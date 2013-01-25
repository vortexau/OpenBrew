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

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>

#include "../defines.h"
#include "runBatch.h"
#include "../vessel/Vessel.h"
#include "../vessel/Hlt.h"
#include "../vessel/Mlt.h"
#include "../vessel/Kettle.h"
#include "../batch/Batch.h"

using namespace std;

runBatch::runBatch() {
    // TODO Auto-generated constructor stub

}

void runBatch::run(Batch batch) {

    pid_t pid;
    int rv;

    // fork each of these processes so they run concurrently.

//  for(int i = 1; i < (VESSEL_KETTLE + 1); i++) {
//
//      switch(pid = fork()) {
//      case -1:
//          perror("fork");  /* something went wrong */
//          exit(1);         /* parent exits */
//
//          break;
//      case 0:
//          // this is the child.
//          cout << "This is the Child, PID is: " << getpid() << endl;
//          this->runSteps(batch.getVessel(i));
//          break;
//      default:
//          // this is the parent
//          cout << "This is the Parent, PID is: " << getpid() << endl;
//          break;
//      }
//
//  }

//  this->runSteps(batch.getVessel(VESSEL_HLT));
//  this->runSteps(batch.getVessel(VESSEL_MLT));
//  this->runSteps(batch.getVessel(VESSEL_KETTLE));
}

void runBatch::runSteps(Vessel vessel) {

    int numSteps = vessel.getNumSteps();

    string vessel_name = vessel.getVesselName();

    syslog(LOG_INFO, "%s: Vessel Thread starting up. ", vessel_name.c_str());

    cout << "Processing ";
    cout << vessel.getVesselName();
    cout << " Steps. " << numSteps << " steps to perform. " << endl;

    if(numSteps == 0) {
        cout << "No steps configured! Adding default step." << endl;

        if(vessel.getVesselType() == VESSEL_HLT) {

        }

    }

    // Get all the steps and then process them once by one.
    vector<Step> steps = vessel.getAllSteps();

    for(vector<Step>::size_type i = 0; i != steps.size(); i++) {

        Step thisStep = steps[i];

        string step_name = thisStep.getStepName();


        string vessel_name_v    = "%s: Vessel: %s";
        syslog(LOG_INFO, vessel_name.c_str(), vessel_name.c_str(), vessel_name.c_str());

        string vessel_step      = "%s: Running step name '%s'";
        syslog(LOG_INFO, vessel_step.c_str(), vessel_name.c_str(), step_name.c_str());

        string vessel_step_time = "%s: Step will run for %d minutes";
        syslog(LOG_INFO, vessel_step_time.c_str(), vessel_name.c_str(), thisStep.getStepLength());


        thisStep.stepActions();

        // get the time for this step, in minutes.
        // convert the step time to seconds
        int stepTimeSeconds = thisStep.getStepLength() * 60;


        if(stepTimeSeconds == 0) {
        	syslog(LOG_INFO, "%s: No time specified. Temp step.", vessel_name.c_str());
        	// No specified time. So.. it's probably a 'temp' target
        	// like for the HLT. So, we'll need to wait until it's at temp.

        	// For now, eh. We'll just wait 10 mins.
        	sleep(10 * 60);

        } else {

        	syslog(LOG_INFO, "%s: Starting step timer.", vessel_name.c_str());

			while(stepTimeSeconds > 0) {

				sleep(1);
				stepTimeSeconds--;
			}

			syslog(LOG_INFO, "%s: Step timer complete.", vessel_name.c_str());

        }

        string vessel_step_ending = "%s: Step: '%s' step is complete. Proceeding to next step";
        syslog(LOG_INFO, vessel_step_ending.c_str(), vessel_name.c_str(), step_name.c_str());

        cout << vessel_step_ending << endl;
        cout << endl;
        cout << "------------------" << endl;
        cout << endl;


    }

    syslog(LOG_INFO, "%s Thread ending.", vessel_name.c_str());
}

runBatch::~runBatch() {
    // TODO Auto-generated destructor stub
}

