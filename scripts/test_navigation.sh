#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:="/home/workspace/catkin_ws/src/home_service_robot/worlds/world_mapping_features.world"" &
sleep 10
xterm  -e  " export TURTLEBOT_GAZEBO_MAP_FILE=/home/workspace/gmapping_01.yaml ; roslaunch turtlebot_gazebo amcl_demo.launch" & 
sleep 8
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch"
