/*----------------------------------------------------------------
	Princeton Robotics Club, Princeton University 2013
	
	PID Library (C++)
	
	This library contains PID loop functionality. The main
	function is compute, which calculates an output within
	a given range based on error between a value (input) and
	a desired value (setPoint).  Compute should be called as
	often as possible, and if it is not called for a long
	time, reset should be called before the next compute call.
	
	The P, I, and D constants determine the importance of:
		current error (proportional P)
		aggregated error (integral I)
		change in error (derivative D)
		
	When tuning, tune P so that the system makes it close to
	the setpoint without overshooting, then tune I.  Often D
	is not needed, but also is often negative to resist large
	changes in input readings (which can be due to noise)
	The formula used assumes that the D constant is negative by
	default, so specify a positive value to achieve this behavior

----------------------------------------------------------------*/

#ifndef PID_h
#define PID_h

class PID {
	public:
		// constructors
		PID(double p, double i, double d, double lo, double hi);
		PID(double p, double i, double d, double range);
		PID(double p, double i, double d);
		
		// compute PID output (call every loop)
		double compute(double input, double setPoint, int time);
		double compute(double error, int time); // error = setPoint - input
		// reset I term
		void reset();
	
	private:
		double kp, ki, kd; // tuning constants
		double outMin, outMax; // output range
		double iTerm; // error sum (I term)
		unsigned long lastT; // last calculation time
		double lastIn; // last input (D term)
		
		// used by constructors
		void init(double p, double i, double d, double lo, double hi);
};

#endif