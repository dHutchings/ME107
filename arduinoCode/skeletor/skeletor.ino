

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

void setup() {
  setup_serial();

  if(isTom)
  {  
    Serial.println("Starting Pixy...");
    pixy_setup();
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
  
  if( millis() > timeToEncoder)  //only update encoder at 100Hz
  {
    update_encoder();
    timeToEncoder = millis() + 10;
    //print_position();
  }


  if( millis() > timeToEval )  //20Hz compute.
  {
    int motorSpeed = compute_pid(get_velocity() );
    //Serial.println(motorSpeed);
    setMotorSpeed(pwm()+motorSpeed);  // full-speed forward
    timeToEval = millis()+50;
    //print_velocity();
  
  }

  if(isTom)
  {
    if(millis() > timeToCam)
    {
      int val = 155 - xPos();
      
      if(abs(val) > 10)
      {
         set_setpoint(get_setpoint() + k*val); //(val * 50 since 50Hz camera frame)
      }
      timeToCam = millis() + 50;
    }
  }

}



