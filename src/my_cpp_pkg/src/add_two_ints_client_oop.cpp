#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/add_two_ints.hpp"


class AddTwoIntsClientNode : public rclcpp::Node
{
public:
  AddTwoIntsClientNode() : Node("add_two_ints_client")
  {
    threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoInts, this, 1, 2)));
    threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoInts, this, 1, 20)));
    threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoInts, this, 6, 4)));
  }
private:
  void callAddTwoInts(int a, int b)
  {
    // create client and bind to "add_two_ints" service!
    auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    while (!client->wait_for_service(std::chrono::seconds(1))) {
      RCLCPP_WARN(this->get_logger(), "Waiting for server to be up");
    }
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = a;
    request->b = b;

    RCLCPP_INFO(this->get_logger(), "Sending request");

    // this is async call so we need to wait for the future to be available
    auto future = client->async_send_request(request);

    try {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Service response %d from request (%d , %d)", (int) response->sum, (int) request->a, (int) request->b);
    } catch (...) {
        RCLCPP_ERROR(this->get_logger(), "Service call failed");
    }
  }

  std::vector<std::thread> threads_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<AddTwoIntsClientNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}