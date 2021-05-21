// Use the following line if you have a Leonardo, FtDuino or MKR1000
#define USE_USBCON

#include <ros.h>
#include <std_msgs/String.h>
#include <Ftduino.h>

ros::NodeHandle nh;
bool move_hbw = true;

std_msgs::String str_msg;
ros::Publisher update_empty("what_is_empty", &str_msg);
char empty_payload[3] = "D4";

std_msgs::String str_msg_occupied;
ros::Publisher update_occupied("what_is_occupied", &str_msg_occupied);
char occupied_payload[9] = "D4_blue";

void bring_back_home(){
  //Vertical motor setup
  uint16_t button2 = ftduino.input_get(Ftduino::I8);
  uint16_t button3 = ftduino.input_get(Ftduino::I5);
  uint16_t button5 = ftduino.input_get(Ftduino::I6);
  
  //depth motor
  ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX);
  while(!button5){
    button5 = ftduino.input_get(Ftduino::I6);
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

void move_robot_to_shelf(uint16_t x, uint16_t y, String _caller){
  if (_caller == "out_processing"){
    nh.loginfo("HBW Received an Order");
  }
  else if (_caller == "in_processing"){
    nh.loginfo("HBW is Preparing an Empty Box");
  }
  
  if(ftduino.input_get(Ftduino::I5)){
   ftduino.motor_counter_set_brake
   (Ftduino::M2, false);
   ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, x);
   while(ftduino.motor_counter_active(Ftduino::M2));
   ftduino.motor_counter_set_brake(Ftduino::M4, false);
   ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, y);
   while(ftduino.motor_counter_active(Ftduino::M4));
   
   // Extend robot arm 
    uint16_t button = ftduino.input_get(Ftduino::I7);
    //starts motor
    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX);
    while(!button){
      button = ftduino.input_get(Ftduino::I7);
    }
    
    //turns off motor
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
    // Raise robot arm
    
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, 100);
    while(ftduino.motor_counter_active(Ftduino::M4));
    
    if (_caller == "out_processing"){
      nh.loginfo("HBW Picked Up Material");
    }
    else if (_caller == "in_processing"){
      nh.loginfo("HBW Picked Empty Box from The Shelf");
    }
  
    // Retract robot arm
    uint16_t button1 = ftduino.input_get(Ftduino::I6);
    //turns motor back on, in other direction
    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX);
    while(!button1){
      button1 = ftduino.input_get(Ftduino::I6);
     }
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
    //Return robot to conveyor unit
   ftduino.motor_counter_set_brake(Ftduino::M4, false);
   ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, x-40); //768
   while(ftduino.motor_counter_active(Ftduino::M2));
   if (y < 800){
     ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 750-y);  //650
   }
   else{
     ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, y-790);  //650
   }
   while(ftduino.motor_counter_active(Ftduino::M4));
  
   // Extend the robot's arm fully
   uint16_t button2 = ftduino.input_get(Ftduino::I7);
    //starts motor
    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX);
    while(!button2){
      button2 = ftduino.input_get(Ftduino::I7);
    }
    //turns off motor
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
   // Lower the robot's arm, wait for a period of three seconds, then raise the arm again 
   ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 90);
   while(ftduino.motor_counter_active(Ftduino::M4));
   
   if (_caller == "out_processing"){
     nh.loginfo("HBW Placed Material on Belt");
   }
   else if(_caller == "in_processing"){
     nh.loginfo("HBW Placed Box on the Belt");
   }
   
   if(!ftduino.input_get(Ftduino::I4)){
      ftduino.motor_set(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX);
      delay(2000);
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);

      delay(5000);
      
      if (_caller == "out_processing"){
        nh.loginfo("HBW Material is Picked by VGR");
      }
      else if (_caller == "in_processing"){
        nh.loginfo("HBW Material is Dropped by VGR");
      }
      
      ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX);
      delay(1000);
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);
      delay(1000);
      
      if (_caller == "out_processing"){
        nh.loginfo("Empty Box is Ready for HBW Pick Up");
      }
      else if (_caller == "in_processing"){
        nh.loginfo("Material is Ready for HBW Pick Up");
      }
  }}
   
   ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, 90);
   while(ftduino.motor_counter_active(Ftduino::M4));

   if (_caller == "out_processing"){
     nh.loginfo("HBW Picked up the Empty Box from the Belt");
   }
   else if (_caller == "in_processing"){
     nh.loginfo("HBW Picked up Material from the Belt");
   }
  
   // Retract the robot's arm fully
   uint16_t button3 = ftduino.input_get(Ftduino::I6);
    //turns motor back on, in other direction
    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX);
    while(!button3){
      button3 = ftduino.input_get(Ftduino::I6);
     }
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
    if (y < 800){
      ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, 750-y);
    }
    else{
      ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, y-790);
    }
    while(ftduino.motor_counter_active(Ftduino::M4));    
  
   // Return the robot to the inventory rack position 
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, x-40);
    while(ftduino.motor_counter_active(Ftduino::M2));   
   
    // Extend robot arm 
    uint16_t button4 = ftduino.input_get(Ftduino::I7);
    //starts motor
    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX);
    while(!button4){
      button4 = ftduino.input_get(Ftduino::I7);
    }
    //turns off motor
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
    
    nh.loginfo("HBW is Set to Home");
  
   // Lower the robot's arm, wait for a period of three seconds 
   ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 100);
   while(ftduino.motor_counter_active(Ftduino::M4));
   
   if (_caller == "out_processing"){
     nh.loginfo("HBW Empty Box is Back on the Shelf");
   }
   else if (_caller == "in_processing"){
     nh.loginfo("HBW Placed Material on the Shelf");
   }

   if (_caller == "out_processing"){
     //publish the shelf name to the topic what_is_empty:
     str_msg.data = empty_payload;
     update_empty.publish( &str_msg );
   }
   else if (_caller == "in_processing"){
     //publish the shelf name to the topic what_is_occupied:
     str_msg_occupied.data = occupied_payload;
     update_occupied.publish( &str_msg_occupied );
   }   
   nh.spinOnce();
     
   // Return to home position
   bring_back_home();
   nh.loginfo("HBW Robot is Set to Home");
  }

void out_processing(const std_msgs::String &payload_msg){

  strcpy(empty_payload, payload_msg.data);
  uint16_t x;
  uint16_t y;

  String shelf_loc = String(payload_msg.data);
  nh.loginfo(payload_msg.data);
  
  if(shelf_loc == "A1" && move_hbw){
    move_hbw = false;
    x = 810;
    y = 150; 
    move_robot_to_shelf(x, y, "out_processing");
 }

  else if(shelf_loc == "A2" && move_hbw){
    move_hbw = false;
    x = 1405;
    y = 150;
    move_robot_to_shelf(x, y, "out_processing");
 }

  else if(shelf_loc == "A3" && move_hbw){
    move_hbw = false;
    x = 2020;
    y = 150;
    move_robot_to_shelf(x, y, "out_processing");
 }

  else if(shelf_loc == "B1" && move_hbw){
    move_hbw = false;
    x = 810;
    y = 450;
    move_robot_to_shelf(x, y, "out_processing");
 }

  else if(shelf_loc == "B2" && move_hbw){
    move_hbw = false;
    x = 1405;
    y = 450;
    move_robot_to_shelf(x, y, "out_processing");
 }

  else if(shelf_loc == "B3" && move_hbw){
    move_hbw = false;
    x = 2020;
    y = 450;
    move_robot_to_shelf(x, y, "out_processing");
 }

  else if(shelf_loc == "C1" && move_hbw){
    move_hbw = false;
    x = 810;
    y = 840;
    move_robot_to_shelf(x, y, "out_processing");
 }

  else if(shelf_loc == "C2" && move_hbw){
    move_hbw = false;
    x = 1405;
    y = 840;
    move_robot_to_shelf(x, y, "out_processing");
 }

  else if(shelf_loc == "C3" && move_hbw){
    move_hbw = false;
    x = 2020;
    y = 840;
    move_robot_to_shelf(x, y, "out_processing");
 }
 
 move_hbw = true;
}

void in_processing(const std_msgs::String &payload_msg){

  strcpy(occupied_payload, payload_msg.data);
  uint16_t x;
  uint16_t y;

  String shelf_loc = String(payload_msg.data).substring(0,2);
   
  if(shelf_loc == "A1" && move_hbw){
    move_hbw = false;
    x = 810;
    y = 150; 
    move_robot_to_shelf(x, y, "in_processing");
 }

  else if(shelf_loc == "A2" && move_hbw){
    move_hbw = false;
    x = 1405;
    y = 150;
    move_robot_to_shelf(x, y, "in_processing");
 }

  else if(shelf_loc == "A3" && move_hbw){
    move_hbw = false;
    x = 2020;
    y = 150;
    move_robot_to_shelf(x, y, "in_processing");
 }

  else if(shelf_loc == "B1" && move_hbw){
    move_hbw = false;
    x = 810;
    y = 450;
    move_robot_to_shelf(x, y, "in_processing");
 }

  else if(shelf_loc == "B2" && move_hbw){
    move_hbw = false;
    x = 1405;
    y = 450;
    move_robot_to_shelf(x, y, "in_processing");
 }

  else if(shelf_loc == "B3" && move_hbw){
    move_hbw = false;
    x = 2020;
    y = 450;
    move_robot_to_shelf(x, y, "in_processing");
 }

  else if(shelf_loc == "C1" && move_hbw){
    move_hbw = false;
    x = 810;
    y = 840;
    move_robot_to_shelf(x, y, "in_processing");
 }

  else if(shelf_loc == "C2" && move_hbw){
    move_hbw = false;
    x = 1405;
    y = 840;
    move_robot_to_shelf(x, y, "in_processing");
 }

  else if(shelf_loc == "C3" && move_hbw){
    move_hbw = false;
    x = 2020;
    y = 840;
    move_robot_to_shelf(x, y, "in_processing");
 }
 
 move_hbw = true;
}

ros::Subscriber<std_msgs::String> new_order_sub("new_order", &out_processing);
ros::Subscriber<std_msgs::String> vgr_new_material_pub("vgr_new_material", &in_processing);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(new_order_sub);
  nh.subscribe(vgr_new_material_pub);
  nh.advertise(update_empty);
  nh.advertise(update_occupied);
  ftduino.init();
}

void loop() {
  // put your main code here, to run repeatedly:
 
 nh.spinOnce(); // IN-PROCESSING

 delay(250);
}
