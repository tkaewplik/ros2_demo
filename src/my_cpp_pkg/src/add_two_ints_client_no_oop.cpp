#include <rclcpp/rclcpp.hpp>
#include "tutorial_interfaces/srv/add_three_ints.hpp"


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("add_two_ints_client_no_oop");

  auto client = node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_two_ints");
  while (!client->wait_for_service(std::chrono::seconds(1))) {
    RCLCPP_WARN(node->get_logger(), "Waiting for server to be up");

  }
  auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
  request->a = 3;
  request->b = 8;
  request->c = 10;

  RCLCPP_INFO(node->get_logger(), "Sending request");

  // this is async call so we need to wait for the future to be available
  auto future = client->async_send_request(request);

  if (rclcpp::spin_until_future_complete(node, future) != rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_ERROR(node->get_logger(), "Service call failed");
  }

  RCLCPP_INFO(node->get_logger(), "Service response %d from request (%d , %d, %d)", (int) future.get()->sum, (int) request->a, (int) request->b, (int) request->c);
  
  rclcpp::shutdown();
  return 0;
}