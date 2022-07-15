/**
 * AddTwoInts Client
 */
 
#include <cstdlib>
#include "ros/ros.h"
#include "learning_communication/AddTwoInts.h"
#include "learning_communication/getSense.h"

char *id1;
char *id2;
char *id4;


int main(int argc, char **argv)
{
  // ROS节点初始化
  ros::init(argc, argv, "add_two_ints_client");
  
  // 从终端命令行获取两个加数
  //if (argc != 4)
  //{
   // ROS_INFO("usage: add_two_ints_client X Y ID");
    //return 1;
  //}

  // 创建节点句柄
  ros::NodeHandle n;
  
  //id1[0] = n.param<int>("id1",1);
  //id2[0] = n.param<int>("id2",2);
  //id4[0] = n.param<int>("id4",4);
  id1 = "1";
  id2 = "2";
  id4 = "4";
  // 创建一个client，请求add_two_int service，service消息类型是learning_communication::AddTwoInts
  ros::ServiceClient client = n.serviceClient<learning_communication::getSense>("get_TOFsense");
  // 创建learning_communication::AddTwoInts类型的service消息
  learning_communication::getSense srv;
  srv.request.b = atoll(id2);
  srv.request.a = atoll(id1);
  // 设置循环的频率
  ros::Rate loop_rate(10);
  int count = 0;
  
  while (ros::ok())
  {
  if(count == 1)
  {count = 2; srv.request.a = atoll(id1);}
  else if(count == 2)
  {count = 0; srv.request.a = atoll(id2);}
  else
  {count = 1; srv.request.a = atoll(id4);}
  //ROS_INFO("count: %d", count);
  
   client.call(srv);
   // 循环等待回调函数
    ros::spinOnce();
	
	// 按照循环频率延时
   loop_rate.sleep();
  }
  
  
  
  
  // 发布service请求，等待加法运算的应答结果
  if (client.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
