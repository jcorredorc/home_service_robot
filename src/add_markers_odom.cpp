#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
  

 ros::Publisher marker_pub;
 geometry_msgs::Pose turtlebot_pickup;
 geometry_msgs::Pose turtlebot_dropoff;

void odomVisMarker(const geometry_msgs::Pose pose_marker);
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg_odom);

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //ros::Rate r(1);
  ros::Subscriber odom_sub = n.subscribe("/odom",10, odomCallback);
 
    turtlebot_pickup.position.x = -2.26904654503;
    turtlebot_pickup.position.y = 0.0299424827099;
    turtlebot_pickup.position.z = 0.0;
    turtlebot_pickup.orientation.x = 0.0;
    turtlebot_pickup.orientation.y = 0.0;
    turtlebot_pickup.orientation.z = 1.0;
    turtlebot_pickup.orientation.w = 0.00643619605022;
    odomVisMarker(turtlebot_pickup);
    ros::spin();
return 0;
}


void odomCallback(const nav_msgs::Odometry::ConstPtr& msg_odom)
{
  ROS_INFO_ONCE("header frame:  %s", msg_odom->header.frame_id.c_str());
  ROS_INFO_ONCE("child frame: %s", msg_odom->child_frame_id.c_str());
  ROS_INFO_ONCE("x: %f", msg_odom->pose.pose.position.x);
  ROS_INFO_ONCE("y: %f", msg_odom->pose.pose.position.y);
  ROS_INFO_ONCE("z: %f", msg_odom->pose.pose.position.z);
  ROS_INFO_ONCE("Twist_w %f", msg_odom->twist.twist.angular.z);
  ROS_INFO_ONCE("-------------------");
  
}


void odomVisMarker(const geometry_msgs::Pose pose_marker)
{
  visualization_msgs::Marker marker;
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "my_namespace";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::CUBE;
  marker.action = visualization_msgs::Marker::ADD;
  //marker.pose = pose_marker;
  marker.pose.position.x = pose_marker.position.x;
  marker.pose.position.z = pose_marker.position.z;
  marker.pose.orientation.x = pose_marker.orientation.x;
  marker.pose.orientation.y = pose_marker.orientation.y;
  marker.pose.orientation.z = pose_marker.orientation.z;
  marker.pose.orientation.w = pose_marker.orientation.w;
  marker.scale.x = 0.7;
  marker.scale.y = 0.08;
  marker.scale.z = 0.08;
  marker.color.a = 0.8;  // Don't forget to set the alpha!
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 0.0;
  // only if using a MESH_RESOURCE marker type:
  // marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
  marker_pub.publish(marker);
}
