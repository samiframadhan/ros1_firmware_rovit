#ifndef _ROS_rovit_fw_msgs_rovit_msgs_h
#define _ROS_rovit_fw_msgs_rovit_msgs_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace rovit_fw_msgs
{

  class rovit_msgs : public ros::Msg
  {
    public:
      typedef geometry_msgs::Vector3 _imu_acc_type;
      _imu_acc_type imu_acc;
      typedef geometry_msgs::Vector3 _imu_gyro_type;
      _imu_gyro_type imu_gyro;
      typedef float _left_speed_type;
      _left_speed_type left_speed;
      typedef float _right_speed_type;
      _right_speed_type right_speed;

    rovit_msgs():
      imu_acc(),
      imu_gyro(),
      left_speed(0),
      right_speed(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->imu_acc.serialize(outbuffer + offset);
      offset += this->imu_gyro.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_left_speed;
      u_left_speed.real = this->left_speed;
      *(outbuffer + offset + 0) = (u_left_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_left_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_left_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_speed);
      union {
        float real;
        uint32_t base;
      } u_right_speed;
      u_right_speed.real = this->right_speed;
      *(outbuffer + offset + 0) = (u_right_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_right_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_right_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_speed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->imu_acc.deserialize(inbuffer + offset);
      offset += this->imu_gyro.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_left_speed;
      u_left_speed.base = 0;
      u_left_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_left_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_left_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_left_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->left_speed = u_left_speed.real;
      offset += sizeof(this->left_speed);
      union {
        float real;
        uint32_t base;
      } u_right_speed;
      u_right_speed.base = 0;
      u_right_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_right_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_right_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_right_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->right_speed = u_right_speed.real;
      offset += sizeof(this->right_speed);
     return offset;
    }

    virtual const char * getType() override { return "rovit_fw_msgs/rovit_msgs"; };
    virtual const char * getMD5() override { return "6d915cbb3f4c7cbdf2eae2427842c050"; };

  };

}
#endif
