#include "home_service_robot/AddMarkersOdom.hpp"

AddMarkersOdom::AddMarkersOdom(ros::NodeHandle& nodeHandle)
{
  odom_vis_pub_ = nodeHandle.advertise<visualization_msgs::Marker>("/visualization_marker", 0);
  odom_sub_ = nodeHandle.subscribe("/odom", 10, &AddMarkersOdom::odomMsgCallBack, this);
  pickup_pose_.position.x = 4.1003279686;
  pickup_pose_.position.y = 3.93584132195;
  pickup_pose_.position.z = 0.0;
  pickup_pose_.orientation.x = 0.0;
  pickup_pose_.orientation.y = 0.0;
  pickup_pose_.orientation.z = 1;
  pickup_pose_.orientation.w = -0.0221362603563;
  dropoff_pose_.position.x = -2.26904654503;
  dropoff_pose_.position.y = 0.0299424827099;
  dropoff_pose_.position.z = 0.0;
  dropoff_pose_.orientation.x = 0.0;
  dropoff_pose_.orientation.y = 0.0;
  dropoff_pose_.orientation.z = 1;
  dropoff_pose_.orientation.w = 0.00643619605022;
  status_pickup_ = false;
}

void AddMarkersOdom::odomMsgCallBack(const nav_msgs::Odometry::ConstPtr& msg_odom)
{
  ROS_INFO_ONCE("header frame:  %s", msg_odom->header.frame_id.c_str());
  ROS_INFO_ONCE("child frame: %s", msg_odom->child_frame_id.c_str());
  ROS_INFO_ONCE("x: %f", msg_odom->pose.pose.position.x);
  ROS_INFO_ONCE("y: %f", msg_odom->pose.pose.position.y);
  turtlebot_pose_ = msg_odom->pose.pose;
  ROS_INFO_ONCE("turtle_pos_.position.x: %f", turtlebot_pose_.position.x);
  turtlebot_marker_delivery(turtlebot_pose_);
}

int AddMarkersOdom::odomVisMarker(const geometry_msgs::Pose marker_pose, bool show_marker = true)
{
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time();
  marker.ns = "my_namespace";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::CUBE;
  if (show_marker)
    marker.action = visualization_msgs::Marker::ADD;
  else
    marker.action = visualization_msgs::Marker::DELETE;
  marker.pose = marker_pose;
  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.scale.z = 0.5;
  marker.color.a = 0.8;  // Don't forget to set the alpha!
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 0.0;
  // only if using a MESH_RESOURCE marker type:
  // marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
  // marker.lifetime = ros::Duration(5);
  // Publish the marker
  while (odom_vis_pub_.getNumSubscribers() < 1)
  {
    if (!ros::ok())
    {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }
  odom_vis_pub_.publish(marker);
  return 1;
}

void AddMarkersOdom::turtlebot_marker_delivery(const geometry_msgs::Pose marker_pose)
{
  float offset_dist = 0.51;
  // ROS_INFO("distance pickup %f",euler_distance(marker_pose, pickup_pose_));
  // ROS_INFO("distance dropoff %f",euler_distance(marker_pose, dropoff_pose_));
  if (euler_distance(marker_pose, pickup_pose_) <= offset_dist && status_pickup_ == false)
  {
    ROS_INFO_ONCE("pickup reached. Hide marker and wait 5 sec.");
    ros::Duration(5.0).sleep();  // Wait to pickup the object
    status_pickup_ = true;
    odomVisMarker(pickup_pose_, false);
  }else if (euler_distance(marker_pose, dropoff_pose_) <= offset_dist)
  {
    ROS_INFO_ONCE("arriving to dropoff ...");
    ros::Duration(3.0).sleep();  // Wait to dropoff the object
    odomVisMarker(dropoff_pose_, true); // show marker
  }
  else if (!status_pickup_)
  {
    ROS_INFO_ONCE("traveling ...");
    odomVisMarker(pickup_pose_);
  }
}

float AddMarkersOdom::euler_distance(const geometry_msgs::Pose point_1, const geometry_msgs::Pose point_2)
{
  return sqrt(pow(point_1.position.x - point_2.position.x, 2) + pow(point_1.position.y - point_2.position.y, 2));
}

AddMarkersOdom::~AddMarkersOdom()
{
}
