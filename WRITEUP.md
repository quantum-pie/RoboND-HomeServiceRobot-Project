# Home Service Robot Project

## Turtlebot Gazebo

This package loads Turtlebot model into Gazebo world. This robot will be used
in the project to provide home service.

## Turtlebot Teleop

This package is used to teleoperate Turtlebot from keyboard. In this project
it is used to control robot during environment mapping.

## Turtlebot RVIZ Launchers

This package provides a convinent way to visualize Turtlebot in RViz, including
map visualization, path visualization, sensor readings tracking, etc.

## GMAPPING

`slam_gmapping` is a ROS package that implements laser-based SLAM 
(simultaneous localization and mapping). The implementation is based on
Rao-Blackwellized particle filter for localization combined with occupancy grid 
mapping algorithm.

In this project `slam_gmapping` is used to map the environment for a home 
service robot where it will operate. It is assummed that environment is static
and thus map can be prebuilt and then reused by a localization-only algorithm 
(like AMCL, for instance).

## AMCL

This package implements Adaptime Monte-Carlo Localization algorithm, based on particle filter. 
It is assumed that the map of the environment is known in
advance (for instance, built using `slam_gmapping` package).

In this project `amcl` is ised to localize robot during its home service
operation.

## Move Base

This package solves a problem of global navigation linking together local and
global path planners. In this project it is used to plan a path given goal pose
of the Turtlebot.

## Add Markers

This package provides a service `add_markers` that will add or delete markers
in RViz at requested location.

I decided to implement this package using services because I think that it is
a good case for this kind of communcation: markers are shown and hidden only as
a response to certain events (robot reached some location). Moreover, this
approach allows to fully decouple `add_markers` package from robot target locations:
those are communicated through service requests by other packages. 

## Pick Objects

This package is a core of robot home service schedule. It defines pick and place
locations, activates moving action using `move_base` package and controls
markers visualization using `add_markers` service.
