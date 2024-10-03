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

    static constexpr unsigned char threshold = 11; // Threshhold for controller to start moving the robot
    
    static constexpr float trackwidth = 7.5f; // The distance between both the left and an right motors

    static const double pi = 3.14159265358979323846; // pi
    static const double radToDeg = 180/pi;
    static constexpr float wheelDiameter = 3.25f; // Diameter of drive wheels

    /*
    1800 ticks/rev with 36:1 gears (BLUE)
    900 ticks/rev with 18:1 gears (GREEN)
    300 ticks/rev with 6:1 gears (RED)

    Gear Ratio : 36:60
    (1800 * 3/5)
    */

    static constexpr double unitsToRevolution = 1080; // Motor units per revolution for drive wheels (1800 * 3/5)
    static const double inchesPerTick = wheelDiameter*pi/unitsToRevolution; // The inches per tick for the drive encoders

    static inline double headingRestrict(double heading) {
        if (heading <= 0) heading += pi*2;
        heading = fmod(std::abs(heading),pi*2);
        return heading;
    }
};