# ft_industry4_raspi
Implementation of the Fischertechnik Industry 4.0 kit using ftDuino controllers and Raspberry Pi's

## Prerequisites
```shel
snap install mosquitto
sudo apt install python-rospkg
pip install rospkg
sudo apt install ros-melodic-rosbridge-library
```
### MQTT Bridge ROS Package
```shell
cd ~/catkin_ws/src
git clone --depth 1 https://github.com/groove-x/mqtt_bridge.git
cd mqtt_bridge
pip3 install -r requirements.txt
cd ../..
catkin_make
```
or
```shell
sudo apt install ros-melodic-mqtt-bridge
```
