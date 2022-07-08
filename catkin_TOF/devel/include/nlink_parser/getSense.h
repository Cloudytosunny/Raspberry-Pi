// Generated by gencpp from file nlink_parser/getSense.msg
// DO NOT EDIT!


#ifndef NLINK_PARSER_MESSAGE_GETSENSE_H
#define NLINK_PARSER_MESSAGE_GETSENSE_H

#include <ros/service_traits.h>


#include <nlink_parser/getSenseRequest.h>
#include <nlink_parser/getSenseResponse.h>


namespace nlink_parser
{

struct getSense
{

typedef getSenseRequest Request;
typedef getSenseResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct getSense
} // namespace nlink_parser


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::nlink_parser::getSense > {
  static const char* value()
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const ::nlink_parser::getSense&) { return value(); }
};

template<>
struct DataType< ::nlink_parser::getSense > {
  static const char* value()
  {
    return "nlink_parser/getSense";
  }

  static const char* value(const ::nlink_parser::getSense&) { return value(); }
};


// service_traits::MD5Sum< ::nlink_parser::getSenseRequest> should match
// service_traits::MD5Sum< ::nlink_parser::getSense >
template<>
struct MD5Sum< ::nlink_parser::getSenseRequest>
{
  static const char* value()
  {
    return MD5Sum< ::nlink_parser::getSense >::value();
  }
  static const char* value(const ::nlink_parser::getSenseRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::nlink_parser::getSenseRequest> should match
// service_traits::DataType< ::nlink_parser::getSense >
template<>
struct DataType< ::nlink_parser::getSenseRequest>
{
  static const char* value()
  {
    return DataType< ::nlink_parser::getSense >::value();
  }
  static const char* value(const ::nlink_parser::getSenseRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::nlink_parser::getSenseResponse> should match
// service_traits::MD5Sum< ::nlink_parser::getSense >
template<>
struct MD5Sum< ::nlink_parser::getSenseResponse>
{
  static const char* value()
  {
    return MD5Sum< ::nlink_parser::getSense >::value();
  }
  static const char* value(const ::nlink_parser::getSenseResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::nlink_parser::getSenseResponse> should match
// service_traits::DataType< ::nlink_parser::getSense >
template<>
struct DataType< ::nlink_parser::getSenseResponse>
{
  static const char* value()
  {
    return DataType< ::nlink_parser::getSense >::value();
  }
  static const char* value(const ::nlink_parser::getSenseResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // NLINK_PARSER_MESSAGE_GETSENSE_H