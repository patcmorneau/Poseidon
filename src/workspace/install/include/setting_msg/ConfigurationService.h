// Generated by gencpp from file setting_msg/ConfigurationService.msg
// DO NOT EDIT!


#ifndef SETTING_MSG_MESSAGE_CONFIGURATIONSERVICE_H
#define SETTING_MSG_MESSAGE_CONFIGURATIONSERVICE_H

#include <ros/service_traits.h>


#include <setting_msg/ConfigurationServiceRequest.h>
#include <setting_msg/ConfigurationServiceResponse.h>


namespace setting_msg
{

struct ConfigurationService
{

typedef ConfigurationServiceRequest Request;
typedef ConfigurationServiceResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct ConfigurationService
} // namespace setting_msg


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::setting_msg::ConfigurationService > {
  static const char* value()
  {
    return "c7428de72b961d5dc25117ffa14882f8";
  }

  static const char* value(const ::setting_msg::ConfigurationService&) { return value(); }
};

template<>
struct DataType< ::setting_msg::ConfigurationService > {
  static const char* value()
  {
    return "setting_msg/ConfigurationService";
  }

  static const char* value(const ::setting_msg::ConfigurationService&) { return value(); }
};


// service_traits::MD5Sum< ::setting_msg::ConfigurationServiceRequest> should match
// service_traits::MD5Sum< ::setting_msg::ConfigurationService >
template<>
struct MD5Sum< ::setting_msg::ConfigurationServiceRequest>
{
  static const char* value()
  {
    return MD5Sum< ::setting_msg::ConfigurationService >::value();
  }
  static const char* value(const ::setting_msg::ConfigurationServiceRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::setting_msg::ConfigurationServiceRequest> should match
// service_traits::DataType< ::setting_msg::ConfigurationService >
template<>
struct DataType< ::setting_msg::ConfigurationServiceRequest>
{
  static const char* value()
  {
    return DataType< ::setting_msg::ConfigurationService >::value();
  }
  static const char* value(const ::setting_msg::ConfigurationServiceRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::setting_msg::ConfigurationServiceResponse> should match
// service_traits::MD5Sum< ::setting_msg::ConfigurationService >
template<>
struct MD5Sum< ::setting_msg::ConfigurationServiceResponse>
{
  static const char* value()
  {
    return MD5Sum< ::setting_msg::ConfigurationService >::value();
  }
  static const char* value(const ::setting_msg::ConfigurationServiceResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::setting_msg::ConfigurationServiceResponse> should match
// service_traits::DataType< ::setting_msg::ConfigurationService >
template<>
struct DataType< ::setting_msg::ConfigurationServiceResponse>
{
  static const char* value()
  {
    return DataType< ::setting_msg::ConfigurationService >::value();
  }
  static const char* value(const ::setting_msg::ConfigurationServiceResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // SETTING_MSG_MESSAGE_CONFIGURATIONSERVICE_H
