#!/bin/sh
#xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:="/home/workspace/catkin_ws/src/home_service_robot/worlds/world_mapping_features.world"" &
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:="$(find home_service_robot)/worlds/world_mapping_features.world"" &
sleep 8
xterm  -e  " roslaunch turtlebot_gazebo gmapping_demo.launch" & 
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot_teleop keyboard_teleop.launch"


#launch turtlebot_gazebo turtlebot_world.launch world_file:="$(find home_service_robot)/worlds/world_mapping_features.world"
