<?php

define('HLT', 1);
define('MLT', 2);
define('KETTLE', 3);

class batch {

    private $hlt = null;
    private $mlt = null;
    private $kettle = null;

    public function __construct() {

        $this->hlt = new hlt();
        $this->mlt = new mlt();
        $this->kettle = new kettle();

    }

    public function addStep(Step $step) {

        if($step->vessel == HLT) {
            $this->hlt->addStep($step);
        }

        if($step->vessel == MLT) {
            $this->mlt->addStep($step);
        }

        if($step->vessel == KETTLE) {
            $this->kettle->addStep($step);
        }
    }

    public function getVessel($vessel) {
        if($vessel == HLT) {
            return $this->hlt;
        }

        if($vessel == MLT) {
            return $this->mlt;
        }

        if($vessel == KETTLE) {
            return $this->kettle;
        }
    }

    private function checkSteps() {

        // hlt
        if($this->hlt->getNumSteps() == 0) {
            print"HLT has no steps configured!" . PHP_EOL;
        }

        // mlt
        if($this->mlt->getNumSteps() == 0) {
            print"MLT has no steps configured!" . PHP_EOL;
        }

        // kettle
        if($this->kettle->getNumSteps() == 0) {
            print"KETTLE has no steps configured!" . PHP_EOL;
        }

    }

    public function run() {

        $this->checkSteps();

        runBatch::run($this);
    }

}

// --

class vessel {

    // hardware

    // steps
    private $steps = array();

    public function addStep(Step $step) {

        $this->steps[] = $step;

    }

    public function getNumSteps() {
        return sizeof($this->steps);
    }

    public function getAllSteps() {
        return $this->steps;
    }

}

class hlt extends vessel {

    // vessel has some hardware to control
    private $pumps = array();

}

class mlt extends vessel {

}

class kettle extends vessel {

}

// --

abstract class Step {

    public $stepNumber = NULL;
    public $vessel     = NULL;
    public $stepLength = NULL;
    public $stepName   = NULL;

}

class hltAutoFill extends Step {

    public $stepNumber = 1;
    public $vessel     = HLT;
    public $stepLength = 600;
    public $stepName   = "HLT Auto Fill";

}

class hltBoil extends Step {

    public $stepNumber = 2;
    public $vessel     = HLT;
    public $stepLength = 900;
    public $stepName   = "HLT 15min Boil";

}

// --

// hardware objects
class sensors {


}

class pumps {


}

// --

class runBatch {

    public static function run(Batch $batch) {

        // do the HLT steps
        self::runSteps($batch->getVessel(HLT));

        // do the MLT steps
        self::runSteps($batch->getVessel(MLT));

        // do the KETTLE steps
        self::runSteps($batch->getVessel(KETTLE));

    }


    private static function runSteps(Vessel $vessel) {

        $numSteps = $vessel->getNumSteps();

        print"This vessel has " . $numSteps . " steps configured.";

        if($numSteps == 0) {
            print "No steps configured." . PHP_EOL;
            return;
        }

        print"Executing..." . PHP_EOL;

        $steps = $vessel->getAllSteps();

        foreach($steps as $step) {
            print"Running Step Name: " . $step->stepName . PHP_EOL;

            print"Step runs for... " . $step->stepLength . " seconds (sleeping for 5)" . PHP_EOL;
            sleep(5);
        }

    }

}


//--- create a batch
$batch = new Batch;
$batch->addStep(new hltAutoFill());
$batch->addStep(new hltBoil());
$batch->run();
