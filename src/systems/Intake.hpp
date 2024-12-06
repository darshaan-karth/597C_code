#pragma once

#include "../Constants.hpp"
#include "pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct Intake{
    public:
        bool intake_vision_state = false;

    Motor intakeMotor = Motor(intakeMotor_p); //assigning intake motor
    inline void spinRev() {intakeMotor.move(0); intakeMotor.move(-(maxVolt));} //Set the motor to reverse spin with max reverse voltage
    inline void contSpin(int voltage) {intakeMotor.move(voltage);}

    //Auton Intake Code
    //inline void autonSpinCont() {intakeMotor.move(127); delay(delayMove);}
    //inline void autonStopCont() {intakeMotor.move(0); delay(delayMove);}

    //Auton Vision Intake Code
    inline void autonSpinCont() {intake_vision_state = true;}
    inline void autonStopCont() {intake_vision_state = false;}

    //Vision Controlled Intake
    inline void visionIntake() {
        intakeMotor.move(127);
        delay(500);
        intakeMotor.move(0); 
        delay(500);
    }
};