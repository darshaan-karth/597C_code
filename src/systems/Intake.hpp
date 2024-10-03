#pragma once

#include "../Constants.hpp"
#include "pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct Intake{
    Motor intakeMotor = Motor(intakeMotor_p); //assigning intake motor
    inline void spin() {intakeMotor.move(95);}
    inline void spinFast() {intakeMotor.move(127);} //Set the motor to spin with max voltage
    inline void stop() {intakeMotor.move(0);} //Set the motor to stop by setting voltage = 0
    inline void spinRev() {intakeMotor.move(-127);} //Set the motor to reverse spin with max reverse voltage
};