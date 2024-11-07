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
    static constexpr unsigned char distanceSensor_p = 12;

    static const double pi = 3.14159265358979323846; // pi
    static const double degToRad = pi/180.0;
    static constexpr double trackwidth = 12.25f; // The distance between both the left and an right motors
    static constexpr double wheelDiameter = 3.25f; // Diameter of drive wheels(inches)
    static const double gearRatio = 3.0/5.0;
    static const int encoder_ticks_per_rev = 1800;
    static const double wheelCircumference = wheelDiameter * pi;
    static const double distancePerTick = wheelCircumference/(encoder_ticks_per_rev*gearRatio);
    
    /*
    1800 ticks/rev with 36:1 gears (BLUE)
    900 ticks/rev with 18:1 gears (GREEN)
    300 ticks/rev with 6:1 gears (RED)

    Gear Ratio : 36:60
    (1800 * 3/5)
    */

    static constexpr double ticksToRevolution = 1080; // Motor ticks per revolution for drive wheels (1800 * 3/5)
    static const double inchesPerTick = (wheelDiameter*pi)/ticksToRevolution; // The inches per tick for the drive encoders

    //Restricting Variables
    static constexpr unsigned char threshold = 9; // Threshhold for controller to start moving the robot (7%)
    static const int maxRPM = 100;
    static const int maxVolt = 120; //True max volt is 127 but the restricting max volt is 120;
    static const int minVolt = 100;
    static const int delayMove = 20;
};