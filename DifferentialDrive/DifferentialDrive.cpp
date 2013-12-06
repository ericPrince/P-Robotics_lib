#include <Arduino.h>

// constructor
DifferentialDrive(int leftPins[3], int rightPins[3], bool invert[2]) :
	leftMotor(leftPins[0], leftPins[1], leftPins[2], invert[0]), 
	rightMotor(rightPins[0], rightPins[1], rightPins[2], invert[1])
{}
		
// send standard arcade drive instructions
void arcade(double straight, double turn) {
	double y = abs(straight);
	double x = abs(turn);
  
	double right;
	double left;
  
	if (turn >= 0){
		left  = y - x;
		right = max(x, y);
	}
	else{
		left  = max(x, y);
		right = y - x;
	}
  
	if(straight < 0){
		left  *= -1;
		right *= -1;
	}
  
	tank(left, right);
}
// send standard tank drive instructions
void tank(double left, double right) {
	leftMotor.setSpeed(left);
	rightMotor.setSpeed(right);
}
// stop both motors
void stop() {
	leftMotor.stop();
	rightMotor.stop();
}
// return the output speed of the left motor
double getLeft() {
	return leftMotor.getSpeed();
}
// return the output speed of the right motor
double getRight() {
	return rightMotor.getRight();
}
// set the deadband for both motors [0, 255]
double raw_setDeadband(int db) {
	leftMotor.raw_setDeadband(db);
	rightMotor.raw_setDeadband(db);
}