#include "Motors.h"
#include "Controller_Template.h"
#include "Sensors.h"

void doTeleop() {
	// (up, down)
 	coneArmControl(getP5U(), getP5D());
 	// (open, close)
 	coneClawControl(getP6D(), getP6U());
	// (up, down)
 	goalArmControl1(getB6U(), getB6D());
  // (left x-axis, left y-axis, right x-axis, right y-axis)
 	wheelControl(getLJoyX(), getLJoyY(), getRJoyX(), getRJoyY());
 	// (open, close)
 	pusherControl(getB5U(), getB5D());
}

void coneArmControl(const bool moveUp, const bool moveDown) {
	if(moveUp) {
		coneArmSpeed(CONE_ARM_UP);
	}
	else if(moveDown) {
		coneArmSpeed(CONE_ARM_DOWN);
	}
	else {
		if(getArmPosition() < CONE_ARM_HIGH)
			coneArmSpeed(CONE_ARM_UP * .1);
		else
			coneArmSpeed(CONE_ARM_DOWN * .1);
	}
}

void wheelControl(int leftXAxis, int leftYAxis, int rightXAxis, int rightYAxis) {
  const int threshhold = 10;

	/* -Tank- */
	//rightWheels((getRJoyY() * multiplier) * .5);
	//leftWheels(getLJoyY() * multiplier);
	//if(getB8L())
	//	strafeWheel(STRAFE_RIGHT * multiplier);
	//else if(getB7R())
	//	strafeWheel(STRAFE_LEFT * multiplier);
	//else
	//	strafeWheel(0);

	/* -Arcade- */
	rightWheels(leftYAxis - rightXAxis);
	leftWheels(leftYAxis + rightXAxis);
	if(abs(leftXAxis) > threshhold)
		strafeWheel(-leftXAxis);
	else
		strafeWheel(0);
}

void goalArmControl1(const bool moveUp, const bool moveDown) {
	if(moveUp)
		goalArmSpeed(GOAL_ARM_UP);
	else if(moveDown)
		goalArmSpeed(GOAL_ARM_DOWN);
	else
		goalArmSpeed(0);
}

void coneClawControl(const bool open, const bool close){
	//static bool toggleState = true, clawClosed = false;
	//if(toggleState && getB6D()) {
	//	toggleState = false;
	//	if(clawClosed) {
	//		clawSpeed(0);
	//		clawClosed = false;
	//	}
	//	else {
	//		clawSpeed(CLAW_CLOSE * multiplier);
	//		clawClosed = true;
	//	}
	//}
	//else if(!getB6D())
	//	toggleState = true;

	if(open)
		coneClawSpeed(CONE_CLAW_OPEN);
	else if(close)
		coneClawSpeed(CONE_CLAW_CLOSE);
	else
		coneClawSpeed(0);
}

void pusherControl(const bool open, const bool close) {
	if (open)
		goalPusherSpeed(GOAL_PUSHER_OPEN);
	else if (close)
		goalPusherSpeed(GOAL_PUSHER_CLOSE);
	else
		goalPusherSpeed(0);

}
