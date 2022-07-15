#include <ros/ros.h>

#include "init.h"
#include "init_serial.h"
#include "nlink_unpack/nlink_tofsensem_frame0.h"
#include "nlink_unpack/nlink_utils.h"
#include "protocol_extracter/nprotocol_extracter.h"
#include <chrono>
#include <thread>

uint8_t buffer[8];

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tofsensem_parser");
  ros::NodeHandle nh;
  serial::Serial serial;
  initSerial(&serial);

  NProtocolExtracter extracter;
  tofsensem::Init init(&extracter);

  buffer[0] = 0x57;
  buffer[1] = 0x10;
  buffer[2] = 0xff;
  buffer[3] = 0xff;
  buffer[4] = 0x04;
  buffer[5] = 0xff;
  buffer[6] = 0xff;
  buffer[7] = 0x67;
  //ros::Rate r(1);
  
  while (ros::ok())
  {
    serial.write(buffer,8);
    auto available_bytes = serial.available();
    std::string str_received;
    if (available_bytes)
    {
      serial.read(str_received, available_bytes);
      extracter.AddNewData(str_received);
    }
    else
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    ros::spinOnce();
  }
  return EXIT_SUCCESS;
}
