#include <ros/ros.h>

#include "home_service_robot/AddMarkersOdom.hpp"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "add_marker_odom");
  ros::NodeHandle nodeHandle("~");

  AddMarkersOdom turtleAddMarkersOdom(nodeHandle);

  /*
  // se incluye en la clase!
  ros::ServiceServer start_stop_husky = nodeHandle.advertiseService("start_stop_husky_srv",
                &husky_highlevel_controller::HuskyHighlevelController::start_stop_husky_srv,
                &huskyHighlevelController);
  */
  ros::spin();
  return 0;
}