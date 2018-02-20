#include "Sensors.h"
#include "Misc_Template.h"
#include "Auton.h"
#include "Motors.h"
//include "vision.h"
void doAuton() {
	// decide if we are blue or red
	//static int startPosition = getStartPosition();

	retrieveMobile();

	///* stack preload */
	//stackConeFromGround();

	//moveToFeederStation();
	//lowerBase();
	//for (int i = 0; i < 3; i++)
	//	stackConeFromFeeder();
	//depositFirstStack();
	//scanForVisionTarget(1);
	rotateTo(90);
	//while(1) {
	//}
}

int getStartPosition() {
//	if (SensorValue[startModeJumper])
		return RED;
	return BLUE;
}

void retrieveMobile() {
	//turnForDegrees(35, RIGHT_TURN);
rotateTo(45);
//moveIn(66);

//	rotateTo(45);

//	lowerBase();

//	moveIn(-24);

	//raiseBase();
}

void stackConeFromGround() {
//coneArmSpeed(CONE_ARM_UP);
//	delay(750);
//	coneArmSpeed(CONE_ARM_DOWN * .1);
}

void moveToFeederStation() {
	moveIn(12);

	//turnForDegrees(180, RIGHT_TURN);

	strafeIn(24*sign(STRAFE_RIGHT));

	moveIn(24);
}

void stackConeFromFeeder() {
	//setArmToFeeder();
	for(int i = 0; i < 5; i++) {
	coneClawSpeed(CONE_CLAW_OPEN);
	delay(1000);
	coneClawSpeed(0);
	delay(300);
	coneArmSpeed(CONE_ARM_UP);
	delay(1200);
	coneArmSpeed(0);
	delay(750);
	coneClawSpeed(CONE_CLAW_OPEN);
	delay(300);
	coneArmSpeed(CONE_ARM_DOWN);
	delay(400);
	coneClawSpeed(0);
	delay(1000);
	coneArmSpeed(0);
	delay(700);
	coneArmSpeed(CONE_ARM_UP * .2);
  }
	//coneArmSpeed(CONE_ARM_UP * .2);
	//while(1);
}
void setArmToFeeder() {
	coneArmSpeed(CONE_ARM_UP);
	delay(500);
	coneArmSpeed(CONE_ARM_UP * .2);
	coneClawSpeed(CONE_CLAW_OPEN);
}

void depositFirstStack() {
	rotateTo(-45);

	moveIn(-70);

	lowerBase();

	moveIn(12);
}

void turnForDegrees(double angle) {
	angle = angle * 10;
	//while(1) {
	//	writeDebugStreamLine("%i", getGyro());
	//}
	while(getGyro() < angle) {
		leftWheels(50);
		rightWheels(-50);
	}
	while(getGyro() > angle) {
		leftWheels(-50);
		rightWheels(50);
	}
}

void lowerBase() {
	goalArmSpeed(GOAL_ARM_UP);
	delay(400);
	goalArmSpeed(0);
}

void raiseBase() {
	while(!getGoalLiftBump()) {
		goalArmSpeed(GOAL_ARM_DOWN);
	}
	goalArmSpeed(0);
}
void placeBase() {
	goalArmSpeed(GOAL_ARM_DOWN);
	delay(400);
	goalArmSpeed(0);
	delay(400);
	goalPusherSpeed(GOAL_PUSHER_OPEN);
	delay(1000);
	goalPusherSpeed(GOAL_PUSHER_CLOSE);
	delay(1000);
	goalPusherSpeed(0);
}
