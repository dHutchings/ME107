#include <PID_v1.h>







//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,0,0,0, DIRECT);

//best setpoitns right now seem to be 1, .01, 0

void setup_vel_control()
{
   myPID.SetOutputLimits(-3200,3200);
   myPID.SetMode(AUTOMATIC);
   
   
  myPID.SetSampleTime(50); 
   
  //initialize the variables we're linked to
  Input = 0;  //input is Zero, starting at speed = 0
  
  Setpoint = 0;  //setpoint is zero, since I want to be going at zero speed


}

int compute_pid(float inp)
{
  
  
  Input = (double) inp;
  myPID.Compute();
  

  return Output;
}

void set_constants(double p, double i, double d)
{
   myPID.SetTunings(p,i,d); 
  
}

void set_setpoint(float st)
{
   Setpoint = (double) clamp(st,-1000,1000);   //clamp to 1000 so the setpoint's don't go wild, mostly airbitrary numbers that can be changed later
   //Serial.println(Setpoint);
  
}

double get_setpoint()
{
   return Setpoint; 
}

float clamp(float in, float mn, float mx)
{
  if(mx < in)
  {
    return mx;
  }
  else if(mn > in)
  {
    return mn;
  }
  else
  {
    return in;
  }
  
}
