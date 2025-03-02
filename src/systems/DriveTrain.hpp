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
        int ticks = (inches / distancePerTick) / 2;

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();
        imuSensor.tare_yaw();

        //Setting the target ticks
        move_pidController.reset();
        turn_pidController.reset();

        double left_controlRPM, right_controlRPM;
        double current_angle, turn_error, move_error, turn_controlRPM, move_controlRPM;

        while (true){
            if (std::abs((left_g.get_position() + right_g.get_position()) / 2) < std::abs(ticks)) {break;}
            move_controlRPM = move_pidController.compute(ticks, ((left_g.get_position() + right_g.get_position()) / 2));
            
            // If we need to correct the turn
            move_error = ticks - ((left_g.get_position() + right_g.get_position()) / 2);
            if (std::abs(move_error) > move_threshold) {
                current_angle = imuSensor.get_yaw();

                // Normalize the error to ensure the shortest path to the target angle
                turn_error = 0 - current_angle;
                if (turn_error < -180) { turn_error += 360;}  // Normalize to [-180, 180]
                else if (turn_error > 180) { turn_error -= 360;}

                turn_controlRPM = turn_pidController.compute(0, current_angle);
            } else {turn_controlRPM = 0;}
            
            // Adjust the left and right velocities based on the PID outputs
            left_controlRPM = move_controlRPM + turn_controlRPM;
            right_controlRPM = move_controlRPM - turn_controlRPM;

            left_controlRPM = left_controlRPM * auton_drive_speedup;
            right_controlRPM = right_controlRPM * auton_drive_speedup;

            left_controlRPM = std::clamp(left_controlRPM, -maxRPM, maxRPM);
            right_controlRPM = std::clamp(right_controlRPM, -maxRPM, maxRPM);
            
            left_g.move_velocity(left_controlRPM);
            right_g.move_velocity(right_controlRPM);

            delay(5);
        }

        left_g.move_velocity(0);
        right_g.move_velocity(0);
        delay(delayMove);
    }

    //Function allows for the angled turned allowing for the drivetrain to turn left or right at any assigned angle
    inline void turnAnglePID(double angle){    
        imuSensor.tare_yaw();
        turn_pidController.reset();
        
        double current_angle, error, turn_controlRPM;

        while (true) {
            current_angle = imuSensor.get_yaw();

            // Normalize the error to ensure the shortest path to the target angle
            error = angle - current_angle;
            if (error < -180) { error += 360; }  // Normalize to [-180, 180]
            else if (error > 180) { error -= 360; }

            // Stop if the robot is close enough to the target angle
            if (std::abs(error) <= angle_threshold) {break;}

            turn_controlRPM = turn_pidController.compute(angle, current_angle);
            turn_controlRPM = turn_controlRPM * auton_drive_speedup;

            turn_controlRPM = std::clamp(turn_controlRPM, -maxRPM, maxRPM);

            left_g.move_velocity(turn_controlRPM);
            right_g.move_velocity(-(turn_controlRPM));

            delay(5);
        }

        left_g.move_velocity(0);
        right_g.move_velocity(0);
        delay(delayMove);
    }
};