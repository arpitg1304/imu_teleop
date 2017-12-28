#ifndef _ROS_sensor_msgs_ImuMin_h
#define _ROS_sensor_msgs_ImuMin_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace sensor_msgs
{

  class ImuMin : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Vector3 _orientation_type;
      _orientation_type orientation;
      typedef geometry_msgs::Vector3 _angular_acceleration_type;
      _angular_acceleration_type angular_acceleration;
      typedef geometry_msgs::Vector3 _linear_acceleration_type;
      _linear_acceleration_type linear_acceleration;

    ImuMin():
      header(),
      orientation(),
      angular_acceleration(),
      linear_acceleration()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->orientation.serialize(outbuffer + offset);
      offset += this->angular_acceleration.serialize(outbuffer + offset);
      offset += this->linear_acceleration.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->orientation.deserialize(inbuffer + offset);
      offset += this->angular_acceleration.deserialize(inbuffer + offset);
      offset += this->linear_acceleration.deserialize(inbuffer + offset);
      return offset;
    }

    const char * getType(){ return "sensor_msgs/Imu"; };
    const char * getMD5(){ return "6a62c6daae103f4ff57a132d6f95cec2"; };

  };

}
#endif
