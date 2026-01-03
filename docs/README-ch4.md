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
## CH4 Write a Hardware Interface for ros2_control

### Ch4-2 Create a Hardware Package and Set Up Your Driver

Create new package 

```
ros2 pkg create my_robot_hardware --build-type ament_cmake --dependencies rclcpp
```

Add CMakeLists.txt and package.xml


### Ch4-3 Write the Hardware Interface (header file)

Write header file for Hardware Interface. It's about Node lifecycles, you can copy it to if you create the new hardware interface. 

ros2_ws/src/my_robot_hardware/include/my_robot_hardware/mobile_base_hardware_interface.hpp



### Ch4-4 Write the Hardware Interface (cpp file)

Write cpp file for Hardware Interface. It's about Node lifecycles, you can copy it to if you create the new hardware interface. 

ros2_ws/src/my_robot_hardware/src/mobile_base_hardware_interface.cpp