# ROS 2 - Hardware and ros2_control, Step by Step

This is follow course about "ROS 2 - Hardware and ros2_control, Step by Step".

https://www.udemy.com/course/ros2_control/?couponCode=KEEPLEARNING

## The environment setup

* Ubuntu 24.04
* Ros2 Jazzy
* Updat your environment

```
sudo apt update
sudo apt upgrade
```

* Install ros2-control and ros2-controllers(In this case is Jazzy)

```
sudo apt install ros-jazzy-ros2-control ros-jazzy-ros2-controllers
```

----
## CH5 Project: Set up ros2_control for a Robotic Arm

### Ch5-1 Intro - Project Overview

### 5-2 Step 0: Code Setup

New file arm.xacro and add new code in common_properities.xacro and my_robot.urdf.xacro.

```
ros2 launch my_robot_description display.launch.xml 
```

### 5-3 Step 1: ros2_control tag in URDF

1. Change into mock in mobile_base.ros2_control.xacro

2. New file arm.ros2_control.xacro

3. Include arm.ros2_control.xacro in my_robot.urdf.xacro.


### 5-4 Step 2: Configure a Controller

[ros2_controllers github link](https://github.com/ros-controls/ros2_controllers)

[forward_command_controller github link](https://github.com/ros-controls/ros2_controllers/tree/master/forward_command_controller)

1. Add new code in my_robot_controllers.yaml

ros2_ws/src/my_robot_bringup/config/my_robot_controllers.yaml


### 5-5 Step 3: Test the Controller with the Mock Component

1. Add new code in my_robot.launch.xml

ros2_ws/src/my_robot_bringup/launch/my_robot.launch.xml

```
ros2 launch my_robot_bringup my_robot.launch.xml 
```

To understand the node list

```
rqt_graph
```
To understand info 
```
ros2 topic info /arm_joints_controller/commands 
```

Send command to control arm

```
ros2 topic pub -1 /arm_joints_controller/commands std_msgs/msg/Float64MultiArray "{data: [0.0, 0.0]}"

ros2 topic pub -1 /arm_joints_controller/commands std_msgs/msg/Float64MultiArray "{data: [0.4, 0.3]}"

```