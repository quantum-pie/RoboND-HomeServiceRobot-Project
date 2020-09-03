#!/bin/sh

SCRIPT=$(realpath $0)
BASEDIR=$(dirname $SCRIPT)

xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${BASEDIR}/../turtlebot_simulator/turtlebot_gazebo/worlds/apartment.world " &
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch" & 
sleep 5
xterm -e " source ${BASEDIR}/../../devel/setup.bash; rosrun gmapping slam_gmapping" &
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
