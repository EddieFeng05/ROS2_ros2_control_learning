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

### Ch4-5 Make the Hardware Interface a Plugin

Add the plugin code in cpp file end. And new the plugin xml file in my_robot_hardware folder.


ros2_ws/src/my_robot_hardware/src/mobile_base_hardware_interface.cpp

ros2_ws/src/my_robot_hardware/my_robot_hardware_interface.xml

### Ch4-6 Build the Hardware Interface

Add new code in package.xml and CMakeLists.txt.

* Notice: We need to change the on_init function. 

### Ch4-7 Start the ros2_control Stack with your new Hardware Interface

Change plugin (mock to mobile_base_hardware/MobileBaseHardwareInterface) in ros2_control.xacro.

* Notice: ros2_control name="MobileBase cannot the same as <plugin>mobile_base_hardware/MobileBaseHardwareInterface</plugin> name

## Ch4-8 Debugging Steps

Add debuggin code in hardware_interface.cpp.

ros2_ws/src/my_robot_hardware/src/mobile_base_hardware_interface.cpp


## Ch4-9 Add Parameters to the Hardware Interface

Change to parameters to setup hardware interface by ros2_controller.xacro
