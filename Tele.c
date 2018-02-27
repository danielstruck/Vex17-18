#include "Motors.h"
#include "Controller_Template.h"
#include "Sensors.h"

void doTeleop() {
	float multMain = (getB7D() || getB8D())?
					 0.5:
					 1;
	float multPartner = (getP7D() || getP8D())?
						0.5:
						1;
	// (up, down)
 	coneArmControl(getP5U(), getP5D(), getP7L(), multMain);
 	// (open, close)
 	coneClawControl(getP6D(), getP6U(), multMain);
	// (up, down)
 	goalArmControl1(getB6U(), getB6D(), multMain);
  // (left x-axis, left y-axis, right x-axis, right y-axis)
 	wheelControl(getLJoyX(), getLJoyY(), -getRJoyX(), getRJoyY(), multMain);
 	// (open, close)
 	pusherControl(getB5U(), getB5D(), multMain);
}

void coneArmControl(const bool moveUp, const bool moveDown, const bool lockArm, const float multiplier) {
	if(moveUp) {
		coneArmSpeed(CONE_ARM_UP * multiplier);
	}
	else if(moveDown) {
		coneArmSpeed(CONE_ARM_DOWN * multiplier);
	}
	else if (lockArm) {
		if(getArmPosition() < CONE_ARM_HIGH)
			coneArmSpeed(CONE_ARM_UP * .1);
		else
			coneArmSpeed(CONE_ARM_DOWN * .1);
	}
	else {
		coneArmSpeed(0);
  }
}

float applyCurve(float input, int n) {
	return ipow(input, n)/ipow(127,n-1);
}
void wheelControl(int leftXAxis, int leftYAxis, int rightXAxis, int rightYAxis, const float multiplier) {
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

	rightWheels(applyCurve(leftYAxis - rightXAxis, 3) * multiplier);
	leftWheels(applyCurve(leftYAxis + rightXAxis, 3) * multiplier);
	if(abs(leftXAxis) > threshhold)
		strafeWheel(-leftXAxis * multiplier);
	else
		strafeWheel(0);
}

void goalArmControl1(const bool moveUp, const bool moveDown, const float multiplier) {
	if(moveUp)
		goalArmSpeed(GOAL_ARM_UP * multiplier);
	else if(moveDown)
		goalArmSpeed(GOAL_ARM_DOWN * multiplier);
	else
		goalArmSpeed(0);
}

void coneClawControl(const bool open, const bool close, const float multiplier){
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
		coneClawSpeed(CONE_CLAW_OPEN * multiplier);
	else if(close)
		coneClawSpeed(CONE_CLAW_CLOSE * multiplier);
	else
		coneClawSpeed(0);
}

void pusherControl(const bool open, const bool close, const float multiplier) {
	if (open)
		goalPusherSpeed(GOAL_PUSHER_OPEN * multiplier);
	else if (close)
		goalPusherSpeed(GOAL_PUSHER_CLOSE * multiplier);
	else
		goalPusherSpeed(0);

}
