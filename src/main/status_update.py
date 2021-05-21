#!/usr/bin/env python

import json
import time
from os import path
import rospy
from std_msgs.msg import String

def talker(target_loc, terminate):
    pub = rospy.Publisher('provide_empty_loc_back', String, queue_size=1)
    rate = rospy.Rate(10) # 10hz
    while not terminate:
        connections = pub.get_num_connections()
        #subcriber_name = 
        if connections > 0:
            pub.publish(target_loc)
            rospy.loginfo('Published {}'.format(target_loc))
            terminate = True
        else:
            print('Waiting for subscribers')
            rate.sleep()

def remove_item_cb(msg):
    if msg.data:
        # Read existing data file:
        with open(file_path, 'r') as fp:
            r_data = json.load(fp)

        # Update the existing data file with the new data:
        r_data[msg.data] = "NA"
        
        with open(file_path, 'wb') as fp:
            json.dump(r_data, fp, sort_keys=True, indent=4)

        rospy.loginfo('Status updated successfully')

def add_item_cb(msg):
    if msg.data:
        # Read existing data file:
        with open(file_path, 'r') as fp:
            r_data = json.load(fp)

        # Update the existing data file with the new data:
        r_data[msg.data[:2]] = msg.data[3:].lower()
        
        with open(file_path, 'wb') as fp:
            json.dump(r_data, fp, sort_keys=True, indent=4)

        rospy.loginfo('Status updated successfully')

def provide_empty_loc_cb(msg):
    if msg.data == "vgr asks for free location":
        # Read existing data file:
        with open(file_path, 'r') as fp:
            r_data = json.load(fp)
        free_loc = (list(r_data.keys())[list(r_data.values()).index("NA")])
        talker(free_loc, False)

def listener():
    rospy.init_node('status_update', anonymous=True)

    rospy.Subscriber('what_is_empty'    , String, remove_item_cb)
    rospy.Subscriber('what_is_occupied' , String, add_item_cb)
    rospy.Subscriber('provide_empty_loc', String, provide_empty_loc_cb)
    
    rospy.spin()

if __name__ == "__main__":
    file_path = path.join(path.abspath(path.dirname(__file__)), "data.json")
    rospy.loginfo('Status updater launched successfully')
    listener()
