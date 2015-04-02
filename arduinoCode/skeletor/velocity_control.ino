#include <PID_v1.h>







//Define Variables we'll be connecting to
double Setpoint_velocity, Input_velocity, Output_velocity;

//Specify the links and initial tuning parameters
PID velocity_pid(&Input_velocity, &Output_velocity, &Setpoint_velocity,0,0,0, DIRECT);

//best setpoitns right now seem to be 1, .01, 0

void setup_vel_control()
{
   velocity_pid.SetOutputLimits(-3200,3200);
   velocity_pid.SetMode(AUTOMATIC);
   
   
  velocity_pid.SetSampleTime(20); 
   
  //initialize the variables we're linked to
  Input_velocity = 0;  //Input_velocity is Zero, starting at speed = 0
  
  Setpoint_velocity = 0;  //Setpoint_velocity is zero, since I want to be going at zero speed

  set_constants(1.0,0.25,0);
}

int compute_velocity_pid(float inp)
{
  
  
  Input_velocity = (double) inp;
  velocity_pid.Compute();
  

  return Output_velocity;
}

void set_constants(double p, double i, double d)
{
   velocity_pid.SetTunings(p,i,d); 
  
}

void set_setpoint_velocity(float st)
{
   Setpoint_velocity = (double) clamp(st,-1000,1000);   //clamp to 1000 so the Setpoint_velocity's don't go wild, mostly airbitrary numbers that can be changed later
   //Serial.println(Setpoint_velocity);
  
}

double get_setpoint_velocity()
{
   return Setpoint_velocity; 
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
