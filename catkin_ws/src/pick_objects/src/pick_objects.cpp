#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <ros/time.h>
#include <add_markers/PublishMarker.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

bool moveTo(MoveBaseClient& ac, const geometry_msgs::Pose& pose) {
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose = pose;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  return ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED;
}

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  ros::NodeHandle n;

  std::string use_markers_arg;
  n.getParam("use_markers", use_markers_arg);

  bool use_markers = use_markers_arg == "on";
  ros::ServiceClient client = n.serviceClient<add_markers::PublishMarker>("/add_markers/publish_marker");

  if (use_markers) {
    while(!client.waitForExistence(ros::Duration(5.0))){
      ROS_INFO("Waiting for the add_markers server to come up");
    }
  }

  geometry_msgs::Pose goal_pose;
  goal_pose.position.x = 4.0;
  goal_pose.position.y = -4.5;
  goal_pose.orientation.w = 1.0;

  add_markers::PublishMarker srv;
  srv.request.marker_pose = goal_pose;
  srv.request.marker_on = true;
  client.call(srv);

  bool goal_reached = moveTo(ac, goal_pose);

  // Check if the robot reached its goal
  if(goal_reached) {
    ROS_INFO("Pickup location reached");
  } else {
    ROS_INFO("The base failed to reach pickup location");
    return 0;
  }

  srv.request.marker_on = false;
  client.call(srv);

  ROS_INFO("Picking up...");
  ros::Duration(5, 0).sleep();

  goal_pose.position.x = -1.0;
  goal_pose.position.y = -4.0;
  goal_pose.orientation.w = 1.0;

  goal_reached = moveTo(ac, goal_pose);

  // Check if the robot reached its goal
  if(goal_reached) {
    ROS_INFO("Drop-off location reached");
  } else {
    ROS_INFO("The base failed to reach drop-off location");
    return 0;
  }

  goal_pose.position.y -= 0.1;
  srv.request.marker_pose = goal_pose;
  srv.request.marker_on = true;
  client.call(srv);

  return 0;
}
