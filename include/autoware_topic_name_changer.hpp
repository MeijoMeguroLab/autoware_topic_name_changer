#pragma once

#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <velodyne_msgs/msg/velodyne_packet.hpp>
#include <velodyne_msgs/msg/velodyne_scan.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>

class TopicNameChanger : public rclcpp::Node {
  struct Params {
    // rosbag information
    std::string lidar_topic_name, imu_topic_name, gnss_topic_name, pub_lidar_topic_name, pub_imu_topic_name, pub_gnss_topic_name;
  } params_;

public:
  TopicNameChanger(const rclcpp::NodeOptions& node_options = rclcpp::NodeOptions());
  ~TopicNameChanger();

private:
  // callback
  void velodyne_points_callback(velodyne_msgs::msg::VelodyneScan::SharedPtr msg);

  void imu_callback(sensor_msgs::msg::Imu::SharedPtr msg);

  void gnss_callback(sensor_msgs::msg::NavSatFix::SharedPtr msg);

  rclcpp::Subscription<velodyne_msgs::msg::VelodyneScan>::SharedPtr velodyne_points_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gnss_sub_;

  rclcpp::Publisher<velodyne_msgs::msg::VelodyneScan>::SharedPtr velodyne_points_pub_;
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr gnss_pub_;
};

