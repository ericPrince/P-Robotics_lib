


// constructors
PID::PID(double p, double i, double d, double lo, double hi) {
	init(p, i, d, lo, hi);
}
PID::PID(double p, double i, double d, double range) {
	init(p, i, d, -range, range);
}
PID::PID(double p, double i, double d) {
	init(p, i, d, -1, 1);
}
		
// compute PID output (call every loop)
double PID::compute(double input, double setPoint, int time) {
	double error = setPoint - input;  
  
	iTerm += (ki * error * (double) (time - lastT));
  
	// rescale I term to be in output range (no build up)
	if(iTerm > outMax){ 
		iTerm= outMax; 
	}
	else if(iTerm < outMin){ 
		iTerm= outMin;  
	}
	
	double output = kp*error + iTerm - kd*(input - lastInput);     
  
	// rescale output to be in range
	if(output > outMax){ 
	output = outMax;
	} 
	else if(output < outMin){ 
		output = outMin;
	}
  
	lastInput = input;
	lastT = time;

	return output;
}
double PID::compute(double error, int time) {
	compute(error, 0);
}
// reset I term
void PID::reset() {
	iTerm=0;
	lastT=millis();
	lastInput=0;
}
	
	
// used by constructors (private)
void PID::init(double p, double i, double d, double lo, double hi) {
	kp = p; ki = i; kd = d;
	outMin = lo; outMax = hi;
	reset();
}
