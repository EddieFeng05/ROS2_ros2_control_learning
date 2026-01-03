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
## CH2 Adapt a Robot to ros2_control(with Mock Hardware)

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

### Ch2-4 Add a Controller Config(Part 1 Joint State Broadcaster)
ros2_controller link

https://github.com/ros-controls/ros2_controllers

joint state broadcaster

https://github.com/ros-controls/ros2_controllers/tree/master/joint_state_broadcaster


### Ch2-5 Add a Controller Config(Part 2 Diff Drive Controller)

Add a Controller Config Part 2 Diff Drive Controller

diff_drive_controller

https://github.com/ros-controls/ros2_controllers/blob/master/diff_drive_controller/diff_drive_plugin.xml

### Ch2-6 Start Everything from the Terminal

Use every function by terminal


* Termina 1: Run your robot_state_publisher

```
# Use your my_robot.urdf.xacro path

ros2 run robot_state_publisher robot_state_publisher --ros-args -p robot_description:="$(xacro my_robot.urdf.xacro_path)"

# sample path

ros2 run robot_state_publisher robot_state_publisher --ros-args -p robot_description:="$(xacro /home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/my_robot_description/urdf/my_robot.urdf.xacro)"
```

* The result
```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 run robot_state_publisher robot_state_publisher --ros-args -p robot_description:="$(xacro /home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/my_robot_description/urdf/my_robot.urdf.xacro)"
[INFO] [1767356999.658729028] [robot_state_publisher]: Robot initialized


```

* Termina 2: Run controller_manager


```
# Use your my_robot_controllers.yaml path

ros2 run controller_manager ros2_control_node --ros-args --params-file my_robot_controllers.yaml_path

# sample path

ros2 run controller_manager ros2_control_node --ros-args --params-file /home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/my_robot_bringup/config/my_robot_controllers.yaml

```

* the result

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 run controller_manager ros2_control_node --ros-args --params-file /home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/my_robot_bringup/config/my_robot_controllers.yaml
[INFO] [1767357084.071665882] [controller_manager]: Using Steady (Monotonic) clock for triggering controller manager cycles.
[INFO] [1767357084.083316251] [controller_manager]: Subscribing to '/robot_description' topic for robot description.
[INFO] [1767357084.106002565] [controller_manager]: update rate is 50 Hz
[INFO] [1767357084.106180807] [controller_manager]: Overruns handling is : enabled
[INFO] [1767357084.106198887] [controller_manager]: Spawning controller_manager RT thread with scheduler priority: 50
[WARN] [1767357084.106371058] [controller_manager]: Could not enable FIFO RT scheduling policy: with error number <1>(Operation not permitted). See [https://control.ros.org/master/doc/ros2_control/controller_manager/doc/userdoc.html] for details on how to enable realtime scheduling.
[INFO] [1767357084.106816328] [controller_manager]: Received robot description from topic.
[INFO] [1767357084.109129184] [controller_manager]: Loading hardware 'MobileBaseHardwareInterface' 
[INFO] [1767357084.111735796] [controller_manager]: Loaded hardware 'MobileBaseHardwareInterface' from plugin 'mock_components/GenericSystem'
[INFO] [1767357084.112609648] [controller_manager]: Initialize hardware 'MobileBaseHardwareInterface' 
[INFO] [1767357084.114163344] [controller_manager]: Successful initialization of hardware 'MobileBaseHardwareInterface'
[INFO] [1767357084.114361385] [resource_manager]: 'configure' hardware 'MobileBaseHardwareInterface' 
[INFO] [1767357084.114444955] [resource_manager]: Successful 'configure' of hardware 'MobileBaseHardwareInterface'
[INFO] [1767357084.114455272] [resource_manager]: 'activate' hardware 'MobileBaseHardwareInterface' 
[INFO] [1767357084.114465617] [resource_manager]: Successful 'activate' of hardware 'MobileBaseHardwareInterface'
[INFO] [1767357084.114509905] [controller_manager]: Registering statistics for : MobileBaseHardwareInterface
[INFO] [1767357084.114581409] [controller_manager]: Resource Manager has been successfully initialized. Starting Controller Manager services...


```
* Check by ros2 node list

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 node list
/controller_manager
/mobilebasehardwareinterface
/robot_state_publisher
```


* Termina 3: controller_manager spawner two controller 


```
ros2 run controller_manager spawner joint_state_broadcaster

ros2 run controller_manager spawner diff_drive_controller

```

* the result

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 run controller_manager spawner joint_state_broadcaster
[INFO] [1767357348.067814940] [spawner_joint_state_broadcaster]: Loaded joint_state_broadcaster
[INFO] [1767357348.128480489] [spawner_joint_state_broadcaster]: Configured and activated joint_state_broadcaster
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 run controller_manager spawner diff_drive_controller
[INFO] [1767357355.986652759] [spawner_diff_drive_controller]: Loaded diff_drive_controller
[INFO] [1767357356.048393840] [spawner_diff_drive_controller]: Configured and activated diff_drive_controller
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ 
```

* Check by rviz

```
# rviz config path
ros2 run rviz2 rviz2 -d rviz_config_path

#smaple
ros2 run rviz2 rviz2 -d /home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/src/my_robot_description/rviz/urdf_config.rviz

```

* Check by ros2 node list

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 node list
/controller_manager
/diff_drive_controller
/joint_state_broadcaster
/mobilebasehardwareinterface
/robot_state_publisher
/rviz
/transform_listener_impl_555941aaf590
```

* Termina 4: Command by topic info by keyboard


```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 topic list
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
/parameter_events
/robot_description
/rosout
/tf
/tf_static

```

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 topic info /diff_drive_controller/cmd_vel 
Type: geometry_msgs/msg/TwistStamped
Publisher count: 0
Subscription count: 1
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ 

```

```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 interface show geometry_msgs/msg/TwistStamped
# A twist with reference coordinate frame and timestamp

std_msgs/Header header
	builtin_interfaces/Time stamp
		int32 sec
		uint32 nanosec
	string frame_id
Twist twist
	Vector3  linear
		float64 x
		float64 y
		float64 z
	Vector3  angular
		float64 x
		float64 y
		float64 z
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$
```


* Use keyboarda control robot

```
ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r /cmd_vel:=/diff_drive_controller/cmd_vel -p stamped:=true

```



### Ch2-7 Launch File for ros2_control

Do the same thing like ch2-6, but now run by one launch file. 

* Terminal 1: Launch file 

```
ros2 launch my_robot_bringup my_robot.launch.xml 

```

* You will see successfully activated controller
```
eddie@eddie-VM:~/Documents/ROS2_ros2_control_learning/ros2_ws$ ros2 launch my_robot_bringup my_robot.launch.xml 
[INFO] [launch]: All log files can be found below /home/eddie/.ros/log/2026-01-02-20-52-42-011311-eddie-VM-18728
[INFO] [launch]: Default logging verbosity is set to INFO
[INFO] [robot_state_publisher-1]: process started with pid [18732]
[INFO] [ros2_control_node-2]: process started with pid [18733]
[INFO] [spawner-3]: process started with pid [18734]
[INFO] [spawner-4]: process started with pid [18735]
[INFO] [rviz2-5]: process started with pid [18736]
[robot_state_publisher-1] [INFO] [1767358362.225018963] [robot_state_publisher]: Robot initialized
[ros2_control_node-2] [INFO] [1767358362.277936103] [controller_manager]: Using Steady (Monotonic) clock for triggering controller manager cycles.
[ros2_control_node-2] [INFO] [1767358362.282126649] [controller_manager]: Subscribing to '/robot_description' topic for robot description.
[ros2_control_node-2] [INFO] [1767358362.308611896] [controller_manager]: update rate is 50 Hz
[ros2_control_node-2] [INFO] [1767358362.309335754] [controller_manager]: Overruns handling is : enabled
[ros2_control_node-2] [INFO] [1767358362.309345152] [controller_manager]: Spawning controller_manager RT thread with scheduler priority: 50
[ros2_control_node-2] [WARN] [1767358362.309434825] [controller_manager]: Could not enable FIFO RT scheduling policy: with error number <1>(Operation not permitted). See [https://control.ros.org/master/doc/ros2_control/controller_manager/doc/userdoc.html] for details on how to enable realtime scheduling.
[ros2_control_node-2] [INFO] [1767358362.309604056] [controller_manager]: Received robot description from topic.
[ros2_control_node-2] [INFO] [1767358362.320398610] [controller_manager]: Loading hardware 'MobileBaseHardwareInterface' 
[ros2_control_node-2] [INFO] [1767358362.321463498] [controller_manager]: Loaded hardware 'MobileBaseHardwareInterface' from plugin 'mock_components/GenericSystem'
[ros2_control_node-2] [INFO] [1767358362.321835359] [controller_manager]: Initialize hardware 'MobileBaseHardwareInterface' 
[ros2_control_node-2] [INFO] [1767358362.339548521] [controller_manager]: Successful initialization of hardware 'MobileBaseHardwareInterface'
[ros2_control_node-2] [INFO] [1767358362.339667224] [resource_manager]: 'configure' hardware 'MobileBaseHardwareInterface' 
[ros2_control_node-2] [INFO] [1767358362.339674767] [resource_manager]: Successful 'configure' of hardware 'MobileBaseHardwareInterface'
[ros2_control_node-2] [INFO] [1767358362.339679960] [resource_manager]: 'activate' hardware 'MobileBaseHardwareInterface' 
[ros2_control_node-2] [INFO] [1767358362.339685861] [resource_manager]: Successful 'activate' of hardware 'MobileBaseHardwareInterface'
[ros2_control_node-2] [INFO] [1767358362.340108530] [controller_manager]: Registering statistics for : MobileBaseHardwareInterface
[ros2_control_node-2] [INFO] [1767358362.340184628] [controller_manager]: Resource Manager has been successfully initialized. Starting Controller Manager services...
[ros2_control_node-2] [INFO] [1767358362.714083720] [controller_manager]: Loading controller : 'joint_state_broadcaster' of type 'joint_state_broadcaster/JointStateBroadcaster'
[ros2_control_node-2] [INFO] [1767358362.714118640] [controller_manager]: Loading controller 'joint_state_broadcaster'
[ros2_control_node-2] [INFO] [1767358362.720337028] [controller_manager]: Controller 'joint_state_broadcaster' node arguments: --ros-args --params-file /home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/install/my_robot_bringup/share/my_robot_bringup/config/my_robot_controllers.yaml 
[spawner-3] [INFO] [1767358362.746376874] [spawner_joint_state_broadcaster]: Loaded joint_state_broadcaster
[ros2_control_node-2] [INFO] [1767358362.748480721] [controller_manager]: Configuring controller: 'joint_state_broadcaster'
[ros2_control_node-2] [INFO] [1767358362.748743799] [joint_state_broadcaster]: 'joints' or 'interfaces' parameter is empty. All available state interfaces will be published
[ros2_control_node-2] [INFO] [1767358362.785375788] [controller_manager]: Activating controllers: [ joint_state_broadcaster ]
[ros2_control_node-2] [INFO] [1767358362.792175496] [controller_manager]: Successfully switched controllers!
[spawner-3] [INFO] [1767358362.813103471] [spawner_joint_state_broadcaster]: Configured and activated joint_state_broadcaster
[INFO] [spawner-3]: process has finished cleanly [pid 18734]
[ros2_control_node-2] [INFO] [1767358363.190581730] [controller_manager]: Loading controller : 'diff_drive_controller' of type 'diff_drive_controller/DiffDriveController'
[ros2_control_node-2] [INFO] [1767358363.190611949] [controller_manager]: Loading controller 'diff_drive_controller'
[ros2_control_node-2] [INFO] [1767358363.193739090] [controller_manager]: Controller 'diff_drive_controller' node arguments: --ros-args --params-file /home/eddie/Documents/ROS2_ros2_control_learning/ros2_ws/install/my_robot_bringup/share/my_robot_bringup/config/my_robot_controllers.yaml 
[spawner-4] [INFO] [1767358363.226657038] [spawner_diff_drive_controller]: Loaded diff_drive_controller
[ros2_control_node-2] [INFO] [1767358363.228464064] [controller_manager]: Configuring controller: 'diff_drive_controller'
[ros2_control_node-2] [INFO] [1767358363.334050592] [controller_manager]: Activating controllers: [ diff_drive_controller ]
[ros2_control_node-2] [INFO] [1767358363.351987268] [controller_manager]: Successfully switched controllers!
[spawner-4] [INFO] [1767358363.373506364] [spawner_diff_drive_controller]: Configured and activated diff_drive_controller
[rviz2-5] [INFO] [1767358363.516727878] [rviz2]: Stereo is NOT SUPPORTED
[rviz2-5] [INFO] [1767358363.516810971] [rviz2]: OpenGl version: 4.3 (GLSL 4.3)
[rviz2-5] [INFO] [1767358363.552588167] [rviz2]: Stereo is NOT SUPPORTED
[INFO] [spawner-4]: process has finished cleanly [pid 18735]

```

* Terminal 2: Use keyboarda control robot

```
ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r /cmd_vel:=/diff_drive_controller/cmd_vel -p stamped:=true

```

* Rviz: Fixed frame set to odom
