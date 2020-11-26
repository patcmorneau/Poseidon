// Generated by gencpp from file state_controller_msg/GetStateServiceRequest.msg
// DO NOT EDIT!


#ifndef STATE_CONTROLLER_MSG_MESSAGE_GETSTATESERVICEREQUEST_H
#define STATE_CONTROLLER_MSG_MESSAGE_GETSTATESERVICEREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace state_controller_msg
{
template <class ContainerAllocator>
struct GetStateServiceRequest_
{
  typedef GetStateServiceRequest_<ContainerAllocator> Type;

  GetStateServiceRequest_()
    {
    }
  GetStateServiceRequest_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> const> ConstPtr;

}; // struct GetStateServiceRequest_

typedef ::state_controller_msg::GetStateServiceRequest_<std::allocator<void> > GetStateServiceRequest;

typedef boost::shared_ptr< ::state_controller_msg::GetStateServiceRequest > GetStateServiceRequestPtr;
typedef boost::shared_ptr< ::state_controller_msg::GetStateServiceRequest const> GetStateServiceRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace state_controller_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "state_controller_msg/GetStateServiceRequest";
  }

  static const char* value(const ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetStateServiceRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::state_controller_msg::GetStateServiceRequest_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // STATE_CONTROLLER_MSG_MESSAGE_GETSTATESERVICEREQUEST_H
