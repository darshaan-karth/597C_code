#pragma once

#include "../Constants.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.h"


using namespace Constants;
using namespace pros;

struct DriveTrain {
    MotorGroup left_g = MotorGroup({fl_p, ml_p, bl_p}); //Abstracting the left side motors as a motor group
    MotorGroup right_g = MotorGroup({fr_p, mr_p, br_p}); //Abstracting the right side motors as a motor group

    std::function<void(void)> teleMove;

    DriveTrain() {
        left_g.set_brake_mode_all(E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_mode_all(E_MOTOR_BRAKE_HOLD);

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
    inline void moveHorizontal(double inches){
        int ticksToMove = (inches-6)/distancePerTick;

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();

        left_g.move_relative(ticksToMove, maxRPM);
        right_g.move_relative(ticksToMove, maxRPM);
        
        while (std::abs(left_g.get_position()) <= abs(ticksToMove) && std::abs(right_g.get_position()) <= abs(ticksToMove)) {
            delay(20); // Prevents busy waiting
        }

        left_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        delay(delayMove);
    }

    //Function allows for the angled turned allowing for the drivetrain to turn left or right at any assigned angle
    inline void turnAngle(double angle){
        double distanceTravel = ((trackwidth)*angle*pi)/(360.0*2.0);
        int ticks = distanceTravel/distancePerTick;

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();
        
        left_g.move_relative(ticks, maxRPM);
        right_g.move_relative(-(ticks), maxRPM);

        while (std::abs(left_g.get_position()) <= abs(ticks) && std::abs(right_g.get_position()) <= abs(ticks)) {
            delay(20); // Prevents busy waiting
        }

        delay(delayMove);
    }
};