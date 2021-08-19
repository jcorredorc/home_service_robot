#!/bin/sh
xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_world.launch" &
sleep 10
xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_gazebo_rviz.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch"