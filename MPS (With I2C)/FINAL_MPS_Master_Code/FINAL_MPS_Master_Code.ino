#include <Wire.h>
#include <Ftduino.h>

bool activated = false; //loop will only start when activated = false

void receiveEvent(int howMany) //defines events called out in slave code
{
  int x = Wire.read();
  if(x == 9){
    ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX); //compressor turns on
    activated = true; //begins process loop within master
    delay(1500); 
    }
}

void setup()
{
  ftduino.init();
  Serial.begin(9600); //start serial for output
  Wire.begin(0); //defines master as "#0"
}

int x = 0; //resets event loop

void loop()
{
  Wire.onReceive(receiveEvent); //transmits event defined in receiveEvent to Slave
    delay(5000);
    if (activated){ //if slave is activated, slave calls out x=9 and master is activated
      
      Wire.beginTransmission(1);// transmit to device #1
      x = 1;                          //kiln door opens, kiln slider retracts into kiln
      Wire.write(x);            // sends one byte  
      Wire.endTransmission();   // stop transmitting
      Serial.print(x);
  
      delay(3000);
  
      Wire.beginTransmission(1);// transmit to device #1
      x = 3;                          //mini VGR moves to kiln
      Wire.write(x);            // sends one byte 
      Wire.endTransmission();   // stop transmitting
      Serial.print(x);
  
      delay(8000);
  
      Wire.beginTransmission(1); // transmit to device #1
      x = 2;                          //kiln lamp turns off, kiln door opens, kiln slider extends out of kiln
      Wire.write(x);             // sends one byte 
      Wire.endTransmission();    // stop transmitting
      Serial.print(x);
  
      delay(8000);
  
      Wire.beginTransmission(1); // transmit to device #1
      x = 4;                          //mini VGR moves to turntable
      Wire.write(x);             // sends one byte 
      Wire.endTransmission();    // stop transmitting
      Serial.print(x);
  
    
  
      while(!ftduino.input_get(Ftduino::I5)){ 
        ftduino.input_get(Ftduino::I5);}     //when mini VGR reference switch at turntable position is pressed:
      
    
      Wire.beginTransmission(1); // transmit to device #1
      x = 5;                          //mini VGR stops, mini VGR valve moves down
      Wire.write(x);             // sends one byte 
      Wire.endTransmission();    // stop transmitting
      Serial.print(x);

      delay(1000);
    
      Wire.beginTransmission(1); // transmit to device #1
      x = 6;                          //mini VGR valve vacuum turns off
      Wire.write(x);             // sends one byte 
      Wire.endTransmission();    // stop transmitting
      Serial.print(x);

      delay(1000);
      
      Wire.beginTransmission(1); // transmit to device #1
      x = 7;                          //mini VGR valve moves back up
      Wire.write(x);             // sends one byte 
      Wire.endTransmission();    // stop transmitting
      Serial.print(x);
    
      delay(3000);
      
      ftduino.motor_set(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX); //turntable motor turns on

      while(!ftduino.input_get(Ftduino::I2)){   //when turntable reaches saw position:
        ftduino.input_get(Ftduino::I2);} 
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX); //turntable stops
      delay(1000);
      ftduino.motor_set(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX); //saw rotates left
      delay(3000);
      ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX); //saw rotates right
      delay(3000);
      ftduino.motor_set(Ftduino::M2, Ftduino::OFF, Ftduino::MAX); //saw turns off
      ftduino.motor_set(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX); //turntable moves to conveyor
      delay(1000); 
 
      while(!ftduino.input_get(Ftduino::I3)){   //when turntable reaches conveyor position:
        ftduino.input_get(Ftduino::I3);}
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX); //turntable stops
      ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX); //compressor turns on
      ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX); //valve pushes material onto conveyor
      delay(1000);
      ftduino.output_set(Ftduino::O7, Ftduino::LO, Ftduino::MAX); //valve retracts
      delay(1000);
      ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX); //compressor turns off
      ftduino.motor_set(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX); //conveyor belt turns on
      ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX); //turntable moves back to mini VGR position
      

      while(!ftduino.input_get(Ftduino::I1)){   //when turntable reaches mini VGR position:
        ftduino.input_get(Ftduino::I1);}
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX); //turntable stops

      while(!ftduino.input_get(Ftduino::I4)){  //when material passes conveyor belt phototransistor
        ftduino.input_get(Ftduino::I4);}
      delay(2000);
      ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);  //conveyor belt turns off
      delay(1000);

    activated = false; //ends process loop for master, master can now be reactivated
}}
