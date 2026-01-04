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
## CH6 Create a Custom Controller

### 6-1 Intro

### 6-2 Write the Controller Header File

1. New pkg my_robot_controllers

```
ros2 pkg create my_robot_controllers --build-type ament_cmake --dependencies rclcpp

```

2. New file my_controller.hpp

ros2_ws/src/my_robot_controllers/include/my_robot_controllers/my_controller.hpp