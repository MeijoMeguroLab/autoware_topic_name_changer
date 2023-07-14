#include "type_changer.hpp"

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicNameChanger>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}