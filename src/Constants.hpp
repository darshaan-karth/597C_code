#pragma once
#include <stdint.h>
#include <cmath>

namespace Constants {
    static const int8_t fl_p = -15; // Port of Front Left motor
    static const int8_t ml_p = -16; // Port of Middle Left (Back Bottom) motor
    static const int8_t bl_p = 17; // Port of Back Left (Back Top) motor , Because this is on top reversing it

    static const int8_t fr_p = 18; // Port of Front Right motor
    static const int8_t mr_p = 20; // Port of Middle Right (Back Bottom) motor
    static const int8_t  br_p = -19; // Port of Back Right (Back Top) motor, Because this is on top reversing it

    static constexpr unsigned char clamp_p = 'A'; // Port for the Pneumatic clamps
    static constexpr unsigned char intakeMotor_p = 14; // Port for the intake button

    static const double pi = 3.14159265358979323846; // pi
    static constexpr double trackwidth = 12.25f; // The distance between both the left and an right motors
    static constexpr double wheelDiameter = 3.25f; // Diameter of drive wheels(inches)
    static const double gearRatio = 3.0/5.0;
    static const int encoder_ticks_per_rev = 1800;
    static const double wheelCircumference = wheelDiameter * pi;
    static const double distancePerTick = wheelCircumference/(encoder_ticks_per_rev * gearRatio);
    static const int offsetInches = 2; // Fix the drivetrain before programming autonomous
    static const int offsetAngle = 9;

    //PID Control Constants
    static const double kP = 0.3;
    static const double kI = 0.2;
    static const double kD = 0.1;
    static const double integral_threshold = 10;

    /*
    1800 ticks/rev with 36:1 gears (BLUE)
    900 ticks/rev with 18:1 gears (GREEN)
    300 ticks/rev with 6:1 gears (RED)

    Gear Ratio : 36:60
    (1800 * 3/5)
    */

    //Restricting Variables
    static constexpr unsigned char threshold = 9; // Threshhold for controller to start moving the robot (7%)
    static const int maxRPM = 80;
    static const int maxAutonVolt = 127;
    static const int maxVolt = 127; //True max volt is 127 but the restricting max volt is 120;
    static const int minVolt = 150;
    static const int delayMove = 100;

    //Auton modes
    static const bool isSkills = true; // if FALSE then in-match auton else Skills auton
    static const bool leftMode = true; // if TRUE then in-match auton would be starting from left side else right side
    static const bool isBlue = true; // if TRUE then in-match auton is starting from BLUE SIDE else RED SIDE
    static const bool testingMode = false;
    static const bool pair_597A = false;
};