#include "Misc_Template.h"
#include "Sensors.h"
#include "Motors.h"

int getGyro(void) {
	return SensorValue[Gyro];
}

int getGoalLiftBump() {
	return SensorValue[GoalLiftBump];
}

int getArmPosition() {
	return SensorValue[ArmEncoder];
}

void moveArmToPosition(int pos) {
	static const int threshhold = 10;

	const int dir = sign(pos - getArmPosition());
	coneArmSpeed(CONE_ARM_UP * dir);
	while (abs(pos - getArmPosition()) > threshhold)
		delay(10);

	coneArmSpeed(CONE_ARM_DOWN * dir * .3);
	delay(150);
	coneArmSpeed(0);
}

void moveIn(float inches) {
inches /= 2;
	SensorValue[EncoderLeft] = 0;
	SensorValue[EncoderRight] = 0;

	unsigned int threshhold = 1; // function tries to keep encoder values within +-threshhold
	float fastWheelMultiplier = .5; // lower values straiten "faster": .9 usualy good
	float rotReq = (inches / WHEEL_CIRCUMFERENCE) * ENCODER_VALUE_PER_REV; // calcuate required encoder value - CAREFUL NOT TO
																																//   OVERFLOW DOUBLE
	int speed = DRIVE_FORWARD * sign(inches); // full speed in direction traveling

	driveStraight(speed);
	int encoderL, encoderR;
	do {
		encoderL = abs(SensorValue[EncoderLeft]);
		encoderR = abs(SensorValue[EncoderRight]);

		// Check to see if robot is no longer going strait
		if(encoderR - encoderL < threshhold) {// left wheels fast
			// slow down left side to straiten out
			leftWheels(speed);
			rightWheels(speed * fastWheelMultiplier);
			writeDebugStreamLine("left");
		}
		else if(encoderL - encoderR < threshhold) {// right wheel fast
			leftWheels(speed * fastWheelMultiplier);
			// slow down right side to straiten out
			rightWheels(speed);
			writeDebugStreamLine("right");
		}
		else {// robot going strait enough
			leftWheels(speed);
			rightWheels(speed);
			writeDebugStreamLine("straight");
		}

		wait10Msec(5);// let other tasks get some time
	} while((encoderL + encoderR)/2 < abs(rotReq));
	driveStraight(-speed);
	delay(50);
	driveStraight(0);
}

void strafeIn(float inches) {
	SensorValue[EncoderStrafe] = 0;

	const unsigned int threshhold = 10; // function tries to keep encoder values within +-threshhold
	const float fastWheelMultiplier = .9; // lower values straiten "faster": .9 usualy good
	const double rotReq = (inches / WHEEL_CIRCUMFERENCE) * ENCODER_VALUE_PER_REV;
	const int speed = DRIVE_FORWARD * sign(inches);

	strafeWheel(speed);
	int encoderVal;
	do {
		encoderVal = abs(SensorValue[EncoderStrafe]);
		wait10Msec(5);// let other tasks get some time
	} while(encoderVal < abs(rotReq));
	strafeWheel(-speed);
	delay(50);
	strafeWheel(0);
}

int applyDampening(int input) {
	// 															applies equation:
  //
	// (127 - minSpeed) (input / (slowAt*10))^(2*abruptness+1) + minSpeed * sign(input)


	const static unsigned int minSpeed   = 20; // speed will never be lower than this number
	const static unsigned int abruptness = 1;  // power of equation (how quickly the robot will slow down - positive, non-zero integers only)
	const static unsigned int slowAt		 = 10; // horizontal strech (degrees at which the robot will start to slow down)

	int result = input;

	// apply slowAt
	result /= slowAt*10; // simulates (result / slowAt); (slowAt*10) to scale to getGyro()

	// apply abruptness
	for (int i = 0; i < 2*abruptness+1; i++) // simulates (result^abruptness); (2*abruptness+1) to get odd powers
		result *= result;

	// squash the function horizontally for "nice numbers"
	result *= 127 - minSpeed; // simulates ((127 - minSpeed) * result)

	// add on the minimum speed, signed for turning CW or CCW
	result += minSpeed * sign(input); // simulates (result + minSpeed * (input / abs(input)))

	return result;
}
void rotateTo(float targetDeg) {
	const static unsigned float threshhold = 1; // max error in degrees (how many degrees off is "good enough"?)

	int distCCW;
	int distCW;
	int shortestDist;
	int speed;

	while (abs(getGyro() - targetDeg) > threshhold*10) { // (threshhold*10) to scale to getGyro()
		distCCW			 = 3600 - targetDeg;
		distCW  		 = targetDeg - getGyro();
		shortestDist = min(distCCW, distCW); // calculate shortest path
		speed				 = applyDampening(shortestDist);

		leftWheels(speed);
		rightWheels(-speed);
	}

	leftWheels(-speed);
	rightWheels(speed);
}
