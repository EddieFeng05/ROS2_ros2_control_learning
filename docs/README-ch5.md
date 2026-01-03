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