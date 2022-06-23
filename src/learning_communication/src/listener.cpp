/**
 * 该例程将订阅chatter话题，消息类型String
 */
 
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"

// 接收到订阅的消息后，会进入消息回调函数
void chatterCallback(const sensor_msgs::JoyConstPtr& msg)
{
  // 将接收到的消息打印出来
  ROS_INFO("I heard: [%f]", msg->axes[1]);
}

int main(int argc, char **argv)
{
  // 初始化ROS节点
  ros::init(argc, argv, "listener");

  // 创建节点句柄
  ros::NodeHandle n;

  // 创建一个Subscriber，订阅名为chatter的topic，注册回调函数chatterCallback
  ros::Subscriber sub = n.subscribe("joy", 1000, chatterCallback);

  // 循环等待回调函数
  ros::spin();

  return 0;
}
