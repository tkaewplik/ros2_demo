# ros2_demo

## Build
```bash
$ colcon build --packages-select my_cpp_pkg
```
**note** if you can not execute your program, one of the reason might be about conda, please diactivate it before using ros2.

## Execute
```bash
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
this is a tool to see the relation between the node and so on using graph UI. (maybe made from QT... library). you can run it at the same time your run your nodes in order to debuging.

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