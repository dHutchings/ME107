



/* Sekepton Code for Tom and Jerry
 ME 107
 3/12/2015
 
 v 1.0
*/
 
#include <PID_v1.h>







//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

//   avoid using pins with LEDs attached


int pxW = 320;

void setup() {
  Serial.begin(115200);
  
  Serial.println("Starting Pixy...");
  pixy_setup();

  Serial.println("Pixy Started");
 
  Serial.println("Starting SMC");
  setup_smc();
  Serial.println("SMC Started");
  
  Serial.println("Hello world!");
  
  Serial.println("Starting Encoder");
  start_encoder();
  Serial.println("Encoder Setup");
  
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = pxW / 2;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  Serial.println("All functionality Test:");
}


void loop() {
  
  /*----------- Begin Pixy ----------*/

  Input = xPos();
  
  myPID.Compute();



  int motorSpeed = map(Output, 0, 255, -3200, 3200);
  Serial.println(motorSpeed);
  setMotorSpeed(motorSpeed);  // full-speed forward
  delay(100);

  update_encoder();


/*  Serial.print("Pos is");
  print_position();
  Serial.print("Vel is");
  print_velocity();
*/

   Serial.println("ran 1");

}



