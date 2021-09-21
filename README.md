# home_service_robot

**in progress ...** 


Noetic distro ROS

## Install

```
sudo apt install xterm

# gmapping isn't working yet -----
cd ~/catkin_ws/src/
git clone https://github.com/ros-perception/slam_gmapping -b melodic-devel
# or
# sudo apt install ros-noetic-slam-gmapping


cd ~/catkin_ws/src/
git clone https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git -b noetic-devel
git clone https://github.com/ROBOTIS-GIT/turtlebot3.git -b noetic-devel
cd ~/catkin_ws && catkin_make # catkin build

cd ~/catkin_ws/src/
git clone https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git
cd ~/catkin_ws && catkin_make # catkin build
```
<!-- 
git clone https://github.com/ros-perception/slam_gmapping
git clone https://github.com/turtlebot/turtlebot
git clone https://github.com/turtlebot/turtlebot_interactions
git clone https://github.com/turtlebot/turtlebot_simulator
cd ~/catkin_ws/
source devel/setup.bash
rosdep -i install gmapping
rosdep -i install turtlebot_teleop
rosdep -i install turtlebot_rviz_launchers
rosdep -i install turtlebot_gazebo
catkin_make // catkin build
source devel/setup.bash 

```
sudo apt-get install ros-kinetic-turtlebot ros-kinetic-turtlebot-apps ros-kinetic-turtlebot-interactions ros-kinetic-turtlebot-simulator ros-kinetic-kobuki-ftdi ros-kinetic-ar-track-alvar-msgs
```

The vm had an error, but this shouldn't be present in a fresh install

```
git clone git://github.com/ros/rospkg.git
python setup.py install --user
``` 
or (this works for me!)

```
apt-get install python-rospkg
```
-->

### Test the installed packages

```
roslaunch turtlebot3_gazebo turtlebot3_world.launch
roslaunch turtlebot3_gazebo turtlebot3_gazebo_rviz.launch
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch
```
<!-- roslaunch turtlebot3_gazebo gmapping_demo.launch
roslaunch turtlebot_rviz_launchers view_navigation.launch -->

## Usage

run script

```
sh scripts/test_marker.sh
```
<!-- 
Create a map driving the robot throught the world. before close de gmapping and rviz terminals, save the map,

```
rosrun map_server map_saver -f ~/gmapping_01
``` -->


