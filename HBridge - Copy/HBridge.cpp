// changes that

#include <Arduino.h>

#include <HBridge.h>


// constructor
HBridge::HBridge(int pinA, int pinB, int pinPWM, bool invert) {
	_pinA = pinA;
	_pinB = pinB;
	_pinPWM = pinPWM;
	_invert = invert;
	
	_direction = M_STOP;
	_pwmSpeed = 0;
	_deadband = 10;
	_stopMode = HB_BRAKE;
	
	pinMode(_pinA, OUTPUT);
	pinMode(_pinB, OUTPUT);
	pinMode(_pinPWM, OUTPUT);
	
	stop();
}

// set raw direction and speed values
void HBridge::setRaw(int direction, int pwm) {
	_direction = direction;
	_pwmSpeed = pwm;
	
	// if instructed to stop
	if (_direction == M_STOP || pwm < _deadband) {
		// brake mode
		if (_stopMode == HB_BRAKE) {
			_pwmSpeed = 255;
			digitalWrite(_pinA, LOW);
			digitalWrite(_pinB, LOW);
		}
		// coast mode
		else {
			_pwmSpeed = 0;
			digitalWrite(_pinA, LOW);
			digitalWrite(_pinB, LOW);
		}
	}
	// if instructed to go forward
	else if(_direction == M_FWD ^ _invert) {
		digitalWrite(_pinA, HIGH);
		digitalWrite(_pinB, LOW);
	}
	// if instructed to go backward
	else {
		digitalWrite(_pinA, LOW);
		digitalWrite(_pinB, HIGH);
	}
	analogWrite(_pinPWM, _pwmSpeed);
}
// set speed in range [-1, 1]
void HBridge::setSpeed(double speed) {
	if (speed == 0) {
		stop();
	}
	else if (speed < 0) {
		setRaw(M_BACK, -(int)(speed*255.0));
	}
	else {
		setRaw(M_FWD, (int)(speed*255.0));
	}
}
// tell the motor to stop
void HBridge::stop() {
	setRaw(M_STOP, 0);
}
// assign BRAKE or COAST mode for the H-Bridge
void HBridge::setStopMode(int mode) {
	_stopMode = mode;
}
// get motor direction (1, 0, or -1)
int HBridge::getDirection() {
	return _direction;
}
// get motor speed in range [-1, 1]
int HBridge::getSpeed() {
	return ((double)_pwmSpeed)/255.0 * (double)_direction;
}	
// adjust the deadband for the output (as a PWM)
// only adjust deadband if necessary...
int HBridge::raw_setDeadband(int db) {
	_deadband = db;
}