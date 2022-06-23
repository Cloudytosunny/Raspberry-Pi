/**
 * AddTwoInts Client
 */
 
#include <cstdlib>
#include "ros/ros.h"

#include "learning_communication/AddTwoInts.h"
#include "sensor_msgs/Joy.h"

float ALLaxes=0;
int ALLbuttons=0;
int stopflag = 0;

  // 创建learning_communication::AddTwoInts类型的service消息
  learning_communication::AddTwoInts srv;

// 接收到订阅的消息后，会进入消息回调函数
void chatterCallback(const sensor_msgs::JoyConstPtr& msg,
                                            ros::ServiceClient client2)
{
  ALLaxes = 0;
  // 将接收到的消息打印出来
  
  for (int i = 0; i < 11 ; i++)
  {ALLbuttons = ALLbuttons+(long int)msg->buttons[i];}
  for (int j = 0; j < 8 ; j++)
  {ALLaxes = ALLaxes + (float)msg->axes[j];}
  ROS_INFO("I heard: [%lf] and [%d]", ALLaxes, ALLbuttons);

if(ALLbuttons != 0 || ALLaxes != 2 || stopflag >0){
  if(ALLbuttons != 0 || ALLaxes != 2)
  {stopflag=6;}
  //if(stopflag%6 == 0 && stopflag > 0){stopflag = stopflag -1;}
  //if(stopflag < 2){stopflag = stopflag + 1;}
  //else{
  stopflag = stopflag - 1;
  ALLbuttons = 0;
  ALLaxes = 0;
  srv.request.a = (long int)msg->axes[1];
  srv.request.b = (long int)msg->axes[0];
  //srv.request.c[1] = (long int)msg->buttons[1];
  for (int i = 0; i < 11 ; i++)
  {srv.request.c[i] = (long int)msg->buttons[i];}
  for (int j = 0; j < 8 ; j++)
  {srv.request.d[j] = (float)msg->axes[j];}
  //stopflag = 24;
  //if((long int)msg->buttons[6] == 1){stopflag = 0;}
  ROS_INFO("I: [%lf] and [%d]", ALLaxes, stopflag);
  // 发布service请求，等待加法运算的应答结果
  if (client2.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
  }
  //}
}

}

int main(int argc, char **argv)
{
  // ROS节点初始化
  ros::init(argc, argv, "add_two_ints_client1");
  
  // // 从终端命令行获取两个加数
  // if (argc != 3)
  // {
  //   ROS_INFO("usage: add_two_ints_client X Y");
  //   return 1;
  // }

  // 创建节点句柄
  ros::NodeHandle n;
  
  // 创建一个client，请求add_two_int service，service消息类型是learning_communication::AddTwoInts
  ros::ServiceClient client1 = n.serviceClient<learning_communication::AddTwoInts>("add_two_ints");
  
  ros::Subscriber sub = n.subscribe<sensor_msgs::Joy>("joy", 1000, boost::bind(chatterCallback, _1, client1));


  // 循环等待回调函数
  ros::spin();

  return 0;
}
