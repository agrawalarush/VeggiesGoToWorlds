#include "main.h"
#include "robotConfigs.h"
//This file helps save autons!!!

//This auton is for one sie but i don't remember which lol
void fourPlusThree() {
    chassis.setPose(0,0,0);

	chassis.moveToPose(3.14,27,17.25, 2000, {.minSpeed=50},false);//close to blocks
	chassis.moveToPose(6, 33, 17.25, 1000);//pick up blocks (needs tuning)
	limiter.set_value(true);
	intake(127);
	//matchloader.set_value(true);
	//chassis.moveToPose(5.5, 32.5, 129.75, 500 ,{.forwards=false}); (old good for alignment)
	pros::delay(2000);
	intake(0);
	chassis.moveToPose(-12, 45, 140, 2000, {.forwards=false},false); //(perfect alignment to midgoal)
	midscore.set_value(true);
	limiter.set_value(false);
	intake(127);
	pros::delay(1000);
	intake(0);
};