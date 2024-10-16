#include "main.h"
#include "pros/misc.h"
#include "systems/DriveTrain.hpp"
#include "systems/Intake.hpp"
#include "systems/Clamp.hpp"

using namespace pros;

DriveTrain dt = DriveTrain();
Intake intk = Intake();
Clamps clamp = Clamps();
Controller master(E_CONTROLLER_MASTER);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	dt.teleMove = [=]{dt.tankDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));};
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	int clampTime = 0;
	int intkTime = 0;
	int volt = 0;
	int maxVolt = 127;
	int minVolt = 95;

	while (true) {
		//printing the volts values
		master.print(0, 0, "Voltage: %d", volt);

		//Calling DriveTrain System
		dt.teleMove();

		//Intake System to spin, spinFast, spinRev, or stop
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){intk.spin(maxVolt);}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {intk.spin(minVolt);}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {intk.spinRev();}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && (millis() - intkTime > 500)){intk.contSpin(volt); volt = (volt==maxVolt) ? 0:maxVolt; intkTime = millis();} //changing the volt values for the continous intake system
		else if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 0) && (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)==0)) {intk.contSpin(volt);} //If no inputs detected, the voltage of the motors will be decided by the volt variable
	
		//ClampLock System for Mobile Goal Locking
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && (millis() - clampTime > 500)) {clamp.toggleClampLock(); clampTime = millis();};

		delay(20);// Run for 20 ms then updatejiwjeiwe
	}
}