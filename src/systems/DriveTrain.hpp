#pragma once

#include "../Constants.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.h"
#include "../autonomous/PID.hpp"
#include "pros/imu.hpp"

using namespace Constants;
using namespace pros;

struct DriveTrain {
    PIDController move_pidController = PIDController(kP_move, kI_move, kD_move, integral_threshold_move);
    PIDController turn_pidController = PIDController(kP_turn, kI_turn, kD_turn, integral_threshold_turn); 

    Imu imuSensor = Imu(imu_p); //Setting up the IMU sensor
    MotorGroup left_g = MotorGroup({fl_p, ml_p, bl_p}); //Abstracting the left side motors as a motor group
    MotorGroup right_g = MotorGroup({fr_p, mr_p, br_p}); //Abstracting the right side motors as a motor group

    std::function<void(void)> teleMove;

    DriveTrain() {
        left_g.set_encoder_units(E_MOTOR_ENCODER_COUNTS);
        right_g.set_encoder_units(E_MOTOR_ENCODER_COUNTS);
   
        left_g.tare_position();
        right_g.tare_position();
        imuSensor.tare_yaw();
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
        //double direction = (inches > 0) ? 1:-1;
        //inches = std::abs(inches);
        double turn_yaw, turn_controlRPM, left_controlRPM, right_controlRPM;
        int ticks = (inches / distancePerTick) / 2;

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();
        imuSensor.tare_yaw();

        //Setting the target ticks
        move_pidController.reset();
        turn_pidController.reset();
        move_pidController.setTargetTicks(ticks);
        turn_pidController.setTargetTicks(0);

        //(std::abs(left_g.get_position()) < std::abs(ticks) && std::abs(right_g.get_position()) < std::abs(ticks))
        while (std::abs((left_g.get_position() + right_g.get_position()) / 2) < std::abs(ticks)) {
            double move_controlRPM = move_pidController.compute(((left_g.get_position() + right_g.get_position()) / 2), false);
            
            if (std::abs(move_controlRPM) > pid_threshold){
                turn_yaw = (imuSensor.get_yaw() < 0) ? -(imuSensor.get_yaw() - angle_threshold) : -(imuSensor.get_yaw() + angle_threshold);
                turn_controlRPM = turn_pidController.compute(turn_yaw, true);
            }

            if (turn_controlRPM > 0){
                left_controlRPM = move_controlRPM + turn_controlRPM;
                right_controlRPM = move_controlRPM;
            } else {
                left_controlRPM = move_controlRPM;
                right_controlRPM = move_controlRPM + turn_controlRPM;
            }

            left_controlRPM = std::clamp(left_controlRPM, -maxRPM, maxRPM);
            right_controlRPM = std::clamp(right_controlRPM, -maxRPM, maxRPM);
            
            left_g.move_velocity(left_controlRPM);
            right_g.move_velocity(right_controlRPM);

            delay(5);
        }

        left_g.move_velocity(0);
        right_g.move_velocity(0);
        
        move_pidController.reset();
        turn_pidController.reset();
        delay(delayMove);
    }

    //Function allows for the angled turned allowing for the drivetrain to turn left or right at any assigned angle
    inline void turnAnglePID(double angle){
        //double direction = (angle > 0) ? 1:-1;
        //angle = std::abs(angle);     
        imuSensor.tare_yaw();

        //Setting the target ticks
        turn_pidController.reset();
        turn_pidController.setTargetTicks(angle);
        
        while (std::abs(imuSensor.get_yaw()) < std::abs(angle)) {
            double turn_yaw = (imuSensor.get_yaw() < 0) ? -(imuSensor.get_yaw() - angle_threshold) : -(imuSensor.get_yaw() - angle_threshold);
            double turn_controlRPM = turn_pidController.compute(turn_yaw, true);
            turn_controlRPM = std::clamp(turn_controlRPM, -maxRPM, maxRPM);

            left_g.move_velocity(turn_controlRPM);
            right_g.move_velocity(-(turn_controlRPM));

            delay(5);
        }

        left_g.move_velocity(0);
        right_g.move_velocity(0);
        
        turn_pidController.reset();
        delay(delayMove);
    }
};