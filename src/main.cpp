#include <Arduino.h>
#include <ros.h>
#include <rovit_fw_msgs/Rovit.h>
#include <rovit_fw_msgs/RovitDebug.h>
#include <geometry_msgs/Twist.h>
#include <Motor.h>

ros::NodeHandle nh;

Motor motor_kiri;
Motor motor_kanan;
motor_configs motor_kiri_configs;
motor_configs motor_kanan_configs;

// static char* TAG = "debug";
rovit_fw_msgs::Rovit robot_data_msg;
rovit_fw_msgs::RovitDebug debug_data_msg;
ros::Publisher data_pub("robot_covid/data", &robot_data_msg);
ros::Publisher debug_pub("robot_covid/debug", &debug_data_msg);

void cmdvel_cb(const geometry_msgs::Twist& cmd_data){
  nh.loginfo("Test");
  
  // Test jalan PID motor
  motor_kiri.auto_speed(cmd_data.linear.x * 100);
  motor_kanan.auto_speed(cmd_data.linear.x * 100);
  debug_data_msg.PID_kiri.input = motor_kiri.get_speed();
  debug_data_msg.PID_kanan.input = motor_kanan.get_speed();
  debug_data_msg.PID_kiri.output = motor_kiri.get_control_out();
  debug_data_msg.PID_kanan.output = motor_kanan.get_control_out();
  debug_data_msg.header.stamp = nh.now();
  debug_pub.publish(&debug_data_msg);

  // Test jalan sederhana motor
  // motor_kiri.set_pwm(cmd_data.linear.x * 200);
  // motor_kanan.set_pwm(cmd_data.linear.x * 200);
  // robot_data_msg.left_speed = motor_kiri.get_rpm(); //Dalam RPM
  // robot_data_msg.right_speed = motor_kanan.get_rpm(); //Dalam RPM
  // Catat rpm maksimal yang didapatkan

  data_pub.publish(&robot_data_msg);
}

void setup_motor(){
  motor_kiri_configs.pin_enable     = 4;
  motor_kiri_configs.pin_encoder    = 5;
  motor_kiri_configs.pin_pwm        = 13;
  motor_kiri_configs.pin_direction  = 12;
  motor_kiri_configs.pwm_freq       = 1000;
  motor_kiri_configs.reversed       = true;
  motor_kiri_configs.ppr            = 10; // Pulse per revolution (pulse per satu putaran)
  // Uncomment untuk pengetesan fitur PID
  motor_kiri_configs.K_P            = 1.0;
  motor_kiri_configs.K_I            = 1.0;
  motor_kiri_configs.K_D            = 0.0;
  motor_kiri.config(motor_kiri_configs);
  motor_kanan_configs.pin_enable     = 14;
  motor_kanan_configs.pin_encoder    = 15;
  motor_kanan_configs.pin_pwm        = 19;
  motor_kanan_configs.pin_direction  = 18;
  motor_kanan_configs.pwm_freq       = 1000;
  motor_kanan_configs.reversed       = true;
  motor_kanan_configs.ppr            = 10;
  // Uncomment untuk pengetesan fitur PID
  motor_kanan_configs.K_P            = 1.0;
  motor_kanan_configs.K_I            = 1.0;
  motor_kanan_configs.K_D            = 0.0;
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
  nh.advertise(debug_pub);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(10);
}