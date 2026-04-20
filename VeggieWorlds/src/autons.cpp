#include "autons.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "robotConfigs.h"
//This file helps save autons!!!

//This auton is for one sie but i don't remember which lol
void fourPlusThreeRight() {
	chassis.setPose(0,0,0);
	chassis.moveToPose(0.5, 36/*42*/, 90, 1600,/*,1700*/ {.lead=0});//align to matchloader
	pros::delay(800);
	matchloader.set_value(true);
	pros::delay(800);
	chassis.moveToPoint(14, 36, 750, {.maxSpeed=90}, false);//move into matchloader
	left_motor_group.move_velocity(600); //keep moving
	right_motor_group.move_velocity(600);
	limiter.set_value(true);
	intake(200,600);
	pros::delay(1450);
	chassis.cancelAllMotions();
	chassis.moveToPoint(-25, 36, 900, {.forwards=false, .maxSpeed=70}); //move to goal
	pros::delay(500);
	intake_motor.move_velocity(-200);
	pros::delay(100);
	intake(200, 600);
	pros::delay(100);
	intake_motor.move_velocity(-200);
	pros::delay(100);
	intake(200, 600);
	left_motor_group.move_velocity(-600);//properly align
	right_motor_group.move_velocity(-600);
	limiter.set_value(false);
	pros::delay(700);
	intake(-200, 600);
	pros::delay(300);
	intake(200,600); //antijam
	pros::delay(200);
	matchloader.set_value(false);
	pros::delay(1300);
	chassis.cancelAllMotions();
	chassis.moveToPoint(-16, 36, 500,{.minSpeed=30, .earlyExitRange=5},false); //Move out of long goal
	outake_motor.brake();
	chassis.moveToPose(-31.7, 8, -218.5, 1500, {.lead=0,.maxSpeed=50}, false); //collect cluster of 3 blocks
	pros::delay(500);
	chassis.moveToPose(-39.8, 0.5, 228, 1200,{.maxSpeed=60}); //align to bottom goal
	pros::delay(500);
	intake_motor.move_velocity(-200);
	pros::delay(200);
	intake_motor.move_velocity(200);
	pros::delay(500);
	intake(-200, -600);
	pros::delay(1000);
	chassis.moveToPose(-24.2, 23.8, 95, 1000, {.forwards=false,.lead=0.5,.minSpeed=40,.earlyExitRange=3}, false); //move to align wing
	left_motor_group.set_brake_mode_all(pros::MotorBrake::hold);
	right_motor_group.set_brake_mode_all(pros::MotorBrake::hold);
	chassis.moveToPose(-40.4, 25, 85, 20000,{.forwards=false,.lead=0,.minSpeed=127},false);
}

void sevenBlockLeft() {
	chassis.setPose(0, 0, 0);
	chassis.swingToHeading(59, lemlib::DriveSide::LEFT, 500,{},true);//turn to center blocks
	limiter.set_value(true);
	pros::delay(100);
	intake(200, 600);
	chassis.moveToPose(28, 12,62, 3000, {.lead=0.2,.maxSpeed=70},false);//collect center blocks
	left_motor_group.move_voltage(10);
	chassis.turnToHeading(-60, 1000,{.maxSpeed=70},false);//turn to matchloader
	matchloader.set_value(true);
	chassis.moveToPose(-7, 38, -83.4, 1000,{.lead=0},false);//align to matchloader
	chassis.moveToPose(-16, 38, -83.4, 500,{.lead=0,.minSpeed=127},false);//move into matchloader
	left_motor_group.move_velocity(50);
	right_motor_group.move_velocity(50);
	pros::delay(500);
	chassis.cancelAllMotions();
	pros::delay(400);
	chassis.moveToPose(15.8, 39, -86, 900,{.forwards=false,.lead=0});//move into goal
	pros::delay(500);
	intake_motor.move_velocity(-200);
	pros::delay(100);
	intake(200, 600);
	intake_motor.move_velocity(-200);
	pros::delay(100);
	intake(200, 600);
	pros::delay(200);
	left_motor_group.move_velocity(-600);//properly align
	right_motor_group.move_velocity(-600);
	limiter.set_value(false);
	pros::delay(500);
	intake(-200, -600);
	pros::delay(300);
	intake(200,600); //antijam
	pros::delay(200);
	matchloader.set_value(false);
	pros::delay(1400);
	chassis.cancelAllMotions();
	chassis.moveToPose(2.54, 49.5, -82.44, 1100);
	chassis.turnToHeading(-90.5, 500);
	chassis.moveToPose(31.5, 49.5,-89.5, 1000,{.forwards=false,.lead=0,.minSpeed=127},false);
}	

void tune() {
	chassis.setPose(0, 0, 0);
	chassis.moveToPose(0,0,0, 20000);
}