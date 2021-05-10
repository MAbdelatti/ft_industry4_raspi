#include <Ftduino.h>

void setup() {
  // put your setup code here, to run once:
  ftduino.init();
  //Horizontal motor inputs
  ftduino.input_set_mode(Ftduino::I5, Ftduino::SWITCH);
  ftduino.counter_set_mode(Ftduino::C2, Ftduino::C_EDGE_RISING);
  //Vertical motor inputs
  ftduino.input_set_mode(Ftduino::I8, Ftduino::SWITCH);
  ftduino.counter_set_mode(Ftduino::C4, Ftduino::C_EDGE_RISING);
  //arm to rear position input
  ftduino.input_set_mode(Ftduino::I6, Ftduino::SWITCH);
  Serial.begin(57600);
}

void loop() {
  // Setup:
  //Arm to rear setup
  uint16_t button1 = ftduino.input_get(Ftduino::I6);
  
  //Vertical motor setup
  uint16_t button2 = ftduino.input_get(Ftduino::I8);

  //Horizontal motor setup
  uint16_t button3 = ftduino.input_get(Ftduino::I5);

  //Bring the robot to home position:
  //arm to rear
  ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX);
    while(!button1){
      button1 = ftduino.input_get(Ftduino::I6);
     }
  ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
  //horizontal motor
  ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX);
  while(!button3){
    button3 = ftduino.input_get(Ftduino::I5);
  }
  ftduino.motor_set(Ftduino::M2, Ftduino::OFF, Ftduino::MAX);
  
  //vertical motor
  ftduino.motor_set(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX);
  while(!button2){
    button2 = ftduino.input_get(Ftduino::I8);
  }
  ftduino.motor_set(Ftduino::M4, Ftduino::OFF, Ftduino::MAX);

}
