#pragma once

#include "../Constants.hpp"

using namespace Constants;

class PIDController {
    private:
        double kp, ki, kd;
        double integral;
        double integralThreshold;
        double previousError;

    public:
        PIDController(double kp, double ki, double kd, double integralThreshold) : kp(kp), ki(ki), kd(kd), integralThreshold(integralThreshold) {
            previousError = 0.0;
            integral = 0.0;
            }

        void reset() {previousError = 0.0; integral = 0.0;}

        double compute(double target_value, double current_value){
            double error = target_value - current_value;
            
            if (abs(error) < integralThreshold){integral += error;}
            else {integral=0;}

            double derivative = error - previousError;

            previousError = error;

            double velocity = (kp*error) + (ki*integral) + (kd*derivative);
            return velocity;
        }
};