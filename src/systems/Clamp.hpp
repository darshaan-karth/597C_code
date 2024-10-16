#pragma once

#include "pros/adi.hpp"
#include "../Constants.hpp"

using namespace pros::adi;
using namespace Constants;

class Clamps {
    private:
        DigitalOut clampLock = DigitalOut(clamp_p, false);
        bool stateClamp = false;

    public:
        Clamps(){}
        void toggleClampLock(){stateClamp=!stateClamp; clampLock.set_value(stateClamp);}
};