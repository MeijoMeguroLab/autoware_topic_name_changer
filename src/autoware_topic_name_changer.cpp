#include <type_changer.hpp>

TopicNameChanger::TopicNameChanger(const rclcpp::NodeOption& node_options):Node("autoware_topic_name_changer",node_options){
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
  qos.get_rmw_qos_profile().depteh = 100;
  velodyne_points_sub_ = this->create_subscription<>(params_.lidar_topic_name, qos, std::bind(&TopicNameChanger::velodyne_callback, this, std::placeholders::_1));
  imu_sub_ = this->create_subscription<>(params_.imu_topic_name, qos, std::bind(&TopicNameChanger::imu_callback, this, std::placeholders::_1));
  gnss_sub_ = this->create_subscription<>(params_.gnss_topic_name, qos, std::bind(&TopicNameChanger::gnss_callback, this, std::placeholders::_1));

  gnss_pub_ = this->create_publisher<sensor_msgs::msg::NavSatFix>( params_.pub_gnss_topic_name, 10);
}

  void gnss_callback(const sensor_msgs::msg::NavSatFix::SharedPtr msg)
  {
    gnss_sub_->publish(*msg);
  }