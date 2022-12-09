#ifndef _ROS_rovit_fw_msgs_RovitDebug_h
#define _ROS_rovit_fw_msgs_RovitDebug_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "rovit_fw_msgs/PID.h"

namespace rovit_fw_msgs
{

  class RovitDebug : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef rovit_fw_msgs::PID _PIDs_type;
      _PIDs_type PIDs;

    RovitDebug():
      header(),
      PIDs()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->PIDs.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->PIDs.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "rovit_fw_msgs/RovitDebug"; };
    virtual const char * getMD5() override { return "16efbfb43d7bea1f79c47199e26746ee"; };

  };

}
#endif
