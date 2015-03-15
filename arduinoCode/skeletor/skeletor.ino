/* Sekepton Code for Tom and Jerry
 ME 107
 3/12/2015
 
 v 1.0
*/
 
#include <PID_v1.h>

#include <Wire.h>
#include <PixyI2C.h>

//#include <Encoder.h>

#include <SoftwareSerial.h>

#define rxPin 5  // pin 3 connects to smcSerial TX  (not used in this example)
#define txPin 6  // pin 4 connects to smcSerial RX
SoftwareSerial smcSerial = SoftwareSerial(rxPin, txPin);

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
//Encoder myEnc(5, 6);
//   avoid using pins with LEDs attached

PixyI2C pixy(0x55); // You can set the I2C address through PixyI2C object 
int pxW = 320;

void setup() {
  Serial.begin(115200);
  
  Serial.println("Starting Pixy...");
  pixy.init();
  Serial.println("Pixy Started");
 
  // the Simple Motor Controller must be running for at least 1 ms
  // before we try to send serial data, so we delay here for 5 ms
  delay(5);
 
  // if the Simple Motor Controller has automatic baud detection
  // enabled, we first need to send it the byte 0xAA (170 in decimal)
  // so that it can learn the baud rate
  smcSerial.write(0xAA);  // send baud-indicator byte
 
  // next we need to send the Exit Safe Start command, which
  // clears the safe-start violation and lets the motor run
  exitSafeStart();  // clear the safe-start violation and let the motor run
  Serial.println("Hello world!");
  
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = pxW / 2;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  Serial.println("All functionality Test:");
}

//long oldPosition  = -999;

void loop() {
  
  /*----------- Begin Pixy ----------*/
  //Serial.println("Hello world!");
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  
  //Serial.println("Getting BLocks");
  blocks = pixy.getBlocks();
  //Serial.println("Got Blocks");
  Input = pixy.blocks[0].x;
  /*
  if (blocks)
  {
    //Serial.println("Inside if");
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%5==0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();
      }
    }
  }
  */
  
/*----------- End Pixy ----------*/

/*----------- Begin PID ----------*/
  //Input = analogRead(0);
  myPID.Compute();
  //analogWrite(3,Output);
/*----------- End PID ----------*/

/*----------- Begin Motor ----------*/
  int motorSpeed = map(Output, 0, 255, -3200, 3200);
  Serial.println(motorSpeed);
  setMotorSpeed(motorSpeed);  // full-speed forward
  delay(100);
  //setMotorSpeed(-3200);  // full-speed reverse
  //delay(1000);
  Serial.println("ran 1");
/*----------- End Motor ----------*/

/*----------- Begin Encoder ----------*/
//  long newPosition = myEnc.read();
//  if (newPosition != oldPosition) {
//   oldPosition = newPosition;
//    Serial.println(newPosition);
//  }
/*----------- End Encoder ----------*/

}

// required to allow motors to move
// must be called when controller restarts and after any error
void exitSafeStart()
{
  smcSerial.write(0x83);
}

// speed should be a number from -3200 to 3200
void setMotorSpeed(int speed)
{
  if (speed < 0)
  {
    smcSerial.write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    smcSerial.write(0x85);  // motor forward command
  }
  smcSerial.write(speed & 0x1F);
  smcSerial.write(speed >> 5);
}

