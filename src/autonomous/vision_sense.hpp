#pragma once

#include "../Constants.hpp"
#include "pros/screen.hpp"
#include "pros/vision.hpp"

using namespace Constants;
using namespace pros;

struct VisionRedBlue {
    pros::Vision vision_sensor = pros::Vision(vision_p);
    pros::vision_object_s_t object_arr[NUM_VISION_OBJECTS];

    //Converting to pros signature based on the VEX Vision Utility Output
    vision_signature_s_t RED_SIG = Vision::signature_from_utility(RED_SIG_id, 7717, 9497, 8607, -1129, -419, -774, 2.5, 0);
    vision_signature_s_t BLUE_SIG = Vision::signature_from_utility(BLUE_SIG_id, -3455, -2823, -3139, 5995, 7729, 6862, 2.5, 0);

    //Creating the Color Code for the Vision Sensor to detect
    vision_color_code_t COLOR_CODE = vision_sensor.create_color_code(RED_SIG_id, BLUE_SIG_id);

    VisionRedBlue(){
        //Setting up the signatures into the brain
        vision_sensor.set_signature(RED_SIG_id, &RED_SIG);
        vision_sensor.set_signature(BLUE_SIG_id, &BLUE_SIG);
        vision_sensor.clear_led();
    }

    //To detect the color of the ring in the intake conveyor belt
    int detect_color(){
        int detect_sig = NAN_SIG_id;
        screen::print(pros::E_TEXT_MEDIUM, 2, "Object Count: %d", vision_sensor.get_object_count());
        if (vision_sensor.get_object_count() > object_threshold) {
            vision_sensor.read_by_code(0, COLOR_CODE, NUM_VISION_OBJECTS, object_arr);
            detect_sig = object_arr[0].signature;
            //screen::print(pros::E_TEXT_MEDIUM, 2, "Found a %s", ((detect_sig==RED_SIG_id)?"RED":"BLUE"));
        } 
        screen::print(pros::E_TEXT_MEDIUM, 5, "Signature: %d", detect_sig);
        return(detect_sig);
    }
};

        