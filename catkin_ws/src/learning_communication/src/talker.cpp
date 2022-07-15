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
float data;

std_msgs::String msg;
std::stringstream ss;

int main(int argc, char **argv)
{
  // ROS节点初始化
  ros::init(argc, argv, "talker");
  
  // 创建节点句柄
  ros::NodeHandle n;
  char buf[64] = {'\0'};
  char open[5] = {0x50, 0x06, 0x05, 0x01, 0xA4};
  char close[5] = {0x50, 0x06, 0x05, 0x00, 0xA5};
  char succession[4] = {0x50, 0x06, 0x03, 0xA7};
  int n_read;
  wiringPiSetup();
  
  if((fd = serialOpen("/dev/ttyAMA3",9600)) < 0) {
        printf("serial err\n");}
  else{ROS_INFO_STREAM("/dev/ttyAMA3 is opened.");}
        
  

  // 创建一个Publisher，发布名为chatter的topic，消息类型为std_msgs::String
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  // 设置循环的频率
  ros::Rate loop_rate(100);
  write(fd,succession,sizeof(succession));

  int count = 0;
  while (ros::ok())
  {
    //ROS_INFO("data %d",serialDataAvail(fd));
    //n_read = read(fd,buf,sizeof(buf));
    n_read = read(fd,buf,serialDataAvail(fd));
    //write(fd,close,sizeof(close));
    //write(fd,succession,sizeof(succession));
    if(n_read != 0){
			
			//for(int i=0; i<n_read; i++)//16进制的方式打印到屏幕
            //{std::cout << std::hex << (buf[i] & 0xff) << " ";}
            //std::cout << std::endl;
            if(buf[0]==80 && buf[1]==6 && (buf[6] & 0xff)==0x2e)
            {
            data = buf[5]%48+0.1*(buf[7]%48)+0.01*(buf[8]%48)+0.001*(buf[9]%48)+0.0001*(buf[10]%48);
            //ROS_INFO("data %f\n",buf[5]%48+0.1*(buf[7]%48)+0.01*(buf[8]%48)+0.001*(buf[9]%48)+0.0001*(buf[10]%48)); 
             }
			}
	 // 初始化std_msgs::String类型的消息
    ss.str("");
    ss << data << "  ";
    msg.data = ss.str();

	 // 发布消息
    //ROS_INFO("ss:%s", msg.data.c_str());
    chatter_pub.publish(msg);
    serialFlush(fd);
    
   // 循环等待回调函数
    ros::spinOnce();

    
	 // 按照循环频率延时
    
    loop_rate.sleep();
    
    ++count;
  }
  write(fd,close,sizeof(close));
  serialClose(fd);
  return 0;
}
