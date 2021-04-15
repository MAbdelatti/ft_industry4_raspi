#include <Wire.h>
#include <Ftduino.h>

bool activated = false; //loop will onyl start when activated = false

void receiveEvent(int howMany) //defines events called out in master code
{
  int x = Wire.read();
  if(x == 1){
    ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX); //kiln door opens
    ftduino.motor_set(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX); //kiln slider retracts into kiln
    x = 10;
  }

  else if(x == 2){
    ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX); //kiln lamp turns off
    ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX); //kiln door opens
    ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX); //kiln slider extends out of kiln
    x = 10;
   }

  else if(x == 3){
    ftduino.motor_set(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX); //mini VGR moves to kiln
    x = 10;
   }

  else if(x == 4){
    ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX); //mini VGR moves to turntable
    x = 10;
   }

  else if(x == 5){
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF, Ftduino::MAX); //mini VGR stops
    ftduino.output_set(Ftduino::O6, Ftduino::HI, Ftduino::MAX); //mini VGR valve moves down
    
    x = 10;
   }
   
 else if(x == 6){
    ftduino.output_set(Ftduino::O5, Ftduino::LO, Ftduino::MAX); //mini VGR valve vaccuum turns off

    x=10;
 }
 
 else if(x == 7){
    ftduino.output_set(Ftduino::O6, Ftduino::LO, Ftduino::MAX); //mini VGR valve moves back up
    
    x = 10;
   }

}

void setup()
{
  ftduino.init();
  Wire.begin(1);                // defines slave as "#1"
  Serial.begin(9600);           // start serial for output
}

void loop() {

 int object_is_there = ftduino.input_get(Ftduino::I5); //defines "object_is_there" as kiln phototransistor (KPT)
 while(!activated){   //while activated is false, KPT open to receiving signals
   object_is_there = ftduino.input_get(Ftduino::I5); //defines "object_is_there" as KPT within while loop
   if (!object_is_there){    //if KPT is tripped:
    
     activated = true; //stops any signals from KPT while process is occurring

     Serial.print("Material detected at KPT");
     
     Wire.beginTransmission(0); // transmit to device #0
     int x = 9;                 //compressor turns on
     Wire.write(x);              // sends one byte  
     Wire.endTransmission();    // stop transmitting
    
     Wire.onReceive(receiveEvent); // transmits events defined in receiveEvent to Master 
     
     while(!ftduino.input_get(Ftduino::I1)){  //when retracted kiln reference switch is pushed:
      ftduino.input_get(Ftduino::I1);}
     Serial.print("Material baking.\n");
     ftduino.output_set(Ftduino::O7, Ftduino::LO, Ftduino::MAX);  //kiln door closes
     ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);  //kiln slider motor stops
     delay(1000);
     ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);  //light turns on
     delay(1000);
     ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);  //light turns off
     delay(1000);
     ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);  //light turns on
     delay(1000);
     ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);  //light turns off
     delay(1000);
     ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);  //light turns on
    
     while(!ftduino.input_get(Ftduino::I3)){  //when mini VGR reaches kiln reference switch:
      ftduino.input_get(Ftduino::I3);}
     Serial.print("Material done baking.\n");
     ftduino.motor_set(Ftduino::M2, Ftduino::OFF, Ftduino::MAX);
      
       
    
     while(!ftduino.input_get(Ftduino::I2)){  //when extended kiln reference switch is pushed:
      ftduino.input_get(Ftduino::I2);}
     Serial.print("Material ready for pick-up from kiln.\n");
     ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);  //kiln light turns off
     ftduino.output_set(Ftduino::O7, Ftduino::LO, Ftduino::MAX);  //kiln door closes
     ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);  //kiln slider motor turns off
     delay(1000);
     ftduino.output_set(Ftduino::O6, Ftduino::HI, Ftduino::MAX);  //mini VGR valve lowers to material
     delay(1000);
     ftduino.output_set(Ftduino::O5, Ftduino::HI, Ftduino::MAX); //mini VGR vaccuum suction turns on
     delay(1000);
     ftduino.output_set(Ftduino::O6, Ftduino::LO, Ftduino::MAX); //mini VGR valve moves back up
     }
     activated = false; //ends process loop for slave, slave can now be reactivated by sensor
     delay(250);
 }
} 
