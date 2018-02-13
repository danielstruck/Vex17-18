#include "Sensors.h"
#include "Misc_Template.h"
#include "Auton.h"

void doAuton() {
	// decide if we are blue or red
	static int startPosition = getStartPosition();

	retrieveMobile();

	/* stack preload */
	stackConeFromGround();

	moveToFeederStation();

	for (int i = 0; i < 3; i++)
		stackConeFromFeeder();

	depositFirstStack();
}

int getStartPosition() {
	if (SensorValue[dgtl1])
		return RED;
	return BLUE;
}

void retrieveMobile() {
	//turnForDegrees(35, RIGHT_TURN);

	moveIn(66);

	rotateTo(45);

	lowerBase();

	moveIn(-24);

	raiseBase();
}

void stackConeFromGround() {

}

void moveToFeederStation() {
	moveIn(12);

	//turnForDegrees(180, RIGHT_TURN);

	strafeIn(24*sign(STRAFE_RIGHT));

	moveIn(24);
}

void stackConeFromFeeder() {

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

}

void raiseBase() {

}
