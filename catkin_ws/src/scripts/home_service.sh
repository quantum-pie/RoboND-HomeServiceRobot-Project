#!/bin/sh

SCRIPT=$(realpath $0)
BASEDIR=$(dirname $SCRIPT)

xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${BASEDIR}/../turtlebot_simulator/turtlebot_gazebo/worlds/apartment.world " &
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${BASEDIR}/../map/map.yaml" & 
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; rosrun rviz rviz -d ${BASEDIR}/../rvizConfig/navigation_with_markers.rviz" &
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; rosrun add_markers add_markers" &
sleep 5
xterm  -e  " source ${BASEDIR}/../../devel/setup.bash; rosrun pick_objects pick_objects use_markers:=on" &

