#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class RobotNewsStationNode : public rclcpp::Node
{
public:
  RobotNewsStationNode() : Node("cpp_test"), robot_name_("R2D2")
  {
    RCLCPP_INFO(this->get_logger(), "Hello ROS 2, I'm %s", robot_name_.c_str());

    publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
    
    timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&RobotNewsStationNode::publishNews, this));

    RCLCPP_INFO(this->get_logger(), "%s has been started", robot_name_.c_str());
  }
  
private:
  rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
  std::string robot_name_;
  rclcpp::TimerBase::SharedPtr timer_;

  void publishNews()
  {
    auto msg = example_interfaces::msg::String();
    msg.data = robot_name_ + " news here";
    publisher_->publish(msg);
  }

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RobotNewsStationNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}