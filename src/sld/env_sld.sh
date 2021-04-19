#!/bin/bash

export ROS_MASTER_URI=http://192.168.0.10:11311
export ROS_HOSTNAME=192.168.0.14

source /opt/ros/melodic/setup.bash
source /home/ubuntu/catkin_ws/devel/setup.bash

exec "$@"
