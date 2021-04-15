// Use the following line if you have a Leonardo, FtDuino or MKR1000
#define USE_USBCON

#include <ros.h>
#include <std_msgs/Bool.h>
#include <Ftduino.h>

#define OUTPUT_PORT FTduino::O8

ros::NodeHandle nh;

std_msgs::Bool msg_blue;
std_msgs::Bool msg_red;
std_msgs::Bool msg_white;

ros::Publisher sld_blue_pub("sld_blue_pub",   &msg_blue);
ros::Publisher sld_red_pub("sld_red_pub",     &msg_red);
ros::Publisher sld_white_pub("sld_white_pub", &msg_white);

bool belt_running = false;

void setup()
{
  // Initialize ROS Nodes
  nh.initNode();
  nh.advertise(sld_blue_pub);
  nh.advertise(sld_red_pub);
  nh.advertise(sld_white_pub);

  // Begin Setup of Conveyor Belt Code
  ftduino.init();
  ftduino.input_set_mode(Ftduino::I1, Ftduino::SWITCH);

  // Begin Setup of Color Sensor Code
  ftduino.input_set_mode(Ftduino::I2, Ftduino::VOLTAGE);
  //ftduino.output_set(Ftduino::O1, Ftduino::OFF, Ftduino::MAX);
 
  Serial.begin(57600);

  ftduino.output_set(Ftduino::O5, Ftduino::OFF, Ftduino::MAX);
  ftduino.output_set(Ftduino::O6, Ftduino::OFF, Ftduino::MAX);
  ftduino.output_set(Ftduino::O7, Ftduino::OFF, Ftduino::MAX);
  ftduino.output_set(Ftduino::O8, Ftduino::OFF, Ftduino::MAX);
  
  ftduino.counter_set_mode(Ftduino::C1, Ftduino::C_EDGE_RISING);

  ftduino.input_set_mode(Ftduino::I3, Ftduino::SWITCH);

}

void loop()
{  
  // Publish Initial Storage Status
  bool storage_b = !(ftduino.input_get(Ftduino::I6));
  bool storage_r = !(ftduino.input_get(Ftduino::I7));
  bool storage_w = !(ftduino.input_get(Ftduino::I8));

  bool old_storage_b;
  bool old_storage_r;
  bool old_storage_w;
  
  msg_blue.data  = !storage_b;
  msg_red.data   = !storage_r;
  msg_white.data = !storage_w;
  
//  sld_blue_pub.publish( &msg_blue);
//  sld_red_pub.publish( &msg_red);
//  sld_white_pub.publish( &msg_white);
      
  // When an Object Reaches The Belt
  uint8_t new_input = ftduino.input_get(Ftduino::I1);
  if(!new_input){
      ftduino.motor_set(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX); //Run The Belt
      belt_running = true;
  }
  while(belt_running){

    // Begin Color Sensor Code
    uint16_t color_val = ftduino.input_get(Ftduino::I2);
    uint8_t color = 0; // No object detected
    uint8_t impulse = ftduino.counter_get(Ftduino::C1);
     
    // Wait Until an Object Passes
    while (color_val > 2100){
      color_val = ftduino.input_get(Ftduino::I2);
      nh.spinOnce();
      delay(100);
    }   
  
    for (int i = 1; i <= 3; i++){
        color_val = min(color_val, ftduino.input_get(Ftduino::I2));
        delay(500);
      }
     
    if (color_val > 1900){ //Blue object detected
      color = 1;
      bool object  = ftduino.input_get(Ftduino::I3);
  
      // Wait Until the Object Comes Outside
      while(object){
        object  = ftduino.input_get(Ftduino::I3);
        delay(100);
      }
      ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);
      ftduino.counter_clear(Ftduino::C1);
      
      impulse = ftduino.counter_get(Ftduino::C1);
      while (impulse <=1){
        impulse = ftduino.counter_get(Ftduino::C1);
        delay(050);
      }
      
      ftduino.output_set(Ftduino::O5, Ftduino::HI, Ftduino::MAX);
      delay(1000);
      ftduino.output_set(Ftduino::O5, Ftduino::LO, Ftduino::MAX);
      ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);
      }
      
    else if (color_val > 1700){ // Red object detected
      color = 2;
      bool object  = ftduino.input_get(Ftduino::I3);
  
      while(object){
        object  = ftduino.input_get(Ftduino::I3);
        delay(100);
      }
    
      ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);
      ftduino.counter_clear(Ftduino::C1);
      
      impulse = ftduino.counter_get(Ftduino::C1);
      while (impulse <=5){
        impulse = ftduino.counter_get(Ftduino::C1);
        delay(200);
      }    
      
      ftduino.output_set(Ftduino::O6, Ftduino::HI, Ftduino::MAX);
      delay(1000);
      ftduino.output_set(Ftduino::O6, Ftduino::LO, Ftduino::MAX);
      ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);
      }
      
    else if (color_val > 800){ // White object detected
      color = 3;
      bool object  = ftduino.input_get(Ftduino::I3);
  
      while(object){
        object  = ftduino.input_get(Ftduino::I3);
        delay(100);
      }
    
      ftduino.output_set(Ftduino::O8, Ftduino::HI, Ftduino::MAX);
      ftduino.counter_clear(Ftduino::C1);
      
      impulse = ftduino.counter_get(Ftduino::C1);
      while (impulse <=9){
        impulse = ftduino.counter_get(Ftduino::C1);
        delay(500);
      }
      
      ftduino.output_set(Ftduino::O7, Ftduino::HI, Ftduino::MAX);
      delay(1000);
      ftduino.output_set(Ftduino::O7, Ftduino::LO, Ftduino::MAX);
      ftduino.output_set(Ftduino::O8, Ftduino::LO, Ftduino::MAX);
      }

      old_storage_b = storage_b;
      old_storage_r = storage_r;
      old_storage_w = storage_w;
  
      storage_b = !(ftduino.input_get(Ftduino::I6));
      storage_r = !(ftduino.input_get(Ftduino::I7));
      storage_w = !(ftduino.input_get(Ftduino::I8));

      if (!(storage_b == old_storage_b)){
        // Send ROS Messages of the Blue Storage Status
        msg_blue.data  = storage_b;
        sld_blue_pub.publish( &msg_blue);
      }

      if (!(storage_r == old_storage_r)){
        // Send ROS Messages of the Red Storage Status
        msg_red.data   = storage_r;
        sld_red_pub.publish( &msg_red);
      }

      if (!(storage_w == old_storage_w)){
        // Send ROS Messages of the White Storage Status
        msg_white.data = storage_w;
        sld_white_pub.publish( &msg_white);
      }
  
      // Turn Off the Belt
      if (!((storage_b) && (storage_r) && (storage_w))){
        ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);
        belt_running = false;
      }
  }
  nh.spinOnce();
  delay(250);

}
