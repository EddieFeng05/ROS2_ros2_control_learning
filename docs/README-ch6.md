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

### 6-3 Write the controller cpp file

1. New file my_controller.cpp

ros2_ws/src/my_robot_controllers/src/my_controller.cpp

2. Setting .vscode

```
      "includePath": [
        "/opt/ros/jazzy/include/**",
        "/usr/include/**",
        "/home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/dxl_test/include/**",
        "/home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/my_robot_hardware/include/**",
        "/home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/my_robot_controllers/include/**"
      ],
```

### 6-4 Build as a Plugin

1. Add plugin code in my_controller.cpp

ros2_ws/src/my_robot_controllers/src/my_controller.cpp

2. New file my_controller_plugin.xml

ros2_ws/src/my_robot_controllers/my_controller_plugin.xml

3. Add new depend in packages 

4. Add new depend and includes in CMakeList.txt


### 6-5 Use the Controller with our Robot

1. Add new code in my_robot_controllers.yaml

ros2_ws/src/my_robot_bringup/config/my_robot_controllers.yaml

2. Add new code in my_robot.launch.xml

ros2_ws/src/my_robot_bringup/launch/my_robot.launch.xml

3. Launch file

```
ros2 launch my_robot_bringup my_robot.launch.xml
```

4. Check and debugging

```
rqt_graph

ros2 topic list
```

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws/src$ ros2 topic list
/clicked_point
/controller_manager/activity
/controller_manager/introspection_data/full
/controller_manager/introspection_data/names
/controller_manager/introspection_data/values
/controller_manager/statistics/full
/controller_manager/statistics/names
/controller_manager/statistics/values
/diagnostics
/diff_drive_controller/cmd_vel
/diff_drive_controller/odom
/diff_drive_controller/transition_event
/dynamic_joint_states
/goal_pose
/initialpose
/joint_state_broadcaster/transition_event
/joint_states
/joints_command
/my_arm_controller/transition_event
/parameter_events
/robot_description
/rosout
/tf
/tf_static

```

```
ros2 topic info /joints_command 
```

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws/src$ ros2 topic info /joints_command 
Type: example_interfaces/msg/Float64MultiArray
Publisher count: 0
Subscription count: 1


```

```
ros2 interface show example_interfaces/msg/Float64MultiArray 

```

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws/src$ ros2 interface show example_interfaces/msg/Float64MultiArray 
# This is an example of using complex datatypes.
# It is not recommended to use directly.
# To use a similar datastruct please define a custom message with appropriate semantic meaning.

# Please look at the MultiArrayLayout message definition for
# documentation on all multiarrays.

MultiArrayLayout  layout        # specification of data layout
	#
	#
	#
	#
	#
	MultiArrayDimension[] dim #
		string label   #
		uint32 size    #
		uint32 stride  #
	uint32 data_offset        #
float64[]         data          # array of data
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws/src$ 

```

* Send command

```
ros2 topic pub -1 /joints_command example_interfaces/msg/Float64MultiArray "{data: [0.5, 0.5]}"

```