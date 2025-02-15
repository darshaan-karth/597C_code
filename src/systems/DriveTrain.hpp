#pragma once

#include "../Constants.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.h"
#include "../autonomous/PID.hpp"

using namespace Constants;
using namespace pros;

struct DriveTrain {
    PIDController pidController = PIDController(kP, kI, kD, integral_threshold); 
    MotorGroup left_g = MotorGroup({fl_p, ml_p, bl_p}); //Abstracting the left side motors as a motor group
    MotorGroup right_g = MotorGroup({fr_p, mr_p, br_p}); //Abstracting the right side motors as a motor group

    std::function<void(void)> teleMove;

    DriveTrain() {
        left_g.set_encoder_units(E_MOTOR_ENCODER_COUNTS);
        right_g.set_encoder_units(E_MOTOR_ENCODER_COUNTS);
   
        left_g.tare_position();
        right_g.tare_position();
    }

    inline void tankDrive(signed char leftY, signed char rightY){
        left_g.move(abs(leftY)<threshold ? 0 :leftY);
        right_g.move(abs(rightY)<threshold ? 0 :rightY);
    }

    inline void arcadeDrive(signed char leftY, signed char rightX) {
        leftY = abs(leftY)<threshold ? 0 : leftY;
        rightX = abs(rightX)<threshold ? 0 : rightX;
        left_g.move(leftY + rightX);
        right_g.move(leftY - rightX);
    }

    //Function allows for the forward and backward motion of the drivetrain based on the given inches
    inline void moveHorizontalPID(double inches){
        double direction = (inches > 0) ? 1:-1;
        inches = std::abs(inches);
        inches = (inches > offsetInches) ? inches - offsetInches : inches;
        int ticks = (inches / distancePerTick) / 2;

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();

        //Setting the target ticks
        pidController.setTargetTicks(ticks);
        
        /*MAJOR CHANGE FOR TESTING --> SWITCHING '&&' TO '||' TO ENSURE BOTH SIDES REACH THE TARGET
        CHANGED IT BACK TO '&&' - 2/11/2025
        */
        while (std::abs(left_g.get_position()) < ticks && std::abs(right_g.get_position()) < ticks) {
            double controlRPM = direction * pidController.compute(std::abs(left_g.get_position()));

            left_g.move_velocity(controlRPM);
            right_g.move_velocity(controlRPM);

            delay(20);
        }

        left_g.move_velocity(0);
        right_g.move_velocity(0);
        
        pidController.reset();

        delay(delayMove);
    }

    //Function allows for the angled turned allowing for the drivetrain to turn left or right at any assigned angle
    inline void turnAnglePID(double angle){
        double direction = (angle > 0) ? 1:-1;
        angle = std::abs(angle+angle_threshold);

        double distanceTravel = (trackwidth * angle * pi) / (360*2);
        int ticks = (distanceTravel / distancePerTick);

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();

        //Setting the target ticks
        pidController.setTargetTicks(ticks);
        
        while (std::abs(left_g.get_position()) < ticks && std::abs(right_g.get_position()) < ticks) {
            double controlRPM = direction * pidController.compute(std::abs(left_g.get_position()));

            left_g.move_velocity(controlRPM);
            right_g.move_velocity(-(controlRPM));

            delay(20);
        }

        left_g.move_velocity(0);
        right_g.move_velocity(0);
        
        pidController.reset();

        delay(delayMove);
    }
};