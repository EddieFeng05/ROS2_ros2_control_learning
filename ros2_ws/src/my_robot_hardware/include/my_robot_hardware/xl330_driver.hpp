#ifndef XL330_DRIVER_HPP
#define XL330_DRIVER_HPP

#define PROTOCOL_VERSION 2.0
#define BAUDRATE 57600

#define ADDR_OPERATING_MODE 11
#define ADDR_TORQUE_ENABLE 64
#define ADDR_GOAL_VELOCITY 104
#define ADDR_GOAL_POSITION 116
#define ADDR_PRESENT_VELOCITY 128
#define ADDR_PRESENT_POSITION 132

#define RAD_TO_DXL_POSITION 651.088636364 // 1 / 0.0174533 / 0.088
#define RAD_S_TO_RPM 9.549                // 60 / (2*PI)
#define RPM_TO_DXL_VELOCITY 4.366812227   // 1 / 0.229

#define OPERATING_MODE_VELOCITY 1
#define OPERATING_MODE_POSITION 3

#include <dynamixel_sdk/dynamixel_sdk.h>
#include <iostream>

class XL330Driver
{
public:
    XL330Driver(const std::string &device_name)
    {
        this->device_name = device_name;
        port_handler_ = dynamixel::PortHandler::getPortHandler(device_name.c_str());
        packet_handler_ = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    }

    int init()
    {
        std::cout << "Initializing connection with robot " << std::endl;

        if (port_handler_->openPort())
        {
            std::cout << "Successfully opened port: " << device_name << std::endl;
        }
        else
        {
            std::cerr << "Failed to open port: " << device_name << std::endl;
            return -1;
        }

        if (port_handler_->setBaudRate(BAUDRATE))
        {
            std::cout << "Successfully set baudrate: " << device_name << std::endl;
        }
        else
        {
            std::cerr << "Failed to set baudrate: " << device_name << std::endl;
            return -1;
        }
        return 0;
    }

    void activateWithPositionMode(int dxl_id)
    {

        std::cout << "Activate motor" << std::endl;

        // Set Position Control Mode
        packet_handler_->write1ByteTxRx(port_handler_, dxl_id, ADDR_OPERATING_MODE, OPERATING_MODE_POSITION);
        // Enable Torque
        packet_handler_->write1ByteTxRx(port_handler_, dxl_id, ADDR_TORQUE_ENABLE, 1);
    }

    void activateWithVelocityMode(int dxl_id)
    {

        std::cout << "Activate motor" << std::endl;

        // Set Velocity Control Mode
        packet_handler_->write1ByteTxRx(port_handler_, dxl_id, ADDR_OPERATING_MODE, OPERATING_MODE_VELOCITY);
        // Enable Torque
        packet_handler_->write1ByteTxRx(port_handler_, dxl_id, ADDR_TORQUE_ENABLE, 1);
    }

    void deactivate(int dxl_id)
    {
        std::cout << "Deactivate motor" << std::endl;
        // Disable Torque
        packet_handler_->write1ByteTxRx(port_handler_, dxl_id, ADDR_TORQUE_ENABLE, 0);
    }

    void setTargetPositionRadian(int dxl_id, double position_rad)
    {
        int position = position_rad * RAD_TO_DXL_POSITION + 2048;
        packet_handler_->write4ByteTxRx(port_handler_, dxl_id, ADDR_GOAL_POSITION, position);
    }

    void setTargetVelocityRadianPerSec(int dxl_id, double command)
    {
        int velocity = command * RAD_S_TO_RPM * RPM_TO_DXL_VELOCITY;
        packet_handler_->write4ByteTxRx(port_handler_, dxl_id, ADDR_GOAL_VELOCITY, velocity);
    }

    double getPositionRadian(int dxl_id)
    {

        int32_t dxl_present_position = 0;
        packet_handler_->read4ByteTxRx(port_handler_, dxl_id, ADDR_PRESENT_POSITION, (uint32_t *)&dxl_present_position);
        return (double)(dxl_present_position - 2048) / RAD_TO_DXL_POSITION;
    }

    double getVelocityRadianPerSec(int dxl_id)
    {
        int32_t dxl_present_velocity = 0;
        packet_handler_->read4ByteTxRx(port_handler_, dxl_id, ADDR_PRESENT_VELOCITY, (uint32_t *)&dxl_present_velocity);
        return (double)dxl_present_velocity / RPM_TO_DXL_VELOCITY / RAD_S_TO_RPM;
    }

private:
    dynamixel::PortHandler *port_handler_;
    dynamixel::PacketHandler *packet_handler_;
    std::string device_name;
};

#endif // XL330_DRIVER_HPP