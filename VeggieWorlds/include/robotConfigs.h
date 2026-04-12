#ifndef _PROS_ROBOT_CONFIG_H_
#define _PROS_ROBOT_CONFIG_H_
#include "main.h"
#include "lemlib/api.hpp"


//drivetrain
extern pros::MotorGroup left_motor_group;
extern pros::MotorGroup right_motor_group;
extern lemlib::Chassis chassis;

extern pros::Motor outake_motor;
extern pros::Motor intake_motor;
//pneumatics
extern pros::adi::DigitalOut wing;
extern pros::adi::DigitalOut midscore;

extern bool wing_state;
extern bool midscore_state;
//extern bool matchloader_state;
//extern bool limiter_state;

extern pros::Imu imu;
extern pros::Rotation perpendicular_encoder;
extern pros::Rotation parallel_encoder;

extern pros::Controller controller;

#endif