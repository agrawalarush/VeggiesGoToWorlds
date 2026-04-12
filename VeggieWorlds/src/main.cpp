#include "main.h"
#include "robotConfigs.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
// initialize function. Runs on program startup
void initialize() {
    //Remember to set break modes   
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
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
bool midscore_pressed = false;
bool wing_pressed = false;
// bool matchloader_pressed = false;
// bool limiter_pressed = false;

void opcontrol() {
    // loop forever
    while (true) {
        /*Tank drive:
		// get left y and right y positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // move the robot
        chassis.tank(leftY, rightY);*/
		
		// get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);

	 	// ---------------------------
     	// INTAKE
     	// ---------------------------
     	if (controller.get_digital(DIGITAL_R1))
     	    intake_motor.move(-127);
     	else if (controller.get_digital(DIGITAL_L1))
     	    intake_motor.move(127);
     	else
     	    intake_motor.brake();

        // ---------------------------
        // OUTAKE
     	// ---------------------------
     	if (controller.get_digital(DIGITAL_R2))
     	    outake_motor.move(-127);
     	else if (controller.get_digital(DIGITAL_L2))
     	    outake_motor.move(127);
     	else
     	    outake_motor.brake();

	
     	// WING TOGGLE
     	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) && !wing_pressed) {
     	    wing_state = !wing_state;
     	    wing.set_value(wing_state);
     	    wing_pressed = true;
     	}
     	if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
     	    wing_pressed = false;

		// MIDSCORE TOGGLE
     	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) && !midscore_pressed) {
     	    midscore_state = !midscore_state;
     	    midscore.set_value(midscore_state);
     	    midscore_pressed = true;
     	}
     	if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
     	    midscore_pressed = false;
	
        // delay to save resources
        pros::delay(25);
    }
}