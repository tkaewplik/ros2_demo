#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalParam: public rclcpp::Node{
private:
    rclcpp::TimerBase::SharedPtr timer_;
public:
    MinimalParam(): Node("minimal_param"){
        this->declare_parameter("my_parameter", "default_value");
        timer_ = this->create_wall_timer(1000ms, std::bind(&MinimalParam::timer_callback, this));
    }
    void timer_callback(){
        std::string value = this->get_parameter("my_parameter").as_string();
        RCLCPP_INFO(this->get_logger(), "My parameter value: %s", value.c_str());
    }
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalParam>());
    rclcpp::shutdown();
    return 0;
}