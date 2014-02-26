#include <Arduino.h>
#include <Encoder.h>

Encoder::Encoder(int pA, int pB, double distPerCount, int t, bool invertDir){
	timeout = t;
	distancePerCount = distPerCount;
	pinA = pA;
	pinB = pB;
  
	invert = invertDir;
  
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);

	p1=0; p2=0; p3=0; p4=0; p5=0;
}
  
double Encoder::getDistance(){
  return count * distancePerCount;
}
double Encoder::getSpeed(){
  if(millis() - lastTime >= timeout){
    speed = 0;
    lastTime = millis() - timeout;
  }
  return speed;
}
double Encoder::getCount(){
  return count;
}
void Encoder::reset(){
  count = 0;
  speed = 0;
}
double Encoder::getDistancePerCount(){
  return distancePerCount;
}

bool Encoder::isStopped(){
  return getSpeed() == 0;
}
int Encoder::getDirection(){
  double s = getSpeed();
  if(s > 0){ return  1; }
  if(s < 0){ return -1; }
  return 0;
}

void Encoder::encoderEvent(bool mode){
  int temp = millis();
  // average recent periods
  double p = ((double)(temp - lastTime));
  double period = (p1+p2+p3+p4+p5+p)/6;
  p5=p4; p4=p3; p3=p2; p2=p1; p1=p;
  
  // update times and speeds
  lastTime=temp;
  speed= distancePerCount / period * 1000.0;
  
  // update count
  if(digitalRead(pinA) == digitalRead(pinB) ^ !invert ^ mode){
    count++;
  }else{
    count--;
    speed *= -1.0;
  }
}