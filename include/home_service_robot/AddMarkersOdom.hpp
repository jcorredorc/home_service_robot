#pragma once

#include "geometry_msgs/Pose.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
#include "visualization_msgs/Marker.h"

class AddMarkersOdom
{
private:
  // ROS NodeHandle
  ros::NodeHandle nh_;

  // ROS Parameters

  // ROS Time

  // ROS Topic Publishers
  // ros::Publisher cmd_vel_pub_;
  ros::Publisher odom_vis_pub_;

  // ROS Topic Subscribers
  ros::Subscriber odom_sub_;

  // Variables
  geometry_msgs::Pose turtlebot_pose_;
  geometry_msgs::Pose pickup_pose_;
  geometry_msgs::Pose dropoff_pose_;
  bool status_pickup_;

  // Function prototypes
  void odomMsgCallBack(const nav_msgs::Odometry::ConstPtr& msg_odom);
  int odomVisMarker(const geometry_msgs::Pose marker_pose, bool show_marker);
  void turtlebot_marker_delivery(const geometry_msgs::Pose marker_pose);
  float euler_distance(const geometry_msgs::Pose point_1, const geometry_msgs::Pose point_2);

public:
  AddMarkersOdom(ros::NodeHandle& nodeHandle);
  ~AddMarkersOdom();
};