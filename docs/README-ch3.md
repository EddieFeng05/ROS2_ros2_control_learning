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
## CH3 Create an C++ Hardware Driver

### Ch3-3 Motor Driver

Write the Robotis XL330 motor library. We follow the information below the links:

[Robotis XL330 e-Manual](https://emanual.robotis.com/docs/en/dxl/x/xl330-m288/)

[DynamixelSDK github](https://github.com/ROBOTIS-GIT/DynamixelSDK)

[DynamixelSDK read_write.cpp github](https://github.com/ROBOTIS-GIT/DynamixelSDK/blob/main/c%2B%2B/example/protocol2.0/read_write/read_write.cpp)


### Ch3-4 Include the Driver in a ROS Node

Download dyanamixel sdk

```
sudo apt install ros-jazzy-dynamixel-sdk*
```

Create the new package about dxl

```
ros2 pkg create dxl_test --build-type ament_cmake --dependencies rclcpp dynamixel_sdk
```

Add the  dxl_test code and test it 

```
ros2 run dxl_test test_motors 

```