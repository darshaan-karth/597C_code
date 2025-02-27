#pragma once

#include "../Constants.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct Intake{
    public:
        bool intake_vision_state = false;

    Motor intakeMotor = Motor(intakeMotor_p); //assigning intake motor
    Motor intakeMotor2 = Motor(intakeMotor2_p);

    MotorGroup intake = MotorGroup({intakeMotor_p, intakeMotor2_p});

    inline void spinRev() {intake.move(0); intake.move(-(maxVolt));} //Set the motor to reverse spin with max reverse voltage
    inline void contSpin(int voltage) {intake.move(voltage);}

    //Auton Intake Code
    inline void autonSpinCont() {intake.move(127); delay(delayMove);}
    inline void autonStopCont() {intake.move(0); delay(delayMove);}

    //Auton Vision Intake Code
    //inline void autonSpinCont() {intake_vision_state = true;}
    //inline void autonStopCont() {intake_vision_state = false;}

    //Vision Controlled Intake
    inline void visionIntake() {
        intake.move(127);
        delay(500);
        intake.move(0); 
        delay(500);
    }
};