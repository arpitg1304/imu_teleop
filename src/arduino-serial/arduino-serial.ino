/*
 * Written by Daniel Wivagg
 * Wiring: SDA-A4, SCL-A5, VDD-3.3V, GND-GND, BTN-D2/GND
 */
#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>
#include <ros.h>
#include <sensor_msgs/ImuMin.h>

sensor_msgs::ImuMin imu_msg;

ros::NodeHandle nh;
ros::Publisher imu_pub("/arduino/imu_data", &imu_msg);

L3G gyro;
LSM303 compass;

void setup() {
  
  Serial.begin(57600);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();

  compass.init();
  compass.enableDefault();

  // Setup code for the button ISR
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), BtnISR, CHANGE);

  nh.initNode();
  nh.advertise(imu_pub);
}

void loop() {
    gyro.read();
    compass.read();
    
    imu_msg.linear_acceleration.x = compass.a.x;
    imu_msg.linear_acceleration.y = compass.a.y;
    imu_msg.linear_acceleration.z = compass.a.z;

    imu_msg.orientation.x = compass.m.x;
    imu_msg.orientation.y = compass.m.y;
    imu_msg.orientation.z = compass.m.z;
    
    imu_msg.angular_acceleration.x = gyro.g.x;
    imu_msg.angular_acceleration.y = gyro.g.y;
    imu_msg.angular_acceleration.z = gyro.g.z;
    
    imu_pub.publish(&imu_msg);
    nh.spinOnce();
    delay(5);
  
}

void BtnISR() {
    delay(50);
    
}
