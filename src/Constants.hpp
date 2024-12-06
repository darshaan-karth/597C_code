#pragma once
#include <stdint.h>
#include <cmath>

namespace Constants {
    static const int8_t fl_p = -15; // Port of Front Left motor
    static const int8_t ml_p = 16; // Port of Middle Left (Back Bottom) motor
    static const int8_t bl_p = -17; // Port of Back Left (Back Top) motor , Because this is on top reversing it

    static const int8_t fr_p = 18; // Port of Front Right motor
    static const int8_t mr_p = -20; // Port of Middle Right (Back Bottom) motor
    static const int8_t  br_p = 19; // Port of Back Right (Back Top) motor, Because this is on top reversing it

    static constexpr unsigned char clamp_p = 'A'; // Port for the Pneumatic clamps
    static constexpr unsigned char intakeMotor_p = 14; // Port for the intake button
    static constexpr unsigned char vision_p = 13;

    static const double pi = 3.14159265358979323846; // pi
    static constexpr double trackwidth = 12.25f; // The distance between both the left and an right motors
    static constexpr double wheelDiameter = 3.25f; // Diameter of drive wheels(inches)
    static const double gearRatio = 3.0/5.0;
    static const int encoder_ticks_per_rev = 1800;
    static const double wheelCircumference = wheelDiameter * pi;
    static const double distancePerTick = wheelCircumference/(encoder_ticks_per_rev * gearRatio);
    static const int offsetInches = 2; // Fine-tuning the drivetrain for auton  **TRY 11 inches**  - 2

    //Setting up the signature IDs for blue and red colors
    constexpr int NAN_SIG_id = 0;
    constexpr int RED_SIG_id = 1;
    constexpr int BLUE_SIG_id = 2;
    static const int object_threshold = 0;
    static const int NUM_VISION_OBJECTS = 4;

    //PID Control Constants
    static const double kP = 0.2;
    static const double kI = 0.2;
    static const double kD = 0.2;
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
    static const int minVolt = 100;
    static const int delayMove = 150;

    //Auton modes
    static const bool isSkills = false; // if FALSE then in-match auton else Skills auton

    static const bool winPointSide = true; // if TRUE then in-match auton would be starting from the side with extra mobile stake else the other side
    static const bool isBlue = true; // if TRUE then in-match auton is starting from BLUE SIDE else RED SIDE
};