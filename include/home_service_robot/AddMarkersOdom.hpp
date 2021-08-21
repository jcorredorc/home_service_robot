#pragma once

// #include "angles/angles.h"
#include "geometry_msgs/Pose.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
// #include "std_msgs/Bool.h"
// #include "tf2/LinearMath/Matrix3x3.h"
// #include "tf2/LinearMath/Quaternion.h"
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
  // ros::Subscriber bumper_sub_;

  // Variables
  geometry_msgs::Pose turtlebot_pose_;
  geometry_msgs::Pose pickup_pose_;
  geometry_msgs::Pose dropoff_pose_;
  bool status_pickup_;
  // double robotino_yaw_;

  // Function prototypes
  // void updateCommandVelocity(double vel_x, double vel_y, double angular);
  void odomMsgCallBack(const nav_msgs::Odometry::ConstPtr& msg_odom);
  // void bumperMsgCallBack(const std_msgs::Bool::ConstPtr& bumper);
  // double getYaw(const geometry_msgs::Pose& pose_msg);
  // void rotateAngleIncrement(double angular_speed, double relative_angle, bool clockwise);
  // void rotateRelativeAngle(double angular_speed, double relative_angle, bool clockwise);
  int odomVisMarker(const geometry_msgs::Pose marker_pose, bool show_marker);
  void turtlebot_marker_delivery(const geometry_msgs::Pose marker_pose);
  float euler_distance(const geometry_msgs::Pose point_1, const geometry_msgs::Pose point_2);

public:
  AddMarkersOdom(ros::NodeHandle& nodeHandle);
  ~AddMarkersOdom();
};