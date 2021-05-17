#include <Ftduino.h>

void setup() {
  // put your setup code here, to run once:
  ftduino.init();
  //Horizontal motor inputs
  ftduino.input_set_mode(Ftduino::I1, Ftduino::SWITCH);
  ftduino.input_set_mode(Ftduino::I8, Ftduino::SWITCH);
  ftduino.counter_set_mode(Ftduino::C2, Ftduino::C_EDGE_RISING);
  //Vertical motor inputs
  ftduino.input_set_mode(Ftduino::I5, Ftduino::SWITCH);
  ftduino.counter_set_mode(Ftduino::C4, Ftduino::C_EDGE_RISING);
  //arm to rear position input
  ftduino.input_set_mode(Ftduino::I6, Ftduino::SWITCH);
  Serial.begin(57600);
}

void loop() {
  //Setup:
  //Arm reference switch, front
  uint16_t button = ftduino.input_get(Ftduino::I7);
  //Arm reference switch, rear
  uint16_t button1 = ftduino.input_get(Ftduino::I6);
  //Arm reference switch, vertical
  uint16_t button2 = ftduino.input_get(Ftduino::I8);
  //Robot reference switch, horizontal
  uint16_t button3 = ftduino.input_get(Ftduino::I5);
  //REMOVE LATER
  uint16_t m = ftduino.input_get(Ftduino::I1);
  
  //Position 1 (A1):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 800);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 100);
    while(ftduino.motor_counter_active(Ftduino::M4));

  //Position 2 (A2):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 1400);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 100);
    while(ftduino.motor_counter_active(Ftduino::M4));

  //Position 3 (A3):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 2000);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 100);
    while(ftduino.motor_counter_active(Ftduino::M4));
    
  //Position 4 (B1):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 800);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 450);
    while(ftduino.motor_counter_active(Ftduino::M4));
    
  //Position 5 (B2):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 1400);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 450);
    while(ftduino.motor_counter_active(Ftduino::M4));
    
  //Position 6 (B3):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 2000);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 450);
    while(ftduino.motor_counter_active(Ftduino::M4));
    
  //Position 7 (C1):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 800);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 800);
    while(ftduino.motor_counter_active(Ftduino::M4));
    
  //Position 8 (C2):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 1400);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 800);
    while(ftduino.motor_counter_active(Ftduino::M4));
    
  //Position 9 (C3):
    //horizontal move to rack
    ftduino.motor_counter_set_brake(Ftduino::M2, false);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 2000);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    //vertical move:
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 800);
    while(ftduino.motor_counter_active(Ftduino::M4));
}
