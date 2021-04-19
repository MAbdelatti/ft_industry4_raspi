#include <Ftduino.h>

void setup() {
  // put your setup code here, to run once:
  ftduino.init();
  //Vertical motor inputs
  ftduino.input_set_mode(Ftduino::I2, Ftduino::SWITCH);
  ftduino.counter_set_mode(Ftduino::C2, Ftduino::C_EDGE_RISING);
  //Horizontal motor inputs
  ftduino.input_set_mode(Ftduino::I3, Ftduino::SWITCH);
  ftduino.counter_set_mode(Ftduino::C3, Ftduino::C_EDGE_RISING);
  //turn encoder
  ftduino.input_set_mode(Ftduino::I1, Ftduino::SWITCH);
  ftduino.counter_set_mode(Ftduino::C1, Ftduino::C_EDGE_RISING);
  Serial.begin(57600);
}

void loop() {
  //Turn motor setup
  uint16_t button1 = ftduino.input_get(Ftduino::I1);
  uint16_t impulse1 = ftduino.counter_get(Ftduino::C1);
  
  //Vertical motor setup
  uint16_t button2 = ftduino.input_get(Ftduino::I2);
  uint16_t impulse2 = ftduino.counter_get(Ftduino::C2);

  //Horizontal motor setup
  uint16_t button3 = ftduino.input_get(Ftduino::I3);
  uint16_t impulse3 = ftduino.counter_get(Ftduino::C3);

      //vertical motor
  ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX);
  while(!button2){
    button2 = ftduino.input_get(Ftduino::I2);
  }
  ftduino.motor_set(Ftduino::M2, Ftduino::OFF, Ftduino::MAX);

      //horizontal motor
  ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX);
  while(!button3){
    button3 = ftduino.input_get(Ftduino::I3);
  }
  ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
  //Return the robot to the home position
    //Turn motor
  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX);
  while(!button1){
    button1 = ftduino.input_get(Ftduino::I1);
  }
  ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);

}
