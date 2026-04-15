#include "main.h"
#include "pros/rtos.hpp"
#include "robotConfigs.h"

//helper functions:
void intake(int speed // 127 for outtake, -127 for intake) 
){
	intake_motor.move(speed);
	outake_motor.move(speed);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
// initialize function. Runs on program startup
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    left_motor_group.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    right_motor_group.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    intake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    outake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %1.2f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %1.2f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %1.2f", chassis.getPose().theta); // heading
			// delay to save resources
            pros::delay(50);
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
void autonomous() {
    chassis.setPose(0,0,0);

	chassis.moveToPose(3.14,27,17.25, 2000, {.minSpeed=50},false);//close to blocks
	chassis.moveToPose(6, 33, 17.25, 1000);//pick up blocks (needs tuning)
	limiter.set_value(true);
	intake(127);
	//matchloader.set_value(true);
	//chassis.moveToPose(5.5, 32.5, 129.75, 500 ,{.forwards=false}); (old good for alignment)
	pros::delay(2000);
	intake(0);
	/*chassis.moveToPose(-12, 45, 140, 2000, {.forwards=false},false); (perfect alignment to midgoal)
	midscore.set_value(true);
	limiter.set_value(false);
	intake(127);
	pros::delay(1000);
	intake(0);*/
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
bool midscore_pressed = false;
bool wing_pressed = false;
bool matchloader_pressed = false;
bool limiter_pressed = false;

//break between haptics
bool haptics_cooldown = false;

void opcontrol() {
    // loop forever
    while (true) {
        //Tank drive:
		//get left y and right y positions
        /*int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
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
     	if (controller.get_digital(DIGITAL_L1))
     	    intake_motor.move(-127);
     	else if (controller.get_digital(DIGITAL_R1))
     	    intake_motor.move(127);
     	else
     	    intake_motor.brake();

        // ---------------------------
        // OUTAKE
     	// ---------------------------
     	if (controller.get_digital(DIGITAL_R2))
     	    outake_motor.move(127);
     	else if (controller.get_digital(DIGITAL_L2))
     	    outake_motor.move(-127);
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
     	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && !midscore_pressed) {
     	    midscore_state = !midscore_state;
     	    midscore.set_value(midscore_state);
     	    midscore_pressed = true;
     	}
     	if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
     	    midscore_pressed = false;

		//midscore haptics
		if (midscore_state and !haptics_cooldown) {
			controller.rumble("."); // short rumble when midscore is active
			haptics_cooldown = true;
		} else {
			haptics_cooldown = false;
		}
    
        // limiter TOGGLE
     	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) && !limiter_pressed) {
     	    limiter_state = !limiter_state;
     	    limiter.set_value(limiter_state);
     	    limiter_pressed = true;
     	}
     	if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
     	    limiter_pressed = false;
		
		if (limiter_state and !haptics_cooldown) {
			controller.rumble("--");
		} else {
			haptics_cooldown = false;
		};
		/*//limiter controller screen status show
		if (limiter_state) {
			controller.print(3, 0, "Limiter: ON");
		} else if (!limiter_state) {
			controller.print(3, 0, "Limiter: OFF");
		} else {
			controller.clear()
		}*/

		 // matchloader TOGGLE
     	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) && !matchloader_pressed) {
     	    matchloader_state = !matchloader_state;
     	    matchloader.set_value(matchloader_state);
     	    matchloader_pressed = true;
     	}
     	if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
     	    matchloader_pressed = false;

        // delay to save resources
        pros::delay(25);
    }
}
