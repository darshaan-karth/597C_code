#pragma once

#include "../Constants.hpp"
#include "pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct Intake{
    Motor intakeMotor = Motor(intakeMotor_p); //assigning intake motor
    inline void spin(int voltage) {intakeMotor.move(0); intakeMotor.move(voltage);}
    inline void spinRev() {intakeMotor.move(0); intakeMotor.move(-127);} //Set the motor to reverse spin with max reverse voltage
    inline void stop() {intakeMotor.move(0);} //Set the motor to stop by setting voltage = 0
    inline void contSpin(int voltage) {intakeMotor.move(voltage);}
};