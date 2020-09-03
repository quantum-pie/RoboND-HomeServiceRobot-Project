#!/bin/sh

SCRIPT=$(realpath $0)
BASEDIR=$(dirname $SCRIPT)

xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${BASEDIR}/../turtlebot_simulator/turtlebot_gazebo/worlds/apartment.world " &
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${BASEDIR}/../map/map.yaml" & 
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; rosrun pick_objects pick_objects use_markers:=off" &

