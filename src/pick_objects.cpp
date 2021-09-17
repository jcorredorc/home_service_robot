#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  bool state_goal_reached = 0;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);


  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0)) && ros::ok()){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 4.1003279686;
  goal.target_pose.pose.position.y = 3.93584132195;
  goal.target_pose.pose.position.z = 0.0;

  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 1;
  goal.target_pose.pose.orientation.w = -0.0221362603563;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    	{
	ROS_INFO("Hooray, the turtlebot moved to pickup zone");
	state_goal_reached = 1;	
	}
  else
	{
    	ROS_INFO("The turtlebot failed to move to pickup zone");
	state_goal_reached = 0;	
	}

  if (state_goal_reached)
	{
		ROS_INFO("Waiting 5 sec. to pickup the object");
		ros::Duration(5.0).sleep(); // Wait to pickup the object
		goal.target_pose.header.stamp = ros::Time::now();

  		// Define a position and orientation for the robot to reach
		  goal.target_pose.pose.position.x = -2.26904654503;
		  goal.target_pose.pose.position.y = 0.0299424827099;
		  goal.target_pose.pose.position.z = 0.0;

		  goal.target_pose.pose.orientation.x = 0.0;
		  goal.target_pose.pose.orientation.y = 0.0;
		  goal.target_pose.pose.orientation.z = 1;
		  goal.target_pose.pose.orientation.w = 0.00643619605022;
		

   		// Send the goal position and orientation for the robot to reach
  		ROS_INFO("Sending dropoff");
		  ac.sendGoal(goal);

		  // Wait an infinite time for the results
		  ac.waitForResult();

		  // Check if the robot reached its goal
		  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		    	{
			ROS_INFO("Hooray, the turtlebot moved to drop off zone");
			//state_goal_reached = 1;	
			}
		  else
			{
		    	ROS_INFO("The turtlebot failed to move to drop off zone");
			//state_goal_reached = 0;	
			}

	}		

  return 0;
}
