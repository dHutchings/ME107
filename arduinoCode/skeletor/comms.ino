void setup_serial()
{
    Serial.begin(57600);
}

void parse_input()
{
  if (Serial.available() > 0)
  {
    int msg = Serial.read();
    if(msg == 112) // small p --> Change PID CONSTANTS 
    {
       Serial.println("Awaiting three floats, for the PID constants");
       Serial.println("kp?");
       while(Serial.available() == 0)
       {
         delay(1);
       }
       double kp = Serial.parseFloat();
       Serial.println("ki?");
       while(Serial.available() == 0)
       {
         delay(1);
       }
       double ki = Serial.parseFloat();
       Serial.println("kd?");
       while(Serial.available() == 0)
       {
         delay(1);
       }
       double kd = Serial.parseFloat();
       Serial.println("Constants are");
       
       Serial.print("kp = ");
       Serial.println(kp); 
       
       Serial.print("ki = ");
       Serial.println(ki); 
       
       Serial.print("kd = ");
       Serial.println(kd); 
       
       set_constants(kp,ki,kd);  
    }
    else if(msg ==  115) //small s, set setpoint
    {
       Serial.println("Setpoint?");
       while(Serial.available() == 0)
       {
         delay(1);
       }
       float set = Serial.parseFloat();
       set_setpoint_velocity(set);
    }
    else if(msg == 108) //small l
    {
       //Serial.print("Location is");
       print_position();
    }
    else if(msg == 99)//small c, get camera location
    {
       Serial.println(xPos());
    }
    else if(msg == 107) //small k, change camera PID consants
    {
       Serial.println("Awaiting three float, for the camera PID constant");
       Serial.println("kp?");
       while(Serial.available() == 0)
       {
         delay(1);
       }
       double kp = Serial.parseFloat();
       Serial.println("ki?");
       while(Serial.available() == 0)
       {
         delay(1);
       }
       double ki = Serial.parseFloat();
       Serial.println("kd?");
       while(Serial.available() == 0)
       {
         delay(1);
       }
       double kd = Serial.parseFloat();
       Serial.println("Constants are");
       
       Serial.print("kp = ");
       Serial.println(kp); 
       
       Serial.print("ki = ");
       Serial.println(ki); 
       
       Serial.print("kd = ");
       Serial.println(kd); 
       
       set_camera_constants(kp,ki,kd);  
    }
    else if(msg == 121) //small y, system enable
    {
      Serial.println("Start!");
      system_enabled = true;
    }
    else if(msg == 110) //small n, system disable
    {
      Serial.println("Stop!");
      system_enabled = false;
    }

  }
  
  
  
}
