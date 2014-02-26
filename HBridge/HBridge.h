 /*----------------------------------------------------------------
	Princeton Robotics Club, Princeton University 2013
	
	H-Bridge Library (Arduino C++)
	
	This library is for use with Arduino and any standard
	H-Bridge.  The library is geared towards motor control, as
	functions exist for setting speed and direction as well as
	braking and coasting.
	
	When using this library, keep in mind that the motor will
	always be running with the last set values from this library,
	even if it has been a long time since the last function call.
	
	For reference, a commonly used double H-Bridge is the SN754410:
	http://www.ti.com/lit/ds/symlink/sn754410.pdf

----------------------------------------------------------------*/

#ifndef HBridge_h
#define HBridge_h

// motor direction values
enum {M_FWD = 1, M_STOP = 0, M_BACK = -1};
// H-Bridge stop modes
enum {HB_BRAKE = 0, HB_COAST = 1};

class HBridge{
	public:
		// constructor
		HBridge(int pinA, int pinB, int pinPWM, bool invert);
		
		// set raw direction and speed values
		void setRaw(int direction, int pwm);
		// set speed in range [-1, 1]
		void setSpeed(double speed);
		// tell the motor to stop
		void stop();
		// assign BRAKE or COAST mode for the H-Bridge
		void setStopMode(int mode);
		
		// get motor direction (1, 0, or -1)
		int getDirection();
		// get motor speed in range [-1, 1]
		int getSpeed();
		
		// adjust the deadband for the output (as a PWM)
		int raw_setDeadband(int db);
	
	private:
		int _pinA, _pinB, _pinPWM; // H-Bridge pins
		bool _invert; // invert forward direction
		int _direction, _pwmSpeed; // direction and speed
		int _deadband; // motor deadband (minimum output value)
		int _stopMode; // brake or coast mode
};

#endif 