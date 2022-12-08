#include <Arduino.h>
#include <ros.h>
#include <rovit_fw_msgs/rovit_msgs.h>
#include <geometry_msgs/Twist.h>
#include <Motor.h>

ros::NodeHandle nh;

Motor motor_kiri;
Motor motor_kanan;
motor_configs motor_kiri_configs;
motor_configs motor_kanan_configs;

// static char* TAG = "debug";
rovit_fw_msgs::rovit_msgs robot_data_msg;
ros::Publisher data_pub("robot_covid", &robot_data_msg);

void cmdvel_cb(const geometry_msgs::Twist& cmd_data){
  nh.loginfo("Test");
  robot_data_msg.imu_acc = cmd_data.linear;
  robot_data_msg.imu_gyro = cmd_data.angular;
  motor_kiri.set_pwm(cmd_data.linear.x * 10);
  motor_kanan.set_pwm(cmd_data.linear.x * 10);
  data_pub.publish(&robot_data_msg);
}

void setup_motor(){
  motor_kiri_configs.pin_enable     = 4;
  motor_kiri_configs.pin_encoder    = 5;
  motor_kiri_configs.pin_pwm        = 12;
  motor_kiri_configs.pin_direction  = 13;
  motor_kiri_configs.pwm_freq       = 1000;
  motor_kiri_configs.reversed       = true;
  motor_kiri_configs.ppr            = 10;
  motor_kiri.config(motor_kiri_configs);
  motor_kanan_configs.pin_enable     = 14;
  motor_kanan_configs.pin_encoder    = 15;
  motor_kanan_configs.pin_pwm        = 18;
  motor_kanan_configs.pin_direction  = 19;
  motor_kanan_configs.pwm_freq       = 1000;
  motor_kanan_configs.reversed       = true;
  motor_kanan_configs.ppr            = 10;
  motor_kanan.config(motor_kanan_configs);
}

ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", cmdvel_cb);

void setup() {
  // put your setup code here, to run once:
  setup_motor();
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(cmd_sub);
  nh.advertise(data_pub);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(10);
}