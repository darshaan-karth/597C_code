#pragma once

#include "../Constants.hpp"

using namespace Constants;

class PIDController {
    private:
        double kp, ki, kd;
        double integral;
        double integralThreshold;
        double previousError;
        double target_ticks;

    public:
        PIDController(double kp, double ki, double kd, double integralThreshold) : kp(kp), ki(ki), kd(kd), integralThreshold(integralThreshold) {
            previousError = 0.0;
            integral = 0.0;
            }

        void setTargetTicks(double target) {target_ticks = target;}
        void reset() {target_ticks = 0.0; previousError = 0.0; integral = 0.0;}

        double compute(double current_ticks, bool is_turn_pid){
            double error = target_ticks - current_ticks;
            
            if (is_turn_pid){
                if (error < -180) {error += 360;}
                else if (error > 180) {error += 360;}
            }
            
            if (abs(error) < integralThreshold){integral += error;}
            else {integral=0;}

            double derivative = error - previousError;

            previousError = error;

            double velocity = (kp*error) + (ki*integral) + (kd*derivative);
            return velocity;
        }
};