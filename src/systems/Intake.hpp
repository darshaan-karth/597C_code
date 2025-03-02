#pragma once

#include "../Constants.hpp"
#include "pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct Intake{
    MotorGroup intakeMotor_g = MotorGroup({intakeMotor_p, elevatorMotor_p});

    inline void spinRev() {intakeMotor_g.move(0); intakeMotor_g.move(-(maxVolt));} //Set the motor to reverse spin with max reverse voltage
    inline void contSpin(int voltage) {intakeMotor_g.move(voltage);}

    //Auton Intake Code
    inline void autonSpinCont() {intakeMotor_g.move(127); delay(delayMove);}
    inline void autonStopCont() {intakeMotor_g.move(0); delay(delayMove);}
};