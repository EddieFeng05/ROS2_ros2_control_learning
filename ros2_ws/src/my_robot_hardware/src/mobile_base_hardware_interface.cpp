#include "my_robot_hardware/mobile_base_hardware_interface.hpp"

namespace mobile_base_hardware{

hardware_interface::CallbackReturn MobileBaseHardwareInterface::on_init
    (const hardware_interface::HardwareComponentInterfaceParams & params)
{
    if(hardware_interface::SystemInterface::on_init(params) !=
        hardware_interface::CallbackReturn::SUCCESS)
    {
        return hardware_interface::CallbackReturn::ERROR;
    }

    info_ = params.hardware_info;

    // left_motor_id_ = 10;
    // right_motor_id_ = 20;
    // port_ = "/dev/ttyUSB0";

    // Use hardware parameters from ros2_control.xacro
    left_motor_id_ = std::stoi(info_.hardware_parameters["left_motor_id"]);
    right_motor_id_ = std::stoi(info_.hardware_parameters["right_motor_id"]);
    port_ = info_.hardware_parameters["dynamixel_port"];

    driver_ = std::make_shared<XL330Driver>(port_);
    
    return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn MobileBaseHardwareInterface::on_configure
    (const rclcpp_lifecycle::State & previous_state) 
{
    (void) previous_state; 
    if(!driver_ ->init() !=0){
        return hardware_interface::CallbackReturn::ERROR;
    }

    // For debugging Log the available interfaces
    // for (const auto & [name, descr] : joint_command_interfaces_)
    // {
    //     RCLCPP_INFO(get_logger(), "COMMAND INTERFACE NAME: ");
    //     RCLCPP_INFO(get_logger(), name.c_str());
    // }

    // for (const auto & [name, descr] : joint_state_interfaces_)
    // {
    //     RCLCPP_INFO(get_logger(), "STATE INTERFACE NAME: ");
    //     RCLCPP_INFO(get_logger(), name.c_str());
    // }

    return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn MobileBaseHardwareInterface::on_activate
    (const rclcpp_lifecycle::State & previous_state)
{
    (void) previous_state;

    set_state("base_left_wheel_joint/velocity", 0.0);
    set_state("base_right_wheel_joint/velocity", 0.0);
    set_state("base_left_wheel_joint/position", 0.0);
    set_state("base_right_wheel_joint/position", 0.0);

    driver_->activateWithVelocityMode(left_motor_id_);
    driver_->activateWithVelocityMode(right_motor_id_);
    return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn MobileBaseHardwareInterface::on_deactivate
    (const rclcpp_lifecycle::State & previous_state)
{
    (void) previous_state;
    driver_->deactivate(left_motor_id_);
    driver_->deactivate(right_motor_id_);
    return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type MobileBaseHardwareInterface::read
    (const rclcpp::Time & time, const rclcpp::Duration & period)
{
    (void) time;
    double left_vel = driver_->getVelocityRadianPerSec(left_motor_id_);
    double right_vel = -1.0 * driver_->getVelocityRadianPerSec(right_motor_id_);

    // Filter the velocities to reduce noise
    if (abs(left_vel) < 0.03) { left_vel = 0.0; }
    if (abs(right_vel) < 0.03) { right_vel = 0.0; }

    // URDF variable names match variable names in ros2_control
    set_state("base_left_wheel_joint/velocity", left_vel);
    set_state("base_right_wheel_joint/velocity", right_vel);
    set_state("base_left_wheel_joint/position",get_state("base_left_wheel_joint/position") + left_vel * period.seconds());
    set_state("base_right_wheel_joint/position",get_state("base_right_wheel_joint/position") + right_vel * period.seconds());
    
    //debugging info
    // RCLCPP_INFO(get_logger(), "left vel: %f, right vel: %f, left pos: %f, right pos: %f",
    //     left_vel, right_vel, get_state("base_left_wheel_joint/position"), get_state("base_right_wheel_joint/position"));

    return hardware_interface::return_type::OK;
}
hardware_interface::return_type MobileBaseHardwareInterface::write
    (const rclcpp::Time & time, const rclcpp::Duration & period)
{
    (void) time;
    (void) period;
    driver_->setTargetVelocityRadianPerSec(left_motor_id_, get_command("base_left_wheel_joint/velocity"));
    driver_->setTargetVelocityRadianPerSec(right_motor_id_, -1.0 *get_command("base_right_wheel_joint/velocity"));

    //debugging info
    // RCLCPP_INFO(get_logger(), "left vel: %f, right vel: %f",
    //     get_command("base_left_wheel_joint/velocity"), get_command("base_right_wheel_joint/velocity"));

    return hardware_interface::return_type::OK;
}
} // namespace mobile_base_hardware

#include "pluginlib/class_list_macros.hpp"

PLUGINLIB_EXPORT_CLASS(mobile_base_hardware::MobileBaseHardwareInterface, hardware_interface::SystemInterface)