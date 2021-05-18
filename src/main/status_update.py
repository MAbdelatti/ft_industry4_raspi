#!/usr/bin/env python

import json
import rospy
from std_msgs.msg import String

def remove_item_cb(msg):
    if msg.data:
        # Read existing data file:
        with open('data.json', 'r') as fp:
            r_data = json.load(fp)

        # Update the existing data file with the new data:
        r_data[msg.data] = "NA"
        
        with open('data.json', 'wb') as fp:
            json.dump(r_data, fp, sort_keys=True, indent=4)

        rospy.loginfo('Status updated successfully')

def add_item_cb(msg):
    if msg.data:
        # Read existing data file:
        with open('data.json', 'r') as fp:
            r_data = json.load(fp)

        # Update the existing data file with the new data:
        r_data[msg.data[:2]] = msg.data[3:].lower()
        
        with open('data.json', 'wb') as fp:
            json.dump(r_data, fp, sort_keys=True, indent=4)

        rospy.loginfo('Status updated successfully')

def listener():
    rospy.init_node('status_update', anonymous=True)
    rospy.Subscriber('what_is_empty', String, remove_item_cb)
    rospy.Subscriber('what_is_occupied', String, add_item_cb)
    
    rospy.spin()

if __name__ == "__main__":
    rospy.loginfo('Status updater launched successfully')
    listener()
