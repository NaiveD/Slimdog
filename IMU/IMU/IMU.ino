#include "GY_85.h" // IMU
#include <Wire.h> // Used for I2C (IMU and PCA9685)

GY_85 GY85; // create the IMU object

int weight = 30; // weight of complementary filter
double interval; // time interval
double timer = 0; // Previous time

double gyro_roll = 0; // Roll angle calculated by gyroscope
double acce_roll = 0; // Roll angle calculated by accelarator
double filter_roll = 0; // Roll angle after filtering
double delta_angle = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // For I2C
  delay(10);
  Serial.begin(9600);
  delay(10);
  GY85.init();
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  double ax = GY85.accelerometer_x( GY85.readFromAccelerometer() ); // Acceleration in x direction
  double ay = GY85.accelerometer_y( GY85.readFromAccelerometer() ); // Acceleration in y direction
  double az = GY85.accelerometer_z( GY85.readFromAccelerometer() ); // Acceleration in z direction

  // Read gyroscope (rate of angular change) in the 3 axis
  float gx = GY85.gyro_x( GY85.readGyro() );
  float gy = GY85.gyro_y( GY85.readGyro() );
  float gz = GY85.gyro_z( GY85.readGyro() );


//  Serial.print("ax = ");
//  Serial.print(ax);
//  Serial.print(", ay = ");
//  Serial.print(ay);
//  Serial.print(", az = ");
//  Serial.print(az);
//  Serial.print(", gx = ");
//  Serial.print(gx);
//  Serial.print(", gy = ");
//  Serial.print(gy);
//  Serial.print(", gz = ");
//  Serial.println(gz);
  
  // Set time interval and timer
  interval = micros() - timer; // time interval = current time - previous time
  timer = micros(); // Set current time as previous time

  delta_angle = gx * (interval/1000000);
  gyro_roll += delta_angle;

  acce_roll = 90-abs((atan2(az, ax) * 180/PI));        // Angle according to Accelerometer  (added the last element to make sure that it ended in zero degrees)

  // Complementary filter: combine gyrox (roll angle according to gyro) and roll (roll angle according to accelerometer)
  filter_roll = (acce_roll + weight * gyro_roll) / (1 + weight);
  
//  Serial.print("gx = ");
//  Serial.print(gx);
//  Serial.print(", delta_angle = ");
//  Serial.print(delta_angle);
  Serial.print(", acce_roll = ");
  Serial.print(acce_roll);
  Serial.print(", gyro_roll = ");
  Serial.print(gyro_roll);
  Serial.print(", filter_roll = ");
  Serial.println(filter_roll);
  
  delay(50);
}
