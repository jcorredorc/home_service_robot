#!/bin/sh
xterm  -e  " roslaunch home_service_robot turtlebot_world.launch " &
sleep 5
xterm  -e  " roslaunch home_service_robot amcl_demo.launch" & 
sleep 5
xterm  -e  " roslaunch home_service_robot view_navigation.launch" &
sleep 5
xterm  -e  " rosrun home_service_robot pick_objects_node" &
sleep 1
xterm -e   " rosrun home_service_robot add_markers_odom"
