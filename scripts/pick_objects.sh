#!/bin/sh
xterm  -e  " roslaunch home_service_robot turtlebot_world.launch " &
sleep 10
xterm  -e  " roslaunch home_service_robot amcl_demo.launch" & 
sleep 8
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 10
xterm  -e  " rosrun home_service_robot pick_objects_node"
