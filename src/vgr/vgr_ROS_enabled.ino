// Use the following line if you have a Leonardo, FtDuino or MKR1000
#define USE_USBCON

#include <ros.h>
#include <std_msgs/Bool.h>
#include <Ftduino.h>

ros::NodeHandle nh;
std_msgs::Bool bool_msg;

bool move_cmd = true;
bool in_processing_object = false;

ros::Publisher vgr_new_material("vgr_new_material", &bool_msg);

void goHome(){
  
  ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 350);
  while(ftduino.motor_counter_active(Ftduino::M2));
  ftduino.motor_counter(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX, 595);
  while(ftduino.motor_counter_active(Ftduino::M3));
  ftduino.motor_counter(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX, 260);
  nh.loginfo("VGR is Set to Home");
  move_cmd = true;
}

void dropMaterial(){
  ftduino.motor_counter(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX, 595);
  while(ftduino.motor_counter_active(Ftduino::M3));
  ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 350);
  while(ftduino.motor_counter_active(Ftduino::M2));
  
  ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);
  ftduino.output_set(Ftduino::O7, Ftduino::LO, Ftduino::MAX);
  nh.loginfo("VGR Dropped Material at DPS");
}

void messageCb_blue(const std_msgs::Bool &payload_msg){  
  
  if (payload_msg.data && move_cmd){    
    nh.loginfo("VGR Received an Order at the BLUE Topic");
    move_cmd = false;
    //move to Sorting Line Drop-off area (blue)
    ftduino.motor_counter(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX, 470);  
    while(ftduino.motor_counter_active(Ftduino::M1));
    
    //pick up material (blue)
    ftduino.motor_counter(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX, 400);  
    while(ftduino.motor_counter_active(Ftduino::M3));
    
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 850);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX);
    ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);
    delay(2000);
    
    //move to end point
    ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 850);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    ftduino.motor_counter(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX, 400);
    while(ftduino.motor_counter_active(Ftduino::M3));
    
    ftduino.motor_counter(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX, 210);
    while(ftduino.motor_counter_active(Ftduino::M1));
    
    //drop off material at end point
    digitalWrite(LED_BUILTIN, HIGH);
    dropMaterial();
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    
    //move back home
    goHome();
  }
}

void messageCb_red(const std_msgs::Bool &payload_msg){
  
  if (payload_msg.data && move_cmd){
    nh.loginfo("VGR Received an Order at the RED Topic");
    move_cmd = false;
    //move to Sorting Line Drop-off area (red)
    ftduino.motor_counter(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX, 390);
    while(ftduino.motor_counter_active(Ftduino::M1));
    
    //pick up material (red)
    ftduino.motor_counter(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX, 450);
    while(ftduino.motor_counter_active(Ftduino::M3));
    
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 850);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX);
    ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);
    delay(2000);
    
    //move to end point
    ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 850);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    ftduino.motor_counter(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX, 450);
    while(ftduino.motor_counter_active(Ftduino::M3));
    
    ftduino.motor_counter(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX, 130);
    while(ftduino.motor_counter_active(Ftduino::M1));
    
    //drop off material at end point
    digitalWrite(LED_BUILTIN, HIGH);
    dropMaterial();
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    
    //move back home
    goHome();
  }
}

void messageCb_white(const std_msgs::Bool &payload_msg){
  
  if (payload_msg.data && move_cmd){
    nh.loginfo("VGR Received an Order at the WHITE Topic");
    move_cmd = false;
    //move to Sorting Line Drop-off area (white)
    ftduino.motor_counter(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX, 320);
    while(ftduino.motor_counter_active(Ftduino::M1));
    
    //pick up material (white)
    ftduino.motor_counter(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX, 610);
    while(ftduino.motor_counter_active(Ftduino::M3));
    
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 850);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX);
    ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);
    delay(2000);
    
    //move to end point
    ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 850);
    while(ftduino.motor_counter_active(Ftduino::M2));
    
    ftduino.motor_counter(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX, 610);
    while(ftduino.motor_counter_active(Ftduino::M3));
    
    ftduino.motor_counter(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX, 60);
    while(ftduino.motor_counter_active(Ftduino::M1));
    
    //drop off material at end point
    digitalWrite(LED_BUILTIN, HIGH);
    dropMaterial();
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    //move back home
    goHome();
  }
}

void in_processing(){
 if (move_cmd){
   move_cmd = false; 
   //pick up material from in-processing point
   nh.loginfo("VGR is Picking Up Material from in-Processing Unit"); 
   ftduino.motor_counter_set_brake(Ftduino::M2, false);
   ftduino.motor_counter(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX, 15);
   ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 800);
   while(ftduino.motor_counter_active(Ftduino::M2));
   ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX);
   ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);
   delay(2000);
   ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 800);
   while(ftduino.motor_counter_active(Ftduino::M2));
   
   //move to color sensor
   nh.loginfo("VGR is Moving to DPS Color Sensor"); 
   ftduino.motor_counter(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX, 105);
   while(ftduino.motor_counter_active(Ftduino::M1));
   ftduino.motor_counter(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX, 70);
   while(ftduino.motor_counter_active(Ftduino::M3));
   ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 650);
   while(ftduino.motor_counter_active(Ftduino::M2));
 
   //color sensor code
   uint16_t color_val = ftduino.input_get(Ftduino::I8);

   if (color_val > 1700){
     nh.loginfo("DPS Detected Blue Object");
  }
   else if (color_val > 1350){
     nh.loginfo("DPS Detected Red Object");
  }
   else if (color_val > 200){
     nh.loginfo("DPS Detected White Object");
  }

  in_processing_object = true;
  bool_msg.data = in_processing_object;
  
  vgr_new_material.publish( &bool_msg);
  nh.spinOnce();
  in_processing_object = false;
  delay(5000);
  nh.loginfo("Done Sending Message");
  
  ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 670);
  while(ftduino.motor_counter_active(Ftduino::M2));
 
  //move to HBW conveyor belt
  nh.loginfo("VGR is Moving to HBW"); 
  ftduino.motor_counter(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX, 1280);
  while(ftduino.motor_counter_active(Ftduino::M1));
  ftduino.motor_counter(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX, 105);
  while(ftduino.motor_counter_active(Ftduino::M3));
  ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 30);
  while(ftduino.motor_counter_active(Ftduino::M2));

  delay(12000);
  
  //drop material
  ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);
  ftduino.output_set(Ftduino::O7, Ftduino::LO, Ftduino::MAX);
  nh.loginfo("VGR Dropped Material at HBW"); 
  delay(2000);

 //move back to home position
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
  
  //Turn motor
  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX);
  while(!button1){
    button1 = ftduino.input_get(Ftduino::I1);
  }
  ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);
  nh.loginfo("VGR is Set to Home");
  move_cmd = true;
  }
}

void material_processing(const std_msgs::Bool &payload_msg){
  if (payload_msg.data && move_cmd){
    move_cmd = false;
    //move to HBW
    nh.loginfo("VGR is Moving to HBW");
    ftduino.motor_counter(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX, 1410);
    while(ftduino.motor_counter_active(Ftduino::M1));
    //pick up material
    ftduino.motor_counter(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX, 180);
    while(ftduino.motor_counter_active(Ftduino::M3));
    delay(21000);
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 250);
    while(ftduino.motor_counter_active(Ftduino::M2));
    ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX);
    ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);
    delay(2000);
    nh.loginfo("VGR Picked Up Material from HBW");
    
    //move to MPS
    nh.loginfo("VGR is Moving to MPS");
    ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 250);
    while(ftduino.motor_counter_active(Ftduino::M2));
    ftduino.motor_counter(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX, 180);
    while(ftduino.motor_counter_active(Ftduino::M3));
    ftduino.motor_counter(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX, 480);
    while(ftduino.motor_counter_active(Ftduino::M1));
    //drop off material
    ftduino.motor_counter(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX, 870);
    while(ftduino.motor_counter_active(Ftduino::M3));
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 510);
    while(ftduino.motor_counter_active(Ftduino::M2));
    ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);
    ftduino.output_set(Ftduino::O7, Ftduino::LO, Ftduino::MAX);
    delay(2000);
    nh.loginfo("VGR Dropped Material at MPS");
    
    //move back to home position
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
    
    //Turn motor
    ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX);
    while(!button1){
      button1 = ftduino.input_get(Ftduino::I1);
    }
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);
    while(ftduino.motor_counter_active(Ftduino::M1));
  
    //wait for material to be processed through MPS and Sorting Line
    delay(3000);
    nh.loginfo("VGR is Set to Home");
    move_cmd = true;
  }
}

ros::Subscriber<std_msgs::Bool> vgr_blue_sub("sld_blue_pub", &messageCb_blue);
ros::Subscriber<std_msgs::Bool> vgr_red_sub("sld_red_pub", &messageCb_red);
ros::Subscriber<std_msgs::Bool> vgr_white_sub("sld_white_pub", &messageCb_white);
ros::Subscriber<std_msgs::Bool> new_order_sub("new_order", &material_processing);

void setup()
{
  nh.initNode();
  nh.subscribe(vgr_blue_sub);
  nh.subscribe(vgr_red_sub);
  nh.subscribe(vgr_white_sub);
  nh.subscribe(new_order_sub);

  nh.advertise(vgr_new_material);

  pinMode(LED_BUILTIN, OUTPUT);

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
  //in-processing sensor
  ftduino.input_set_mode(Ftduino::I7, Ftduino::SWITCH);
  //color sensor
  ftduino.input_set_mode(Ftduino::I8, Ftduino::VOLTAGE);
  //ending sensor
  ftduino.input_set_mode(Ftduino::C4, Ftduino::SWITCH);
//  Serial.begin(57600); 
}


void loop()
{
  while(move_cmd && ftduino.input_get(Ftduino::I7)){
    nh.spinOnce(); 
    delay(250);
  }
  
  if (!ftduino.input_get(Ftduino::I7)){
    in_processing();
  }
  delay(250);
}
