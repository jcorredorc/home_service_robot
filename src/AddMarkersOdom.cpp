#include "home_service_robot/AddMarkersOdom.hpp"

AddMarkersOdom::AddMarkersOdom(ros::NodeHandle& nodeHandle)
{
  // cmd_vel_pub_ = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  odom_vis_pub_ = nodeHandle.advertise<visualization_msgs::Marker>("/visualization_marker", 0);
  odom_sub_ = nodeHandle.subscribe("/odom", 10, &AddMarkersOdom::odomMsgCallBack, this);
  // bumper_sub_ = nodeHandle.subscribe("/bumper", 1, &AddMarkersOdom::bumperMsgCallBack, this);
  // AddMarkersOdom::rotateAngleIncrement(1, 1.5707, false);
  // rotateRelativeAngle(0.5, angles::from_degrees(50), true);
  pickup_pose_.position.x = 4.1003279686;
  pickup_pose_.position.y = 3.93584132195;
  pickup_pose_.position.z = 0.0;
  pickup_pose_.orientation.x = 0.0;
  pickup_pose_.orientation.y = 0.0;
  pickup_pose_.orientation.z = 0.999754962967;
  pickup_pose_.orientation.w = -0.0221362603563;
  dropoff_pose_.position.x = -2.26904654503;
  dropoff_pose_.position.y = 0.0299424827099;
  dropoff_pose_.position.z = 0.0;
  dropoff_pose_.orientation.x = 0.0;
  dropoff_pose_.orientation.y = 0.0;
  dropoff_pose_.orientation.z = 0.999979287476;
  dropoff_pose_.orientation.w = 0.00643619605022;
  status_pickup_ = false;
}

void AddMarkersOdom::odomMsgCallBack(const nav_msgs::Odometry::ConstPtr& msg_odom)
{
  ROS_INFO("header frame:  %s", msg_odom->header.frame_id.c_str());
  ROS_INFO("child frame: %s", msg_odom->child_frame_id.c_str());
  ROS_INFO("x: %f", msg_odom->pose.pose.position.x);
  ROS_INFO("y: %f", msg_odom->pose.pose.position.y);
  // ROS_INFO("z: %f", msg_odom->pose.pose.orientation.z);
  // ROS_INFO("Twist_x %f", msg_odom->twist.twist.angular.x);
  turtlebot_pose_ = msg_odom->pose.pose;
  // robotino_yaw_ = getYaw(turtlebot_pose_);
  ROS_INFO("turtle_pos_.position.x: %f", turtlebot_pose_.position.x);
  turtlebot_marker_delivery(turtlebot_pose_);
  // ROS_INFO("yaw: [%f]rad | [%f]deg", getYaw(turtlebot_pose_), angles::to_degrees(getYaw(turtlebot_pose_)));
  // ROS_INFO("yaw: [%f] | norm: [%f] | norm+: [%f]", angles::to_degrees(getYaw(turtlebot_pose_)),
  //  angles::to_degrees(angles::normalize_angle(getYaw(turtlebot_pose_))),
  //  angles::to_degrees((angles::normalize_angle_positive(getYaw(turtlebot_pose_)))));
}

int AddMarkersOdom::odomVisMarker(const geometry_msgs::Pose marker_pose, bool show_marker = true)
{
  visualization_msgs::Marker marker;
  marker.header.frame_id = "odom";
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
  // ROS_INFO("ok! markerpose: [%f]", marker_pose.position.x);
  // euler_distance(marker_pose, pickup_pose_);
  // ROS_INFO("delivery dist : %f", euler_distance(marker_pose, pickup_pose_));
  float offset = 0.1;
  if (euler_distance(marker_pose, pickup_pose_) <= offset && status_pickup_ == false)
  {
    ROS_INFO_ONCE("pickup reached. Hide marker and wait 5 sec.");
    odomVisMarker(pickup_pose_, false);
    // ROS_INFO("Waiting 5 sec. to show the pickup marker");
    ros::Duration(5.0).sleep();  // Wait to pickup the object
    status_pickup_ = true;
    // odomVisMarker(dropoff_pose_, true);
  }
  else if (euler_distance(marker_pose, dropoff_pose_) <= offset)
  {
    ROS_INFO_ONCE("arrived to dropoff ...");
    odomVisMarker(dropoff_pose_, true);
  }
  else if (!status_pickup_)
  {
    ROS_INFO_ONCE("traveling to pickup ...");
    odomVisMarker(pickup_pose_);
  }
  // odomVisMarker(marker_pose);
}

float AddMarkersOdom::euler_distance(const geometry_msgs::Pose point_1, const geometry_msgs::Pose point_2)
{
  // ROS_INFO("point1.x [%f], point2.x [%f]", point_1.position.x, point_2.position.x);
  // ROS_INFO("euler_distance: [%f]",
  // float distance = 0;
  // distance = sqrt(pow(point_1.position.x - point_2.position.x, 2) + pow(point_1.position.y - point_2.position.y, 2));
  //  sqrt(pow(point_1.position.x - point_2.position.x, 2) + pow(point_1.position.y - point_2.position.y, 2)));
  return sqrt(pow(point_1.position.x - point_2.position.x, 2) + pow(point_1.position.y - point_2.position.y, 2));
  // return distance;
}

// double AddMarkersOdom::getYaw(const geometry_msgs::Pose& pose_msg)
// {
//   tf2::Quaternion q(pose_msg.orientation.x, pose_msg.orientation.y, pose_msg.orientation.z, pose_msg.orientation.w);
//   tf2::Matrix3x3 m(q);
//   double roll, pitch, yaw;
//   m.getRPY(roll, pitch, yaw);
//   // ROS_INFO_ONCE("yaw: [%f]rad ; [%f]deg; acos(w)=[%f]deg", g_yaw, radians2degrees(g_yaw),
//   // radians2degrees(2 * acos(g_robotino_pose.orientation.w)));
//   ROS_WARN_COND(isnan(yaw), "Warning: yaw isnan!");
//   return yaw;
// }

// void AddMarkersOdom::rotateRelativeAngle(double angular_vel, double relative_angle, bool clockwise = false)
// {
//   double error = 0;
//   double init_yaw = robotino_yaw_;
//   updateCommandVelocity(0, 0, angular_vel);
//   double ref = init_yaw + relative_angle;
//   ros::Rate loop_rate(100);
//   do
//   {
//     error = ref - robotino_yaw_;
//     if (error >= 0)
//       updateCommandVelocity(0, 0, angular_vel);
//     else
//       updateCommandVelocity(0, 0, 0);
//     // ROS_INFO_ONCE("rel_angle: [%f]deg | odom_angle: [%f]deg | error: [%f]rad | yaw_init :[%f]deg ",
//     //               angles::to_degrees(relative_angle), angles::to_degrees(robotino_yaw_), error,
//     //               angles::to_degrees(init_yaw));
//     // ROS_INFO("ref: [%f] | ",angles::to_degrees(ref)));
//     ROS_INFO("init_yaw [%f]deg | rel_ang [%f]deg |  ref: [%f]deg | error: [%f]deg ", angles::to_degrees(init_yaw),
//              angles::to_degrees(relative_angle), angles::to_degrees(ref), angles::to_degrees(error));
//     ROS_INFO("norm_init_yaw + rel_ang : [%f]deg",
//              angles::to_degrees(angles::normalize_angle_positive(init_yaw + relative_angle)));
//     ros::spinOnce();
//     loop_rate.sleep();
//   } while (ros::ok() && error > 0.00);
//   ros::shutdown();
// }

/*
void AddMarkersOdom::rotateAbsoluteAngle(double angular_vel, double relative_angle, bool clockwise = false)
{
  if (isnan(robotino_yaw_))
  {
    ROS_INFO("paila yaw");
  };
  double error = 0.001;
  double init_yaw = robotino_yaw_;
  updateCommandVelocity(0, 0, angular_vel);
  ros::Rate loop_rate(100);
  do
  {
    // ROS_INFO_ONCE("ok rotateRelativeAngle ..");
    // if (!isnan(getYaw(turtlebot_pose_)))
    error = relative_angle - robotino_yaw_;
    if (error >= 0.001)
      updateCommandVelocity(0, 0, angular_vel);
    else
      updateCommandVelocity(0, 0, 0);
    ROS_INFO("rel_angle: [%f]deg | odom_angle: [%f]deg | error: [%f]rad | yaw_init :[%f]deg ",
             angles::to_degrees(relative_angle), angles::to_degrees(robotino_yaw_), error,
             angles::to_degrees(init_yaw));
    // angles::normalize_angle_positive()
    ros::spinOnce();
    loop_rate.sleep();
  } while (ros::ok() && error > 0.00);
  ros::shutdown();
}
 */

// void AddMarkersOdom::updateCommandVelocity(double vel_x, double vel_y, double vel_phi)
// {
//   geometry_msgs::Twist vel_msg;
//   vel_msg.linear.x = vel_x;
//   vel_msg.linear.y = vel_y;
//   vel_msg.linear.z = 0;

//   vel_msg.angular.x = 0;
//   vel_msg.angular.y = 0;
//   vel_msg.angular.z = vel_phi;
//   cmd_vel_pub_.publish(vel_msg);
// }

/*
//Este metodo no tiene buen desempeño. La velocidad comandada no es precisa y los tiempos de ejecución no son tan en
//tiempo real
void AddMarkersOdom::rotateAngleIncrement(double angular_vel, double relative_angle, bool clockwise = false)
{
  geometry_msgs::Twist vel_msg;
  // set a random linear velocity in the x-axis
  vel_msg.linear.x = 0;
  vel_msg.linear.y = 0;
  vel_msg.linear.z = 0;
  // set a random angular velocity in the y-axis
  vel_msg.angular.x = 0;
  vel_msg.angular.y = 0;

  if (clockwise)
    vel_msg.angular.z = -abs(angular_vel);
  else
    vel_msg.angular.z = abs(angular_vel);

  double current_angle = 0.0;
  double t0 = ros::Time::now().toSec();
  ros::Rate loop_rate(1);
  do
  {
    cmd_vel_pub_.publish(vel_msg);
    // .publish(vel_msg);
    double t1 = ros::Time::now().toSec();
    current_angle = angular_vel * (t1 - t0);
    // current_angle = 0.90 * (t1 - t0);
    // current_angle = getYaw(turtlebot_pose_);
    ROS_INFO("odom_angle: [%f]deg | current_angle: [%f]deg | relative_angle: [%f]deg",
             angles::to_degrees(getYaw(turtlebot_pose_)), angles::to_degrees(current_angle),
             angles::to_degrees(relative_angle));
    // ROS_INFO("t0= [%f] - t1 = [%f] := [%f]", t0, t1, t1 - t0);
    ros::spinOnce();
    loop_rate.sleep();
  } while (current_angle < relative_angle);

  vel_msg.angular.z = 0;
  cmd_vel_pub_.publish(vel_msg);
}
 */

AddMarkersOdom::~AddMarkersOdom()
{
}