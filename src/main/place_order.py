#!/usr/bin/env python

import json
import sys
from os import path
import rospy
from std_msgs.msg import String

# Define the publishing function:
def talker(target_loc, terminate):
    pub = rospy.Publisher('new_order', String, queue_size=1)
    rospy.init_node('order', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not terminate:
        connections = pub.get_num_connections()
        if connections > 0:
            pub.publish(target_loc)
            rospy.loginfo('Published {}'.format(target_loc))
            terminate = True
        else:
            print('Waiting for subscribers')
            rate.sleep()


# Create new data file:
def create_data_file():
    data = {'A1': 'white', 'A2': 'red', 'A3': 'blue',
            'B1': 'white', 'B2': 'red', 'B3': 'blue',
            'C1': 'white', 'C2': 'red', 'C3': 'blue'}

    with open(file_path, 'wb') as fp:
        json.dump(data, fp, sort_keys=True, indent=4)


if __name__ == '__main__':
#    create_data_file()
    file_path = path.join(path.abspath(path.dirname(__file__)), "data.json")
# Read existing data file:
    with open(file_path, 'r') as fp:
        r_data = json.load(fp)

    u_order = sys.argv[1].lower()
    try:
        target_loc = (list(r_data.keys())[list(r_data.values()).index(u_order)])
        talker(target_loc, False)
    except ValueError:
        print('HBW Error: No "{}" material existing on the shelf'.format(u_order))
    except rospy.ROSInterruptException:
        pass
