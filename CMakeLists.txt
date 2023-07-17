cmake_minimum_required(VERSION 3.5)
project(autoware_topic_name_changer)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(velodyne_msgs REQUIRED)

add_executable(autoware_topic_name_changer 
  src/autoware_topic_name_changer.cpp
  src/autoware_topic_name_changer_node.cpp
)

target_include_directories(autoware_topic_name_changer 
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

ament_target_dependencies(autoware_topic_name_changer
  rclcpp 
  velodyne_msgs
  sensor_msgs
)

# Install the points_processor executable to the lib/points_processor directory
install(TARGETS autoware_topic_name_changer DESTINATION lib/${PROJECT_NAME})


# Install the launch directory to the share/points_processor directory
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)

ament_package()