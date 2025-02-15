#pragma once

#include "pros/adi.hpp"
#include "../Constants.hpp"

using namespace pros::adi;
using namespace Constants;

class ArmMech {
    private:
        DigitalOut armMechLock = DigitalOut(arm_p, false);
        bool stateArm = false;

    public:
        ArmMech(){}
        void toggleArmState(){stateArm=!stateArm; armMechLock.set_value(stateArm);}
};