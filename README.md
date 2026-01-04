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

* In .vscode you need to add

```
      "includePath": [
        "/opt/ros/jazzy/include/**",
        "/usr/include/**",
        "/home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/dxl_test/include/**",
        "/home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/my_robot_hardware/include/**"
      ],
      "name": "ro
```
## CH2 Adapt a Robot to ros2_control(with Mock Hardware)

[CH2 REAMDME](./docs/README-ch2.md)


## CH3 Create an C++ Hardware Driver

[CH3 REAMDME](./docs/README-ch3.md)


## CH4 Write a Hardware Interface for ros2_control

[CH4 REAMDME](./docs/README-ch4.md)


## CH5 Project: Set up ros2_control for a Robotic Arm

[CH5 REAMDME](./docs/README-ch5.md)