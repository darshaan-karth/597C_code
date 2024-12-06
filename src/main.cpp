#include "main.h"
#include "Constants.hpp"
#include "pros/misc.h"
#include "systems/DriveTrain.hpp"
#include "systems/Intake.hpp"
#include "systems/Clamp.hpp"
#include "autonomous/vision_sense.hpp"

#include "pros/screen.hpp"

using namespace pros;

DriveTrain dt = DriveTrain();
Intake intk = Intake();
Clamps clamp = Clamps();
VisionRedBlue vision_sense = VisionRedBlue();
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
* The functions below are autonomous sequence for in-match auton and skills challenge auton
* In-match Auton -
*		Basic Auton Sequence -> Works in all sides of the field. Uses 1 stake, scores 1 preload ring and 1 field ring, and contact the ladder
*		Win Point Advanced Auton Sequence -> 
* Skills Auton -> **/

//The basic in-match auton sequence
void basic_auton(){
	dt.moveHorizontalPID(-35);
	delay(500);
	clamp.toggleClampLock();
	delay(500);
	dt.turnAnglePID(86);
	delay(500);
	dt.moveHorizontalPID(28);
	delay(500);
	intk.autonSpinCont();
	delay(4000);
	intk.autonStopCont();
	delay(500);
	dt.moveHorizontalPID(-28);
	delay(500);
	dt.turnAnglePID(189);
	delay(500);
	clamp.toggleClampLock();
	delay(500);
	dt.moveHorizontalPID(25);
	}
//Advanced in-match Win Point auton sequence 
void win_advanced_auton(int chgAngle){
	//First Stake Loading Phase with two alliance color rings & 1 Stake
	dt.moveHorizontalPID(-30);
	clamp.toggleClampLock();
	//dt.moveHorizontalPID(-9); // TEST THIS LINE of CODE
	dt.turnAnglePID(-45 * chgAngle); //-41.5
	intk.autonSpinCont();
	delay(300);
	dt.moveHorizontalPID(34); //37
	delay(1700);
	intk.autonStopCont();
	dt.turnAnglePID(180 * chgAngle);
	clamp.toggleClampLock();

	 //Second Stake Loading Phase with 1 alliance color ring & 1 Stake
	dt.moveHorizontalPID(34); //41
	delay(500);
	dt.turnAnglePID(-45 * chgAngle); //-37.75
	intk.autonSpinCont();
	dt.moveHorizontalPID(22); //21
	delay(200);
	intk.autonStopCont();
	dt.moveHorizontalPID(2); //5
	dt.turnAnglePID(-90 * chgAngle);
	delay(500);
	dt.moveHorizontalPID(-13); //-15.75
	delay(500);
	clamp.toggleClampLock();
	intk.autonSpinCont();
	delay(300);
	dt.moveHorizontalPID(13);
	dt.turnAnglePID(-90 * chgAngle);
	delay(600);
	intk.autonStopCont();
	clamp.toggleClampLock();
	dt.moveHorizontalPID(40);//48
	}
//Advanced in-match Scoring auton sequence
void score_advanced_auton(int chgAngle){
	//First Phase of right mode: 1 alliance color ring & 1 stake
	dt.moveHorizontalPID(-30);
	clamp.toggleClampLock();
	dt.moveHorizontalPID(-9); //TESTING -9
	dt.turnAnglePID(-90 * chgAngle);
	dt.moveHorizontalPID(24);
	dt.turnAnglePID(-90 * chgAngle);
	delay(100);
	intk.autonSpinCont();
	delay(500);
	intk.autonStopCont();
	
	//Second Phase of right mode: 2 alliance color rings & 1 stake
	dt.turnAnglePID(8.3 * chgAngle);
	intk.autonSpinCont();
	dt.moveHorizontalPID(24.25);
	delay(1000);
	dt.moveHorizontalPID(-24.25);
	dt.turnAnglePID(-16.6 * chgAngle);
	dt.moveHorizontalPID(24.25);
	delay(1000);
	dt.moveHorizontalPID(-24.25);
	dt.turnAnglePID(-81.7 * chgAngle);
	dt.moveHorizontalPID(24);
	intk.autonStopCont();
	clamp.toggleClampLock();
	dt.moveHorizontalPID(24);
	}
//Skills auton sequence
void skills_auton(){
	//First Sector
	dt.moveHorizontalPID(-6); 
	clamp.toggleClampLock();
	intk.autonSpinCont();
	delay(500);
	dt.moveHorizontalPID(-9);
	dt.turnAnglePID(90);
	dt.moveHorizontalPID(24);
	delay(500);
	dt.moveHorizontalPID(12);
	delay(500);
	dt.moveHorizontalPID(-12);
	dt.turnAnglePID(-90);
	dt.moveHorizontalPID(12);
	delay(500);
	dt.turnAnglePID(180);
	dt.moveHorizontalPID(36);
	delay(500);
	dt.turnAnglePID(90);
	dt.moveHorizontalPID(24);
	delay(500);
	dt.moveHorizontalPID(-36);
	dt.turnAnglePID(-90);
	dt.moveHorizontalPID(24);
	delay(500);
	intk.autonStopCont();
	dt.turnAnglePID(153.4);
	dt.moveHorizontalPID(26.8);
	dt.turnAnglePID(26.6);
	dt.moveHorizontalPID(24);
	dt.turnAnglePID(-135);
	dt.moveHorizontalPID(-33);
	clamp.toggleClampLock();

	//Second Sector
	dt.moveHorizontalPID(67);
	intk.autonSpinCont();
	dt.moveHorizontalPID(34);
	delay(100);
	dt.turnAnglePID(90);
	dt.moveHorizontalPID(34);
	delay(100);
	dt.turnAnglePID(-45);
	dt.moveHorizontalPID(24);
	delay(100);
	dt.turnAnglePID(90);
	dt.moveHorizontalPID(24);
	delay(100);
	dt.moveHorizontalPID(12);
	delay(100);
	dt.moveHorizontalPID(-12);
	dt.turnAnglePID(-90);
	dt.moveHorizontalPID(12);
	delay(100);
	dt.moveHorizontalPID(-12);
	dt.turnAnglePID(-135);
	dt.moveHorizontalPID(-33);
	clamp.toggleClampLock();
	dt.moveHorizontalPID(33);
	dt.turnAnglePID(45);
	}

void auton_vision_intake(){
	int sig = NAN_SIG_id;
	screen::print(pros::E_TEXT_MEDIUM, 4, "Running the TASK - %s", (intk.intake_vision_state)?"TRUE":"FALSE");
	if (intk.intake_vision_state == true){
		sig = vision_sense.detect_color();
		if ((sig == BLUE_SIG_id) && (isBlue == false)){intk.visionIntake();} 
		else if ((sig == RED_SIG_id) && (isBlue == true)){intk.visionIntake();}
		else {intk.contSpin(100);}
	} 
	else {intk.contSpin(0);}

	screen::print(pros::E_TEXT_MEDIUM, 1, "Signature: %d", sig);
	delay(20);
}

//Initializing the Task to run the auton vision intake
Task auton_intk(auton_vision_intake);

void test_auton(){
	clamp.toggleClampLock();
	delay(2000);
	intk.autonSpinCont();
	delay(60000);
	intk.autonStopCont();
}
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

	//test_auton();

	if (isSkills == false){
		//Change direction based on alliance color
		int chgAngle = (isBlue == true) ? 1 : -1;
		
		if(winPointSide == true) {win_advanced_auton(chgAngle);}
		else{basic_auton();}
		//else {score_advanced_auton(chgAngle);}

	} else if (isSkills == true){
		skills_auton();
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
	int vision_sig = NAN_SIG_id;

	while (true) {
		//Calling DriveTrain System
		dt.teleMove();

		vision_sig = vision_sense.detect_color();
		if ((vision_sig == BLUE_SIG_id) && (isBlue == false)){intk.visionIntake();} 
		else if ((vision_sig == RED_SIG_id) && (isBlue == true)){intk.visionIntake();}

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