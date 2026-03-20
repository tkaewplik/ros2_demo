# ros2_demo

## Tutorial
https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Introducing-Turtlesim/Introducing-Turtlesim.html


## Build
```bash
$ colcon build --packages-select my_cpp_pkg
```
**note** if you can not execute your program, one of the reason might be about conda, please diactivate it before using ros2.

## Execute
```bash
$ source install/local_setup.bash
$ ros2 run my_cpp_pkg cpp_node
```
## RENAME
```bash
$ ros2 run my_cpp_pkg cpp_node --ros-args -r __node:=node1
```

## Make pakge
```bash
$ ros2 pkg create --build-type ament_cmake --node-name my_node my_package
```

## Rqt and rtq_graph
this is a tool to see the relation between the node and so on using graph UI. (maybe made from QT... library). you can run it at the same time your run your nodes in order to debuging. Also, `rqt` can be used to call service so you don't have to run the command manually in the terminal.

## Turtlesim
run a waling turtle program for using as controlling turtle by ros
```bash
# open the turtle UI
$ ros2 run turtlesim turtlesim_node --ros-args -r __node:=turtle1
# open the turtle controlling application (using keyboard)
$ ros run turtlesim turtle_teleop_key
```
## Debug node
```bash
# see the list of current ndoe
$ ros2 node list
# see the info of the node
$ ros2 node info /node_name
```
## Debug topic
```bash
# see the list of current topic
$ ros2 topic list
# see the topic 
$ ros2 topic hz /robot_news
$ ros2 topic echo /robot_news
$ ros2 topic bw  /robot_news
# see the data type of the topic
$ ros2 topic info /robot_news
# when you want to know more about the datatype (example_interfaces/msg/String is data type)
$ ros2 interface show example_interface/msg/String
# publish a topic manually
$ ros2 topic pub -r 10 /robot_news example_interfaces/msg/String "{data: 'hello from terminal'}"
```

## Rename of topic
```bash
$ ros2 run my_cpp_pkg robot_news_station --ros-args -r robot_news:=my_new_topic
$ ros2 run my_cpp_pkg smartphone --ros-args -r robot_news:=my_new_topic
```

## See services
```bash
$ ros2 service list
$ ros2 service show <service_name>
```

## Run service
```bash
# note: you have to spare the space between : and number unless it is going to error
$ ros2 service call /add_two_ints example_interfaces/srv/AddTwoInts "{a: 10, b: 5}"
```

## rqt_console
to debug the log from ros2
```bash
$ ros2 run rqt_console rqt_console
```

## bag
this is the record of your published data, so you can replay it later. to find the problem for  example.

## msg and srv
message and service inteface can be created by writing a file in `.msg` and `.srv` extension. then you have to add the `rosidl_default_generators` to the buildtool_depend and `rosidl_default_runtime` to the exec_depend in `package.xml`. finally, you have to add the `rosidl_interface_packages` to the member_of_group.

with this setup, you can use your custom message and service in your package.
please check `src/tutorial_interfaces/msg/Num.msg` and `src/tutorial_interfaces/srv/AddThreeInts.srv` as an example.

# ros2 doctor
this command is used to check the health of your ros2 installation and find the problem.

# ros2 param
you can use this command to see the parameter of the node.
when create a node you can declare a parameter in the constructor of the node.
and that one can be changed by using `ros2 param set` command in real time.

# ros2 launch
when you would like to launch multiple nodes, you can use `ros2 launch` command.
please check `launch/cpp_parameters_launch.py` as an example.
and you can change the parameter in the launch file.

# ros2 pluginlib
plugin is a way to load a code dynamically at runtime. 
you have to create a virtual base class first in order to use plugin
create the class loader or instance loader that bind the virtual class
```cpp
// initialize the class loader
pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader(
    "polygon_base",
    "polygon_base::RegularPolygon"
);

// load plugin or the instance from the class loader, this class can not have a arguments in constructor if you need to pass arugment, you have to use initialize() method.
std::shared_ptr<polygon_base::RegularPolygon> square =
      poly_loader.createSharedInstance("polygon_plugins::Square");
```