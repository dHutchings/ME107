#include <PixyI2C.h>
#include <Wire.h>

PixyI2C pixy(0x55); // You can set the I2C address through PixyI2C object 

int oldLoc = 160;

void pixy_setup()
{
    pixy.init();
}

int xPos()
{

uint16_t blocks;
  char buf[32]; 
  
  blocks = pixy.getBlocks();

  
  if (blocks)
  {
    oldLoc = pixy.blocks[0].x;
    return oldLoc;
    
  }
  else  //this else statement will help if the target goes out of frame for a bit, it'll return the most recently seen position as a guess..
  {
    return oldLoc;
  }
}
