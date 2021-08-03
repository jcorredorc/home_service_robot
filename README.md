# home_service_robot

Kinect distro ROS

## Install

```
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

### Test the installed packages

```
roslaunch turtlebot_gazebo turtlebot_world.launch
roslaunch turtlebot_gazebo gmapping_demo.launch
roslaunch turtlebot_teleop keyboard_teleop.launch
roslaunch turtlebot_rviz_launchers view_navigation.launch
```

## Usage

run script

```
sh scripts/test_slam.sh
```

Create a map driving the robot throught the world. before close de gmapping and rviz terminals, save the map,

```
rosrun map_server map_saver -f ~/gmapping_01
```


