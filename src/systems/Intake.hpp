#pragma once

#include "../Constants.hpp"
#include "pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct Intake{
    Motor intakeMotor = Motor(intakeMotor_p); //assigning intake motor
    inline void spinRev() {intakeMotor.move(0); intakeMotor.move(-(maxVolt));} //Set the motor to reverse spin with max reverse voltage
    inline void contSpin(int voltage) {intakeMotor.move(voltage);}

    //Auton Intake Code
    inline void autonSpinCont() {intakeMotor.move(127); delay(delayMove);}
    inline void autonStopCont() {intakeMotor.move(0); delay(delayMove);}
};