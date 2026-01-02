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
## CH2

### Ch2-2 Starting Code + Robot Overview

* Using launch code to show urdf

```
ros2 launch my_robot_description display.launch.xml
```

* Show the URDF infomation


```
ros2 run tf2_tools view_frames 
```


* Show the topic infomation

```
rqt_graph
```

### Ch2-3 Add a ros2_control tag in the URDF

Just add the ros2_control.xacro file.

