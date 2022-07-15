#include <ros/ros.h>

#include "init.h"
#include "initM.h"
#include "init_serial.h"
#include "nlink_unpack/nlink_tofsensem_frame0.h"
#include "nlink_unpack/nlink_utils.h"
#include "nlink_parser/getSense.h"
#include "protocol_extracter/nprotocol_extracter.h"
#include <chrono>
#include <thread>

uint8_t buffer[8];
serial::Serial serial1;

// service回调函数，输入参数req，输出参数res
bool get(nlink_parser::getSense::Request  &req,
         nlink_parser::getSense::Response &res)
{
  // 将输入参数中的请求数据相加，结果放到应答变量中
  res.sum = req.a + req.b;
  if(req.a == 4){buffer[4] = 0x04;buffer[7] = 0x67;}
  else if(req.a == 1){buffer[4] = 0x01;buffer[7] = 0x64;}
  else if(req.a == 2){buffer[4] = 0x02;buffer[7] = 0x65;}
  serial1.write(buffer,8);
  //ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  //ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  
  return true;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "tofsense_parser");
  ros::NodeHandle nh;
  
  initSerial(&serial1);

  NProtocolExtracter extracter;
  NProtocolExtracter extracterM;
  tofsense::Init init(&extracter, &serial1);
  tofsensem::InitM initm(&extracterM);
  
    // 创建一个名为add_two_ints的server，注册回调函数add()
  ros::ServiceServer service = nh.advertiseService("get_TOFsense", get);

  buffer[0] = 0x57;
  buffer[1] = 0x10;
  buffer[2] = 0xff;
  buffer[3] = 0xff;
  buffer[4] = 0x04;
  buffer[5] = 0xff;
  buffer[6] = 0xff;
  buffer[7] = 0x67;
  //ros::Rate r(1);
  serial1.write(buffer,8);
  while (ros::ok())
  {
    auto available_bytes = serial1.available();
    std::string str_received;
    if (available_bytes)
    {
      serial1.read(str_received, available_bytes);
      if(buffer[4] != 0x04)
      {extracter.AddNewData(str_received);}
      else
      {extracterM.AddNewData(str_received);}
      //extracter.AddNewData(str_received);
    }
    //r.sleep();
    ros::spinOnce();
  }
  return EXIT_SUCCESS;
}
