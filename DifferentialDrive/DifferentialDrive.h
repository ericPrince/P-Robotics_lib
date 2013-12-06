/*----------------------------------------------------------------
	Princeton Robotics Club, Princeton University 2013
	
	Differential Drive Library (Arduino C++)
	
	This library is for use with Arduino and 2 H-Bridges.  It
	treats the H-Bridges as the 2 motors in a differential drive
	system.
	
	Inputs to arcade and tank drive must lie in the range [-1, 1].

----------------------------------------------------------------*/


#ifndef MotorOutput_h
#define MotorOutput_h

#include <HBridge.h>

class DifferentialDrive{
	public:
		// constructor
		DifferentialDrive(int leftPins[3], int rightPins[3], bool invert[2]);
		
		// send standard arcade drive instructions
		void arcade(double straight, double turn);
		// send standard tank drive instructions
		void tank(double left, double right);
		// stop both motors
		void stop();
		// return the output speed of the left motor
		double getLeft();
		// return the output speed of the right motor
		double getRight();
		// set the deadband for both motors [0, 255]
		double raw_setDeadband(int db);
	
	private:
		// H-Bridge objects that represent each motor
		HBridge leftMotor, rightMotor;
};

#endif 