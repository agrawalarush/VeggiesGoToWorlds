#include "main.h"
#include "robotConfigs.h"

// left motor group
pros::MotorGroup left_motor_group({-17, -18, 19}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_motor_group({1, -2, 3}, pros::MotorGears::blue);


// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              11, // 11 inch track width
                              lemlib::Omniwheel::NEW_325, // drivetrain wheel type is new 3.25inch omniwheel
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
pros::Rotation parallel_encoder(-13);


// horizontal tracking wheel
lemlib::TrackingWheel parallel_tracking_wheel(&parallel_encoder, lemlib::Omniwheel::NEW_2, -1);
// vertical tracking wheel
lemlib::TrackingWheel perpendicular_tracking_wheel(&perpendicular_encoder, lemlib::Omniwheel::NEW_2, -4.5);

// odometry settings
lemlib::OdomSensors sensors(&parallel_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &perpendicular_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(5.8, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              1, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // 22 proportional gain (kP)
                                              0, // integral gain (kI)
                                              15.7, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
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
pros::adi::DigitalOut limiter('G');
pros::adi::DigitalOut matchloader('F');

bool limiter_state = false;
bool matchloader_state = false;
bool midscore_state = false;
bool wing_state = true;

//controler
pros::Controller controller(pros::E_CONTROLLER_MASTER);