#include <SoftwareSerial.h>

//defines, setup for the software serial pin to communivate to the SMC.
#define rxPin 6  // pin 3 connects to smcSerial TX  (not used in this example)
#define txPin 5  // pin 4 connects to smcSerial RX
SoftwareSerial smcSerial = SoftwareSerial(rxPin, txPin);

int last_cmd;


void setup_smc()
{
  smcSerial.begin(19200);
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
}
// required to allow motors to move
// must be called when controller restarts and after any error
void exitSafeStart()
{
  smcSerial.write(0x83);
}

// speed should be a number from -3200 to 3200.  Required to be such by clamping
void setMotorSpeed(int speed)
{
  last_cmd = clamp(speed,-3200,3200);  //clamp to 3200 so things don't break.
  if (last_cmd < 0)
  {
    smcSerial.write(0x86);  // motor reverse command
    smcSerial.write(-last_cmd & 0x1F);
    smcSerial.write(-last_cmd >> 5);
  }
  else
  {
    smcSerial.write(0x85);  // motor forward command
    smcSerial.write(last_cmd & 0x1F);
    smcSerial.write(last_cmd >> 5);

  }
  
}

int pwm()
{
  return last_cmd;
}


int clamp_int(int in, int mn, int mx)
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
