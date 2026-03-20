#include <rclcpp/rclcpp.hpp>
#include "tutorial_interfaces/srv/add_three_ints.hpp"


class AddTwoIntsServerNode : public rclcpp::Node
{
public:
  AddTwoIntsServerNode() : Node("add_two_ints_server"), counter_(0)
  {
    // create a service which bind with "add_two_ints" service!
    service_ = this->create_service<tutorial_interfaces::srv::AddThreeInts>(
      "add_two_ints", std::bind(&AddTwoIntsServerNode::serviceCallback, this,
      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    RCLCPP_INFO(this->get_logger(), "Add Two Ints Server has been started.");
  }
private:
  rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr service_;
  int counter_;

  void serviceCallback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,
    const std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response> response)
  {
    (void)request_header;
    RCLCPP_INFO(this->get_logger(), "Incoming request");
    response->sum = request->a + request->b + request->c;
    RCLCPP_INFO(this->get_logger(), "Sending back response: [%d]", (int) response->sum);
    counter_++;
    RCLCPP_INFO(this->get_logger(), "Counter: [%d]", counter_);
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<AddTwoIntsServerNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}