#include <autoware_topic_name_changer.hpp>

TopicNameChanger::TopicNameChanger(const rclcpp::NodeOptions& node_options) : Node("autoware_topic_name_changer", node_options) {
  params_.lidar_topic_name = this->declare_parameter<std::string>("lidar_topic_name");
  params_.imu_topic_name = this->declare_parameter<std::string>("imu_topic_name");
  params_.gnss_topic_name = this->declare_parameter<std::string>("gnss_topic_name");

  params_.pub_lidar_topic_name = this->declare_parameter<std::string>("pub_lidar_topic_name");
  params_.pub_imu_topic_name = this->declare_parameter<std::string>("pub_imu_topic_name");
  params_.pub_gnss_topic_name = this->declare_parameter<std::string>("pub_gnss_topic_name");
  

  std::cout << "lidar_topic_name: " << params_.lidar_topic_name << std::endl;
  std::cout << "imu_topic_name: " << params_.imu_topic_name << std::endl;
  std::cout << "gnss_topic_name: " << params_.gnss_topic_name << std::endl;

  std::cout << "pub_lidar_topic_name: " << params_.pub_lidar_topic_name << std::endl;
  std::cout << "pub_imu_topic_name: " << params_.pub_imu_topic_name << std::endl;
  std::cout << "pub_gnss_topic_name: " << params_.pub_gnss_topic_name << std::endl;


  // sub
  auto qos = rclcpp::SensorDataQoS();
  qos.get_rmw_qos_profile().depth = 100;
  velodyne_points_sub_ = this->create_subscription<velodyne_msgs::msg::VelodynePacket>(
    params_.lidar_topic_name,
    qos,
    std::bind(&TopicNameChanger::velodyne_points_callback, this, std::placeholders::_1));
  imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(params_.imu_topic_name, qos, std::bind(&TopicNameChanger::imu_callback, this, std::placeholders::_1));
  gnss_sub_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(params_.gnss_topic_name, qos, std::bind(&TopicNameChanger::gnss_callback, this, std::placeholders::_1));

  velodyne_points_pub_ = this->create_publisher<velodyne_msgs::msg::VelodynePacket>(params_.pub_lidar_topic_name, 10);
  imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>(params_.pub_imu_topic_name, 10);
  gnss_pub_ = this->create_publisher<sensor_msgs::msg::NavSatFix>( params_.pub_gnss_topic_name, 10);
}

void TopicNameChanger::velodyne_points_callback(const velodyne_msgs::msg::VelodynePacket::SharedPtr msg) {
  velodyne_points_pub_->publish(*msg);
}
void TopicNameChanger::imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg) {
  imu_pub_->publish(*msg);
}
void TopicNameChanger::gnss_callback(const sensor_msgs::msg::NavSatFix::SharedPtr msg) {
  gnss_pub_->publish(*msg);
}