#pragma once

#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

class TopicNameChanger : public rclcpp::Node {
  struct Params {
    // rosbag information
    std::string lidar_topic_name, imu_topic_name, pub_lidar_topic_name, pub_imu_topic_name;
  } params_;

public:
  Online(const rclcpp::NodeOptions& node_options = rclcpp::NodeOptions());
  ~Online();

private:
  // callback
  void velodyne_callback(const  msg);

  void imu_callback(const  msg);

  void gnss_callback(const  msg);

  rclcpp::Subscription<>::SharedPtr velodyne_points_sub_;
  rclcpp::Subscription<>::SharedPtr imu_sub_;
  rclcpp::Subscription<>::SharedPtr gnss_sub_;

};
