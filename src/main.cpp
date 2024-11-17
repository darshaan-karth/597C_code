#include "main.h"
#include "Constants.hpp"
#include "pros/misc.h"
#include "systems/DriveTrain.hpp"
#include "systems/Intake.hpp"
#include "systems/Clamp.hpp"

using namespace pros;

DriveTrain dt = DriveTrain();
Intake intk = Intake();
Clamps clamp = Clamps();
PIDController pidController = PIDController(kP, kI, kD); 
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
void autonomous() {
	if (isSkills == false){
		if (testingMode == false) {
			dt.moveHorizontal(-35);
			delay(500);
			clamp.toggleClampLock();
			delay(500);
			dt.turnAngle(86);
			delay(500);
			dt.moveHorizontal(28);
			delay(500);
			intk.autonSpin(maxAutonVolt, 4000); //duration is in milliseconds
			delay(500);
			dt.moveHorizontal(-28);
			delay(500);
			dt.turnAngle(189);
			delay(500);
			clamp.toggleClampLock();
			delay(500);
			dt.moveHorizontal(25);
		} else {
			int chgAngle = (isBlue == true) ? 1 : -1;
			dt.moveHorizontal(-30);
			clamp.toggleClampLock();
			dt.turnAngle(-41.5 * chgAngle);
			delay(300);
			intk.autonSpinCont();
			delay(400);
			dt.moveHorizontal(37);
			delay(1700);
			dt.moveHorizontal(5);
			delay(500);
			intk.autonStopCont();
			dt.turnAngle(180 * chgAngle);

			if (pair_597A == false){
				clamp.toggleClampLock();
				dt.moveHorizontal(41);
				delay(500);
				dt.turnAngle(-37.75 * chgAngle); //-45
				intk.autonSpinCont();
				dt.moveHorizontal(21);
				delay(200);
				intk.autonStopCont();
				dt.moveHorizontal(5);
				dt.turnAngle(-90 * chgAngle);
				delay(500);
				dt.moveHorizontal(-15.75);
				delay(500);
				clamp.toggleClampLock();
				intk.autonSpinCont();
				delay(300);
				dt.moveHorizontal(20);
				dt.turnAngle(-90 * chgAngle);
				delay(600);
				intk.autonStopCont();
				clamp.toggleClampLock();
				dt.moveHorizontal(48);
			} else {
				dt.moveHorizontal(41);
				delay(500);
				dt.turnAngle(-37.75 * chgAngle); //-45
				intk.autonSpinCont();
				dt.moveHorizontal(21);
				delay(500);
				intk.autonStopCont();
				dt.moveHorizontal(-27);
				delay(500);
				dt.turnAngle(189 * chgAngle);
				delay(500);
				clamp.toggleClampLock();
				delay(500);
				dt.moveHorizontal(25);
			}
		}
	} else if (isSkills == true){
		dt.moveHorizontalPID(-30);
		dt.turnAnglePID(-45);
		dt.moveHorizontalPID(30);
	}
}

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
	int currentVolt = 0;

	while (true) {
		//Calling DriveTrain System
		dt.teleMove();

		//Intake System to spin, spinFast, spinRev, or stop
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {intk.contSpin(maxVolt);}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {intk.spinRev();}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && (millis() - intkTime > 500)){intk.contSpin(currentVolt); currentVolt = (currentVolt==maxVolt) ? 0:maxVolt; intkTime = millis();} //changing the volt values for the continous intake system
		else if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 0) && (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)==0)) {intk.contSpin(currentVolt);} //If no inputs detected, the voltage of the motors will be decided by the volt variable
	
		//ClampLock System for Mobile Goal Locking
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && (millis() - clampTime > 500)) {clamp.toggleClampLock(); clampTime = millis();};

		delay(20);// Run for 20 ms then update
	}
}