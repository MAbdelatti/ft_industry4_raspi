// Use the following line if you have a Leonardo, FtDuino or MKR1000
#define USE_USBCON

#include <ros.h>
#include <std_msgs/String.h>
#include <Ftduino.h>

ros::NodeHandle nh;
bool move_hbw = true;

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

void move_robot_outprocessing(uint16_t x, uint16_t y){
  nh.loginfo("HBW Received an Order");
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
    nh.loginfo("HBW Picked Up Material");
  
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
   nh.loginfo("HBW Placed Material on Belt");
   
   if(!ftduino.input_get(Ftduino::I4)){
      ftduino.motor_set(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX);
      delay(2000);
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);

      delay(5000);
      
      nh.loginfo("HBW Material is Picked by VGR");
      
      ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX);
      delay(1000);
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);
      delay(1000);
      nh.loginfo("HBW Empty Box is Ready for Pick Up");
  }}
   
   ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, 90);
   while(ftduino.motor_counter_active(Ftduino::M4));
   nh.loginfo("HBW Picked Up the Empty Box");
  
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
   nh.loginfo("HBW Empty Box is Back on the Shelf");
     
   // Return to home position
   bring_back_home();
   nh.loginfo("HBW Robot is Set to Home");
  }


void out_processing(const std_msgs::String &payload_msg){
  const char* const_text = "Heading to location: ";
  char log_message[256];
  strcpy(log_message, const_text);
  strcpy(log_message, payload_msg.data);

  nh.loginfo(log_message);
  
  if(String(payload_msg.data)=="A1" && move_hbw){
    move_hbw = false;
    uint16_t x = 810;
    uint16_t y = 100;
    move_robot_outprocessing(x, y); 
 }

  else if(String(payload_msg.data)=="A2" && move_hbw){
    move_hbw = false;
    uint16_t x = 1405;
    uint16_t y = 100;
    move_robot_outprocessing(x, y); 
 }

  else if(String(payload_msg.data)=="A3" && move_hbw){
    move_hbw = false;
    uint16_t x = 2020;
    uint16_t y = 100;
    move_robot_outprocessing(x, y); 
 }

  else if(String(payload_msg.data)=="B1" && move_hbw){
    move_hbw = false;
    uint16_t x = 810;
    uint16_t y = 450;
    move_robot_outprocessing(x, y); 
 }

  else if(String(payload_msg.data)=="B2" && move_hbw){
    move_hbw = false;
    uint16_t x = 1405;
    uint16_t y = 450;
    move_robot_outprocessing(x, y); 
 }

  else if(String(payload_msg.data)=="B3" && move_hbw){
    move_hbw = false;
    uint16_t x = 2020;
    uint16_t y = 450;
    move_robot_outprocessing(x, y); 
 }

  else if(String(payload_msg.data)=="C1" && move_hbw){
    move_hbw = false;
    uint16_t x = 810;
    uint16_t y = 840;
    move_robot_outprocessing(x, y); 
 }

  else if(String(payload_msg.data)=="C2" && move_hbw){
    move_hbw = false;
    uint16_t x = 1405;
    uint16_t y = 840;
    move_robot_outprocessing(x, y); 
 }

  else if(String(payload_msg.data)=="C3" && move_hbw){
    move_hbw = false;
    uint16_t x = 2020;
    uint16_t y = 840;
    move_robot_outprocessing(x, y);
 }
 move_hbw = true;
}

void in_processing(const std_msgs::String &payload_msg){
  if (payload_msg.data){
    
   nh.loginfo("HBW is Preparing an Empty Box"); 
   //Move robot from home position to first inventory rack position
   
   if(ftduino.input_get(Ftduino::I5)){
   ftduino.motor_counter_set_brake(Ftduino::M2, false);
   ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 810);
   while(ftduino.motor_counter_active(Ftduino::M2));
   ftduino.motor_counter_set_brake(Ftduino::M4, false);
   ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 100);
   while(ftduino.motor_counter_active(Ftduino::M4));
   
   // Extend robot arm 
    uint16_t button6 = ftduino.input_get(Ftduino::I7);
    //starts motor
    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX);
    while(!button6){
      button6 = ftduino.input_get(Ftduino::I7);
    }
    //turns off motor
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
    // Raise robot arm
    
    ftduino.motor_counter_set_brake(Ftduino::M4, false);
    ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, 100);
    while(ftduino.motor_counter_active(Ftduino::M4));
    nh.loginfo("HBW Picked a Box from The Shelf");
  
    // Retract robot arm
    uint16_t button7 = ftduino.input_get(Ftduino::I6);
    //turns motor back on, in other direction
    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX);
    while(!button7){
      button7 = ftduino.input_get(Ftduino::I6);
     }
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
    //Return robot to conveyor unit
  
   ftduino.motor_counter_set_brake(Ftduino::M4, false);
   ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 768);
   while(ftduino.motor_counter_active(Ftduino::M2));
   ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 650);
   while(ftduino.motor_counter_active(Ftduino::M4));
  
   // Extend the robot's arm fully
   uint16_t button8 = ftduino.input_get(Ftduino::I7);
    //starts motor
    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX);
    while(!button8){
      button8 = ftduino.input_get(Ftduino::I7);
    }
    //turns off motor
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
    nh.loginfo("HBW Placed Box on the Belt");
  
   // Lower the robot's arm, wait for a period of three seconds, then raise the arm again 
   ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 90);
   while(ftduino.motor_counter_active(Ftduino::M4));
   
   if(!ftduino.input_get(Ftduino::I4)){
      ftduino.motor_set(Ftduino::M1, Ftduino::LEFT, Ftduino::MAX);
      delay(1000);
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);
      delay(5000);
      ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT, Ftduino::MAX);
      delay(1000);
      ftduino.motor_set(Ftduino::M1, Ftduino::OFF, Ftduino::MAX);
      delay(1000);
  
  }}
   
   ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, 90);
   while(ftduino.motor_counter_active(Ftduino::M4));
  
   // Retract the robot's arm fully
   uint16_t button9 = ftduino.input_get(Ftduino::I6);
    //turns motor back on, in other direction
    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX);
    while(!button9){
      button9 = ftduino.input_get(Ftduino::I6);
     }
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
    
    ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, 650);
    while(ftduino.motor_counter_active(Ftduino::M4));
    nh.loginfo("HBW Picked Material from the Belt");
    
  
   // Return the robot to the inventory rack position 
    ftduino.motor_counter(Ftduino::M2, Ftduino::LEFT, Ftduino::MAX, 768);
    while(ftduino.motor_counter_active(Ftduino::M2));
   
    // Extend robot arm 
    uint16_t button10 = ftduino.input_get(Ftduino::I7);
    //starts motor
    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT, Ftduino::MAX);
    while(!button10){
      button10 = ftduino.input_get(Ftduino::I7);
    }
    //turns off motor
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
   // Lower the robot's arm, wait for a period of three seconds 
   ftduino.motor_counter(Ftduino::M4, Ftduino::LEFT, Ftduino::MAX, 100);
   while(ftduino.motor_counter_active(Ftduino::M4));
   nh.loginfo("HBW Placed Material on the Shelf");
  
   // Retract the robot's arm fully
   uint16_t button11 = ftduino.input_get(Ftduino::I6);
    //turns motor back on, in other direction
    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT, Ftduino::MAX);
    while(!button11){
      button11 = ftduino.input_get(Ftduino::I6);
     }
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF, Ftduino::MAX);
  
   // Return to home position
   
   ftduino.motor_counter(Ftduino::M4, Ftduino::RIGHT, Ftduino::MAX, 100);
   while(ftduino.motor_counter_active(Ftduino::M4));
   ftduino.motor_counter(Ftduino::M2, Ftduino::RIGHT, Ftduino::MAX, 810);
   while(ftduino.motor_counter_active(Ftduino::M2));
   nh.loginfo("HBW Robot is Set to Home");
  
   // END OF IN-PROCESSING
  }
}

ros::Subscriber<std_msgs::String> new_order_sub("new_order", &out_processing);
ros::Subscriber<std_msgs::String> vgr_new_material_pub("vgr_new_material", &in_processing);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(new_order_sub);
  nh.subscribe(vgr_new_material_pub);
  ftduino.init();
}

void loop() {
  // put your main code here, to run repeatedly:
 
 nh.spinOnce(); // IN-PROCESSING

// out_processing();/

 delay(250);
}
