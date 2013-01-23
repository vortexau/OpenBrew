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
#include <string>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../defines.h"

#include "../../lib/pugixml-1.2/src/pugixml.hpp"

#include "Batch.h"
#include "../runBatch/runBatch.h"
#include "../step/Step.h"

using namespace std;

Batch::Batch(char *recipePath) {

    // set the recipe path
    setRecipeFullPath(recipePath);

    cout << "Parsing recipe: " << getRecipeFullPath() << endl;

    // Parse the recipe and generate vessels and steps for each vessel
    parseRecipe();

    // Setup the objects for each vessel.
    Hlt hlt;
    Mlt mlt;
    Kettle kettle;
}

Batch::Batch() {

    // Setup the objects for each vessel.
    Hlt hlt;
    Mlt mlt;
    Kettle kettle;
}

int Batch::parseRecipe() {

    int i;
    string recipeCorrect;
    string yesLower;
    string yesUpper;
    string stepName;
    double boilLength;
    double stepTemp;
    double stepLength;
    double stepNumber;

    yesLower = 'y';
    yesUpper = 'Y';

    try {

        pugi::xml_document doc;
        if (!doc.load_file(getRecipeFullPath())) return -1;

        pugi::xml_node recipe_name = doc.child("RECIPES").child("RECIPE").child("NAME");

        cout << "Parsing recipe: " << recipe_name.child_value() << endl; // this returns the recipe name correctly.

        // boil length
        pugi::xml_node boil_length = doc.child("RECIPES").child("RECIPE").child("BOIL_TIME");

        boilLength = atof(boil_length.child_value());

        // get the mash steps from the recipe
        pugi::xml_node mash_steps = doc.child("RECIPES").child("RECIPE").child("MASH").child("MASH_STEPS");

        // add the mash steps to the batch
        i = 0;
        for (pugi::xml_node step = mash_steps.child("MASH_STEP"); step; step = step.next_sibling("MASH_STEP")) {

            // Get some details of this step from the recipe.
            stepName   = step.child("NAME").child_value();
            stepTemp   = atof(step.child("STEP_TEMP").child_value()); 
            stepLength = atof(step.child("STEP_TIME").child_value());
            stepNumber = 0; // get this step number from the order of the mash steps.

            cout << "Step Name: '" << stepName << "'. Temp: " << stepTemp << "c for " << stepLength << " minutes" << endl;

            // for the 'mash in' step add a step to the HLT for the mash-in temp.
            if(i == 0) { // rather than use the 'mash in' step, should we use the 'first' element as the mash-in temp? probably.
                // get the 'dough in' temp, add a step for HLT using this temp

                cout << "Dough In step found. Adding Dough-In temp as HLT step" << endl;

                int thisVessel = VESSEL_HLT;

                Step thisStep;
                thisStep.setVessel(thisVessel);
                thisStep.setStepLength(0);
                thisStep.setStepTemperature((float) stepTemp);
                thisStep.setStepName("HLT Mash In Temp");
                /*
                 * It is common to store data as text contents of some node - i.e. <node><description>This is a node</description></node>. In this
                 * case, <description> node does not have a value, but instead has a child of type node_pcdata with value "This is a node".
                 * pugixml provides child_value() and text() helper functions to parse such data.
                 */

                this->addStep(thisStep);

            }

            if(stepName == "Mash Out") {

                cout << "Mash Out step found. Adding Mash-Out temp as HLT step" << endl;

                int thisVessel = VESSEL_HLT;

                Step thisStep;
                thisStep.setVessel(thisVessel);
                thisStep.setStepLength(0);
                thisStep.setStepTemperature((float) stepTemp);
                thisStep.setStepName("HLT Mash Out Temp");

                this->addStep(thisStep);
            }

            // Add the step to the mash vessel.

            Step thisStep;
            thisStep.setVessel(VESSEL_MLT);
            thisStep.setStepLength((float) stepLength);
            thisStep.setStepTemperature((float) stepTemp);
            thisStep.setStepName(stepName);

            this->addStep(thisStep);

            i++;
        }

        // Add the boil step
        Step step;
        step.setVessel(VESSEL_KETTLE);
        step.setStepLength((float) boilLength); // boil time doesn't start until temp is reached?
        step.setStepTemperature(100.0);
        step.setStepName("Boil");

        this->addStep(step);

    } catch (exception& e) {
        // handle the exceptions generated.
        cout << "Something went wrong loading the XML file" << endl;
    }

    cout << "Recipe parsing completed. " << endl;
    
    
    cout << "insert recipe here according to the steps in each vessel " << endl;
    cout << "Does this recipe look correct? (Y/n):" << endl;
    cin >> recipeCorrect;
    
    if(recipeCorrect.compare(yesLower) != 0 || recipeCorrect.compare(yesUpper) != 0) {
    	return 1;
    }
    
    cout << endl;
    cout << "=================================" << endl;
    cout << endl;

    return 0;
}

void Batch::addStep(Step step) {

    cout << "Adding Step '" << step.getStepName() << "' to vessel " << step.getVessel() << endl;

    if(step.getVessel() == VESSEL_HLT) {
        hlt.addStep(step);
    }
    if(step.getVessel() == VESSEL_MLT) {
        mlt.addStep(step);
    }
    if(step.getVessel() == VESSEL_KETTLE) {
        kettle.addStep(step);
    }
}

Vessel Batch::getVessel(int vessel) {
    switch(vessel) {
    case VESSEL_HLT:
        hlt.setVesselType(vessel);
        return hlt;
        break;
    case VESSEL_MLT:
        mlt.setVesselType(vessel);
        return mlt;
        break;
    case VESSEL_KETTLE:
        kettle.setVesselType(vessel);
        return kettle;
        break;
    }

    // Fall back and return the HLT.
    return hlt;

}

void Batch::run() {

    // program can probably sleep here until
    // the defined target time.


    pid_t pids[10]; // array of PIDS
    int rv;         // Again does this need to be an 'array' or something to track this?

    runBatch batch;

    for(int i = 1; i <= VESSEL_KETTLE; i++) {

        switch(pids[i] = fork()) {
        case -1:
            perror("fork");  /* something went wrong */
            exit(1);         /* parent exits */

            break;
        case 0:
            // this is the child.
        	cout << "Process is totally forked. ";
            cout << "PID is: " << getpid() << endl;

            batch.runSteps(getVessel(i));

            scanf(" %d", &rv);
            cout << " CHILD: Exiting..!" << endl;
            exit(rv);

            break;
        default:
            // this is the parent
            cout << "This is the Parent, PID is: " << getpid() << endl;
            // we want this parent process to 'live' while the children are
            // also alive.
            break;
        }

    }

    for(;;) {
        // loop
    }

//    batch.runSteps(getVessel(VESSEL_HLT));
//    batch.runSteps(getVessel(VESSEL_MLT));
//    batch.runSteps(getVessel(VESSEL_KETTLE));

}


Batch::~Batch() {
    // TODO Auto-generated destructor stub
}
