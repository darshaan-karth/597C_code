#pragma once

#include "../Constants.hpp"
#include "pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct Intake{
    Motor intakeMotor = Motor(intakeMotor_p); //assigning intake motor
    inline void spin(int voltage) {intakeMotor.move(0); intakeMotor.move(voltage);}
    inline void spinRev() {intakeMotor.move(0); intakeMotor.move(-(maxVolt));} //Set the motor to reverse spin with max reverse voltage
    inline void contSpin(int voltage) {intakeMotor.move(voltage);}
    inline void autonSpin(int voltage, int duration) {intakeMotor.move(voltage); delay(duration); intakeMotor.move(0);}
};