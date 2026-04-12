#include "main.h"
#include "robotConfigs.h"

// left motor group
pros::MotorGroup left_motor_group({-17, -18, 19}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_motor_group({1, -2, 3}, pros::MotorGears::blue);


// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // tracking wheel type is new 3.25inch omniwheel
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);
//top motor
pros::Motor outake_motor(11, pros::MotorGears::blue);
//flexwheel intake
pros::Motor intake_motor(6, pros::MotorGears::green);

// imu
pros::Imu imu(12);
//tracking rotation sensors
pros::Rotation perpendicular_encoder(14);
pros::Rotation parallel_encoder(13);

//have to measure offset and trackwidth

// horizontal tracking wheel
lemlib::TrackingWheel parallel_tracking_wheel(&parallel_encoder, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel
lemlib::TrackingWheel perpendicular_tracking_wheel(&perpendicular_encoder, lemlib::Omniwheel::NEW_275, -2.5);

// odometry settings
lemlib::OdomSensors sensors(&perpendicular_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &parallel_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);


// PNEUMATICS
pros::adi::DigitalOut wing('A');
pros::adi::DigitalOut midscore('H');
//pros::adi::DigitalOut limiter('B');
//pros::adi::DigitalOut matchloader('C');

//bool limiter_state = false;
//bool matchloader_state = false;
bool midscore_state = false;
bool wing_state = true;

//controler
pros::Controller controller(pros::E_CONTROLLER_MASTER);