/**
 * 该例程将发布chatter话题，消息类型String
 */
 
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <serial/serial.h>
#include <iostream>


int fd;
int main(int argc, char **argv)
{
  // ROS节点初始化
  ros::init(argc, argv, "talker");
  
  // 创建节点句柄
  ros::NodeHandle n;

  uint8_t open[5] = {0x50, 0x06, 0x05, 0x01, 0xA4};
  uint8_t close[5] = {0x50, 0x06, 0x05, 0x00, 0xA5};
  uint8_t succession[4] = {0x50, 0x06, 0x03, 0xA7};


  //创建一个serial类
    serial::Serial sp;
    //创建timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(100);
    //设置要打开的串口名称
    sp.setPort("/dev/ttyAMA2");
    //设置串口通信的波特率
    sp.setBaudrate(9600);
    //串口设置timeout
    sp.setTimeout(to);
 
    try
    {
        //打开串口
        sp.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }
    
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyAMA2 is opened.");
    }
    else
    {
        return -1;
    }
        
  //sp.write(open, sizeof(open));
  sp.write(succession, sizeof(succession));

  // 创建一个Publisher，发布名为chatter的topic，消息类型为std_msgs::String
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  // 设置循环的频率
  //ros::Rate loop_rate(100);
  
  ros::Rate loop_rate(100);
  int count = 0;
  while (ros::ok())
  {
  
    //获取缓冲区内的字节数
        size_t n = sp.available();
        if(n!=0)
        {
            uint8_t buffer[1024];
            //读出数据
            n = sp.read(buffer, n);
            
            for(int i=0; i<n; i++)
            {
                //16进制的方式打印到屏幕
                std::cout << std::hex << (buffer[i] & 0xff) << " ";
            }
            std::cout << std::endl;

        }
	// 初始化std_msgs::String类型的消息
    std_msgs::String msg;
    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

	// 发布消息
    //ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);

	// 循环等待回调函数
    ros::spinOnce();
	// 按照循环频率延时
    loop_rate.sleep();
    
    ++count;
  }
  sp.write(close, sizeof(close));
  sp.close();
  return 0;
}
