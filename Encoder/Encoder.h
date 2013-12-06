/*----------------------------------------------------------------
	Princeton Robotics Club, Princeton University 2013
	
	Encoder Library (Arduino C++)
	
	This is a library for use with quadrature rotary encoders.
	Functions allow the user to get the distance, count, and
	speed of the encoder.
	
	The most important function is encoderEvent, which must be
	attached to a hardware interrupt.  This can only be done in
	the main arduino code.  Here is an example of how:
	
	#include <Encoder.h>
	...
	int pinA = 0;
	int pinB = 1;
	Encoder myEncoder(pinA, pinB, 2.5, 100, false);
	...
	setup(void) {
		attachInterrupt(pinA, encoderEventA, CHANGE);
		attachInterrupt(pinB, encoderEventB, CHANGE);
	}
	...
	// interrupt service routines
	void encoderEventA() {
		myEncoder.encoderEvent(ENCODER_EVENT_A);
	}
	void encoderEventB() {
		myEncoder.encoderEvent(ENCODER_EVENT_B);
	}
	
	Note that 2 interrupts are needed because of the quadrature
	signal.  A change in reading of either pin should cause the
	encoder to update (thus quadrature).

----------------------------------------------------------------*/

#ifndef Encoder_h
#define Encoder_h

#include <Arduino.h>

// pass these to encoderEvent depending on the interrupt pin
const bool ENCODER_EVENT_A = true;
const bool ENCODER_EVENT_B = false;

class Encoder{
	private:
		volatile double speed; // wheel speed
		volatile int count; // encoder count
		volatile int lastTime; // last calculation time
		volatile int p1, p2, p3, p4, p5; // averaging var holders
		volatile bool invert; // invert direction if true
  
		double distancePerCount; // distance per encoder count
		int pinA, pinB, timeout; // pins and max time b/n pulses

	public:
		// constructor
		Encoder(int pa, int pB, double distPerCount, int t, bool invertDir);
  
		// get distance travelled by wheel
		double getDistance();
		// get wheel speed
		double getSpeed();
		// get encoder count
		double getCount();
		// reset encoder position to 0
		void reset();
		// get distance travelled per encoder count
		double getDistancePerCount();
		// returns true if the wheel is stopped
		bool isStopped();
		// get spinning direction: 1=forward, -1=reverse, 0=stopped
		int getDirection();
		
		// update count, distance, and speed. handle this in a hardware interrupt
		void encoderEvent(bool mode);
};

#endif