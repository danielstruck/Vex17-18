#include "Sensors.h"
#include "Misc_Template.h"
#include "Auton.h"
#include "Motors.h"
//include "vision.h"
void doAuton() {
	// decide if we are blue or red
	//static int startPosition = getStartPosition();
//rotateTo(90);
	if(getStartPosition() == BLUE) {
		blueAuton();
	} else {
		redAuton();
	}
	//scanForVisionTarget(1);
//	rotateTo(90);
	//while(1) {
	//}
}
void blueAuton() {
	retrieveMobile();
	moveToFeederStation();
	depositFirstStack();
}
void redAuton() {
	retrieveMobileRed();
	moveToFeederStationRed();
	depositFirstStackRed();
}
int getStartPosition() {
//	if (SensorValue[startModeJumper])
//		return RED;
	return BLUE;
}

void retrieveMobile() {
leftWheels(DRIVE_BACKWARD);
delay(600);
leftWheels(0);
strafeWheel(127);
delay(500);
strafeWheel(-127);
delay(50);
strafeWheel(0);
strafeWheel(45);
moveIn(-41);
strafeWheel(0);
strafeWheel(-127);
delay(300);
strafeWheel(0);
delay(500);
coneArmSpeed(CONE_ARM_DOWN);
delay(2000);
coneArmSpeed(0);
//	resetGyro();
lowerBase();
//leftWheels(-DRIVE_BACKWARD*.6);
delay(800);
leftWheels(0);
moveIn(-25);

raiseBase();
coneArmSpeed(CONE_ARM_UP*.8);
delay(2000);
coneArmSpeed(0);
strafeWheel(127);
delay(500);
//strafeWheel(-127);
//delay(1000);
strafeWheel(0);
//coneClawSpeed(CONE_CLAW_OPEN);
//delay(200);
//coneArmSpeed(CONE_ARM_DOWN);/
//delay(500);
//coneClawS
}
void retrieveMobileRed() {
	rightWheels(DRIVE_BACKWARD);
	delay(600);
	rightWheels(0);
	strafeWheel(-127);
	delay(500);
	strafeWheel(127);
	delay(50);
	strafeWheel(0);
	strafeWheel(-45);
	moveIn(-41);
	strafeWheel(0);
	strafeWheel(127);
	delay(300);
	strafeWheel(0);
	delay(500);
	coneArmSpeed(CONE_ARM_DOWN);
	delay(2000);
	coneArmSpeed(0);
	//	resetGyro();
	lowerBase();
	delay(800);
	leftWheels(0);
	moveIn(-25);

	raiseBase();
	coneArmSpeed(CONE_ARM_UP*.8);
	delay(2000);
	coneArmSpeed(0);
	strafeWheel(-127);
	delay(500);
	strafeWheel(0);
}

void stackConeFromGround() {
//coneArmSpeed(CONE_ARM_UP);
//	delay(750);
//	coneArmSpeed(CONE_ARM_DOWN * .1);
}

void moveToFeederStation() {
	moveIn(16);
	rotateTo(120);
	delay(500);
	moveIn(-18);
	//strafeWheel(60);
	//moveIn(24);
	//strafeWheel(0);
	//delay(500);
	//rotateTo(135);
	//delay(500);
	//moveIn(-10);
	coneClawSpeed(CONE_CLAW_OPEN);
	delay(200);
	coneArmSpeed(CONE_ARM_DOWN*.9);
	delay(500);
	coneClawSpeed(0);
	delay(1000);
	coneClawSpeed(CONE_CLAW_OPEN);
	//coneArmSpeed(0);
	delay(250);
	coneClawSpeed(0);
	//coneArmSpeed(CONE_ARM_UP*.1);
	coneArmSpeed(0);
}
void moveToFeederStationRed() {
	moveIn(16);
	rotateTo(-120);
	delay(500);
	moveIn(-18);
	//strafeWheel(60);
	//moveIn(24);
	//strafeWheel(0);
	//delay(500);
	//rotateTo(135);
	//delay(500);
	//moveIn(-10);
	coneClawSpeed(CONE_CLAW_OPEN);
	delay(200);
	coneArmSpeed(CONE_ARM_DOWN*.9);
	delay(500);
	coneClawSpeed(0);
	delay(1000);
	coneClawSpeed(CONE_CLAW_OPEN);
	//coneArmSpeed(0);
	delay(250);
	coneClawSpeed(0);
	//coneArmSpeed(CONE_ARM_UP*.1);
	coneArmSpeed(0);
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
//	coneClawSpeed(CONE_CLAW_OPEN);
}

void depositFirstStack() {
	rotateTo(180);

	moveIn(-40);
	delay(1000);
	driveStraight(DRIVE_BACKWARD);
	delay(1000);
	driveStraight(0);
	//lowerBase();

//	moveIn(12);
}
void depositFirstStackRed() {
	rotateTo(180);

	moveIn(-40);
	delay(1000);
	driveStraight(DRIVE_BACKWARD);
	delay(1000);
	driveStraight(0);
	//lowerBase();

//	moveIn(12);
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
	goalArmSpeed(GOAL_ARM_DOWN);
	delay(550);
	goalArmSpeed(0);
}

void raiseBase() {
	while(!getGoalLiftBump()) {
		goalArmSpeed(GOAL_ARM_UP);
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
