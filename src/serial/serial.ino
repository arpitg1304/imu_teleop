/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low gyro data registers.
They can be converted to units of dps (degrees per second) using the
conversion factors specified in the datasheet for your particular
device and full scale setting (gain).

Example: An L3GD20H gives a gyro X axis reading of 345 with its
default full scale setting of +/- 245 dps. The So specification
in the L3GD20H datasheet (page 10) states a conversion factor of 8.75
mdps/LSB (least significant bit) at this FS setting, so the raw
reading of 345 corresponds to 345 * 8.75 = 3020 mdps = 3.02 dps.
*/
/*
Wiring: SDA-A4, SCL-A5, VDD-3.3V, GND-GND, BTN-D2/GND
*/

#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist imu_msg;

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
  attachInterrupt(digitalPinToInterrupt(2), BtnISR, FALLING);

  nh.initNode();
  nh.advertise(imu_pub);
}

void loop() {
    gyro.read();
    compass.read();
    
    imu_msg.linear.x = compass.a.x;
    imu_msg.linear.y = compass.a.y;
    imu_msg.linear.z = compass.a.z;
    imu_msg.angular.x = gyro.g.x;
    imu_msg.angular.y = gyro.g.y;
    imu_msg.angular.z = gyro.g.z;
    
    imu_pub.publish(&imu_msg);
    nh.spinOnce();
    delay(5);
  
}

void BtnISR() {
    Serial.println("Button pressed");
}
