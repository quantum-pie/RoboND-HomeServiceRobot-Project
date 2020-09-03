#include <ros/ros.h>
#include "add_markers/PublishMarker.h"

int main( int argc, char** argv )
{
    // Initialize the pick_objects node
    ros::init(argc, argv, "test_markers");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<add_markers::PublishMarker>("/add_markers/publish_marker");

    while(!client.waitForExistence(ros::Duration(5.0))){
      ROS_INFO("Waiting for the add_markers server to come up");
    }

    geometry_msgs::Pose goal_pose;
    goal_pose.position.x = 4.0;
    goal_pose.position.y = -4.5;
    goal_pose.orientation.w = 1.0;

    add_markers::PublishMarker srv;
    srv.request.marker_pose = goal_pose;
    srv.request.marker_on = true;

    if (!client.call(srv)) {
      ROS_ERROR("Failed to call service publish_marker");
    }

    ros::Duration(5, 0).sleep();

    srv.request.marker_on = false;
    if (!client.call(srv)) {
      ROS_ERROR("Failed to call service publish_marker");
    }

    ros::Duration(5, 0).sleep();

    goal_pose.position.x = -1.0;
    goal_pose.position.y = -4.1;
    goal_pose.orientation.w = 1.0;

    srv.request.marker_pose = goal_pose;
    srv.request.marker_on = true;
    if (!client.call(srv)) {
      ROS_ERROR("Failed to call service publish_marker");
    }

    return 0;
}
