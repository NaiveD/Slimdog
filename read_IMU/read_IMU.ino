#include "GY_85.h" // IMU
#include <Wire.h> // Used for I2C (IMU and PCA9685)
 
GY_85 GY85; // create the IMU object

int weight = 100; // weight of complementary filter
double interval; // time interval
double timer = 0; // Previous time
   
double roll = 0; // roll angle read by IMU
double filterroll = 0; // roll angle after filtering
double gyrox = 0; // roll angle calculated by gyroscope
double debug = 0; // delta theta (the changed angle, calculated by gx*interval, then added to the original angle)
 
void setup() {
    Wire.begin(); // For I2C
    delay(10);
    Serial.begin(9600);
    delay(10);
    GY85.init();
    delay(10);
}
 
void loop()
{
  // Read acceleration in the 3 axis
  double ax = GY85.accelerometer_x( GY85.readFromAccelerometer() ); // Acceleration in x direction
  double ay = GY85.accelerometer_y( GY85.readFromAccelerometer() ); // Acceleration in y direction
  double az = GY85.accelerometer_z( GY85.readFromAccelerometer() ); // Acceleration in z direction

 // Read gyroscope (rate of angular change) in the 3 axis
  float gx = GY85.gyro_x( GY85.readGyro() );
  float gy = GY85.gyro_y( GY85.readGyro() );
  float gz = GY85.gyro_z( GY85.readGyro() );
// float gt = GY85.temp  ( GY85.readGyro() ); // temperature (no use)

  // Read from compass (no use)
// int cx = GY85.compass_x( GY85.readFromCompass() );
// int cy = GY85.compass_y( GY85.readFromCompass() );
// int cz = GY85.compass_z( GY85.readFromCompass() );

  // Set time interval and timer
  interval = micros() - timer; // time interval = current time - previous time
  timer = micros(); // Set current time as previous time

  // interval is around 81000 (microsecond) = 81000/1000 (millisecond) = 81000/1000000 (second)
  // here interval/1000000 is transforming from microsecond to second
  debug = gx*(interval/1000000); // delta angle (debug) = angular rate(gx) * time interval(interval)  (in degree)
  gyrox += debug; // Roll angle according to gyro
 
  roll = (atan2(-ax, az) * 180/PI) -2.90f;     // Angle according to Accelerometer  (added the last element to make sure that it ended in zero degrees)
  roll += 180;

  // Complementary filter: combine gyrox (roll angle according to gyro) and roll (roll angle according to accelerometer)
  filterroll = (roll + weight * gyrox) / (1 + weight);

  // Roll by gyro
  Serial.print("gyro_roll = ");
  Serial.print(gyrox);
  Serial.print(", ");

  // Roll by accelerometer
  Serial.print(", accel_roll = ");
  Serial.print(roll);

  // Roll by complementary filter
  Serial.print(", filter_roll = ");
  Serial.println  ( filterroll ); // roll using complementary filter 
    
  delay(50);
}
