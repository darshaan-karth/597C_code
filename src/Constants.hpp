#pragma once
#include <stdint.h>
#include <cmath>

namespace Constants {
    static const int8_t fl_p = -2; // Port of Front Left motor
    static const int8_t ml_p = 18; // Port of Middle Left (Back Bottom) motor
    static const int8_t bl_p = -20; // Port of Back Left (Back Top) motor , Because this is on top reversing it

    static const int8_t fr_p = 15; // Port of Front Right motor
    static const int8_t mr_p = -16; // Port of Middle Right (Back Bottom) motor
    static const int8_t  br_p = 9; // Port of Back Right (Back Top) motor, Because this is on top reversing it

    static constexpr unsigned char clamp_p = 'A'; // Port for the Pneumatic clamps
    static constexpr unsigned char arm_p = 'B'; // Port for the Pneumatic clamps
    static constexpr unsigned char intakeMotor_p = -19; // Port for the intake button
    static constexpr unsigned char imu_p = 5; // Port for the IMU

    static const double pi = 3.14159265358979323846; // pi
    static constexpr double trackwidth = 12.25f; // The distance between both the left and an right motors
    static constexpr double wheelDiameter = 3.25f; // Diameter of drive wheels(inches)
    static const double gearRatio = 3.0/5.0;
    static const int encoder_ticks_per_rev = 1800;
    static const double wheelCircumference = wheelDiameter * pi;
    static const double distancePerTick = wheelCircumference/(encoder_ticks_per_rev * gearRatio);

    //MOVE PID Control Constants
    /*IMPORTANT - NEED TO FINE TUNE TO THE PID CONSTANTS TO ADJUST FOR DIFFERENCES IN FIELD  ***THESE VALUES ARE SUBJECTED TO CHANGE BASED ON ROBOT*** */
    static const double pid_c_move = 1.5625;  //Speedup by 1.225
    static const double kP_move = 0.128 * pid_c_move;
    static const double kI_move = 0.0399* pid_c_move;
    static const double kD_move = 0.129* pid_c_move;
    static const double integral_threshold_move = 10;

    //TURN PID Control Constants
    static const double pid_c_turn = 1;
    static const double kP_turn = 0.129 * pid_c_turn;
    static const double kI_turn = 0.0399* pid_c_turn;
    static const double kD_turn = 0.129* pid_c_turn;
    static const double integral_threshold_turn = 10;

    //PID Offset
    static const double jitter_move_threshold = 10;  //TESTING AFTER THE NEW PID TEST
    static const double angle_threshold = 2;
    static const double pid_threshold = 250;

    //Restricting Variables
    static const double maxRPM = 600; //600
    static constexpr unsigned char threshold = 9; // Threshhold for controller to start moving the robot (7%)
    static const int maxAutonVolt = 127;
    static const int maxVolt = 127; //True max volt is 127 but the restricting max volt is 120;
    static const int minVolt = 100;
    static const int delayMove = 10;

    //Auton modes
    static const bool isSkills = false; // if FALSE then in-match auton else Skills auton

    static const bool winPointSide = false; // if TRUE then in-match auton would be starting from the side with extra mobile stake else the other side
    static const bool isBlue = true; // if TRUE then in-match auton is starting from BLUE SIDE else RED SIDE
};