#include <Encoder.h>

#include <RunningAverage.h>

RunningAverage spd_avg(3); //over 3 datapoints, should be ok for speed control


Encoder myEnc(2, 3);

long oldPosition;

unsigned long time; 

void start_encoder()
{
  oldPosition = 0;  //start at zero
  time = micros();
}

void update_encoder()
{

  long newPosition = myEnc.read();



  spd_avg.addValue( ((float) (newPosition-oldPosition))*100000/(micros() -time) );  //dx/t = speed.  Times 1mil to put into units of tics/sec.
  
  oldPosition = newPosition;

  time = micros();

}

void print_position()
{
  Serial.println(oldPosition);
}

void print_velocity()
{
  Serial.println(spd_avg.getAverage());
}

float get_velocity()
{
  return spd_avg.getAverage();
}

int get_location()
{
  return oldPosition;
}

