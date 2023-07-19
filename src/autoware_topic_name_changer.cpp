#include <autoware_topic_name_changer.hpp>

TopicNameChanger::TopicNameChanger(const rclcpp::NodeOptions& node_options) : Node("autoware_topic_name_changer", node_options) {
  params_.lidar_topic_name = this->declare_parameter<std::string>("lidar_topic_name");
  params_.twist_topic_name = this->declare_parameter<std::string>("twist_topic_name");
  params_.imu_topic_name = this->declare_parameter<std::string>("imu_topic_name");
  params_.gnss_topic_name = this->declare_parameter<std::string>("gnss_topic_name");

  params_.pub_lidar_topic_name = this->declare_parameter<std::string>("pub_lidar_topic_name");
  params_.pub_twist_topic_name = this->declare_parameter<std::string>("pub_twist_topic_name");
  params_.pub_imu_topic_name = this->declare_parameter<std::string>("pub_imu_topic_name");
  params_.pub_gnss_topic_name = this->declare_parameter<std::string>("pub_gnss_topic_name");
  

  std::cout << "lidar_topic_name: " << params_.lidar_topic_name << std::endl;
  std::cout << "twist_topic_name: " << params_.twist_topic_name << std::endl;
  std::cout << "imu_topic_name: " << params_.imu_topic_name << std::endl;
  std::cout << "gnss_topic_name: " << params_.gnss_topic_name << std::endl;

  std::cout << "pub_lidar_topic_name: " << params_.pub_lidar_topic_name << std::endl;
  std::cout << "pub_twist_topic_name: " << params_.pub_twist_topic_name << std::endl;
  std::cout << "pub_imu_topic_name: " << params_.pub_imu_topic_name << std::endl;
  std::cout << "pub_gnss_topic_name: " << params_.pub_gnss_topic_name << std::endl;


  // sub
  auto qos = rclcpp::SensorDataQoS();
  qos.get_rmw_qos_profile().depth = 100;
  velodyne_points_sub_ = this->create_subscription<velodyne_msgs::msg::VelodyneScan>(
    params_.lidar_topic_name,
    rclcpp::SensorDataQoS(),
    std::bind(&TopicNameChanger::velodyne_points_callback, this, std::placeholders::_1));
  twist_sub_ = this->create_subscription<geometry_msgs::msg::TwistStamped>(
    params_.twist_topic_name,
    rclcpp::SensorDataQoS(),
    std::bind(&TopicNameChanger::twist_callback, this, std::placeholders::_1));
  imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(params_.imu_topic_name, qos, std::bind(&TopicNameChanger::imu_callback, this, std::placeholders::_1));
  gnss_sub_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(params_.gnss_topic_name, qos, std::bind(&TopicNameChanger::gnss_callback, this, std::placeholders::_1));

  velodyne_points_pub_ = this->create_publisher<velodyne_msgs::msg::VelodyneScan>(params_.pub_lidar_topic_name, 10);
  twist_pub_ = this->create_publisher<geometry_msgs::msg::TwistWithCovarianceStamped>(params_.pub_twist_topic_name, 10);
  imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>(params_.pub_imu_topic_name, 10);
  gnss_pub_ = this->create_publisher<sensor_msgs::msg::NavSatFix>( params_.pub_gnss_topic_name, 10);
}

TopicNameChanger::~TopicNameChanger() {}

void TopicNameChanger::velodyne_points_callback(velodyne_msgs::msg::VelodyneScan::SharedPtr msg) {
  msg->header.frame_id = "velodyne_top";
  velodyne_points_pub_->publish(*msg);
}
void TopicNameChanger::twist_callback(geometry_msgs::msg::TwistStamped::SharedPtr msg) {
  geometry_msgs::msg::TwistWithCovarianceStamped pub_msg;
  pub_msg.header = msg->header;
  pub_msg.twist.twist = msg->twist;

  pub_msg.header.frame_id = "gnss_link";
  twist_pub_->publish(pub_msg);
}
void TopicNameChanger::imu_callback(sensor_msgs::msg::Imu::SharedPtr msg) {
  msg->header.frame_id = "tamagawa/imu_link";
  imu_pub_->publish(*msg);
}
void TopicNameChanger::gnss_callback(sensor_msgs::msg::NavSatFix::SharedPtr msg) {
  msg->header.frame_id = "gnss_link";
  gnss_pub_->publish(*msg);
}