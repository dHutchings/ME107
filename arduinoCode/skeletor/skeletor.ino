#include <PID_v1.h>






/* Sekepton Code for Tom and Jerry
 ME 107
 3/12/2015
 
 v 1.0
*/
 


// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

//   avoid using pins with LEDs attached


int pxW = 320;

long timeToEval = 0;
long timeToEncoder = 0;
long timeToCam = 0;
float k = .01;  //a geometry constant for the track distances - will tune later.

boolean isTom = true;
boolean system_enabled = false;

//Define Variables we'll be connecting to
double Setpoint_camera, Input_camera, Output_camera;
//Specify the links and initial tuning parameters
PID camera_pid(&Input_camera, &Output_camera, &Setpoint_camera,0,0,0, DIRECT);

//best setpoitns right now seem to be 1, .01, 0


void setup() {
  setup_serial();

  if(isTom)
  {  
    Serial.println("Starting Pixy...");
    pixy_setup();
    setup_camera_control();
    Serial.println("Pixy Started");
  } 
  
  Serial.println("Starting SMC");
  setup_smc();
  Serial.println("SMC Started");
  
   
  Serial.println("Starting Encoder");
  start_encoder();
  Serial.println("Encoder Setup");

  Serial.println("Starting PID");
  setup_vel_control();
  Serial.println("PID Enabled");


  
  Serial.println("All functionality Test:");
}


void loop() 
{
  parse_input();
  
  if(system_enabled)
  {

    
    if( millis() > timeToEncoder)  //only update encoder at 100Hz
    {
      update_encoder();
      timeToEncoder = millis() + 5;
      //print_position();
    }
  
  
    if( millis() > timeToEval )  //20Hz compute.
    {
      int motorSpeed = compute_velocity_pid(get_velocity() );
      setMotorSpeed(pwm()+motorSpeed);  // full-speed forward
      timeToEval = millis()+20;
      //print_velocity();
    
    }
  
    if(isTom)
    {
      if(millis() > timeToCam)
      {
        int result = compute_camera_pid(xPos());
        set_setpoint_velocity(result); //(val * 50 since 50Hz camera frame)
        
        timeToCam = millis() + 50;
      }
    }
  }
  else
  {
    set_setpoint_velocity(0);
    setMotorSpeed(0);
     
  }
  
}




void setup_camera_control()
{
   camera_pid.SetOutputLimits(-1000,1000);
   camera_pid.SetMode(AUTOMATIC);
   
   
   camera_pid.SetSampleTime(50); 
   
  //initialize the variables we're linked to
  Input_camera = 160;  //Input_camera is Zero, starting at the middle (presumably)
  Setpoint_camera = 160;  //Setpoint_camera is zero, since I want to be at the middle of the camrea frame.

  set_constants(0,0.0,0);
}

void set_camera_constants(double p, double i, double d)
{
   camera_pid.SetTunings(p,i,d); 
  
}

int compute_camera_pid(int inp)
{
  
  
  Input_camera = (double) inp;
  camera_pid.Compute();
  

  return Output_camera;
}
