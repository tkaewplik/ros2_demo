#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class SmartphoneNode : public rclcpp::Node
{
public:
  SmartphoneNode() : Node("cpp_test"), phone_name_("R2D2")
  {
    RCLCPP_INFO(this->get_logger(), "Hello ROS 2, I'm %s", phone_name_.c_str());

    subscription_ = this->create_subscription<example_interfaces::msg::String>(
      "robot_news", 10, 
      std::bind(&SmartphoneNode::callbackRobotNews, this, std::placeholders::_1));


    RCLCPP_INFO(this->get_logger(), "%s has been started", phone_name_.c_str());
  }
  
private:
  std::string phone_name_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscription_;
  

  void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "%s received: %s", phone_name_.c_str(), msg->data.c_str());
  }

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<SmartphoneNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}