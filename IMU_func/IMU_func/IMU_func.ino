#include "GY_85.h" // IMU
#include <Wire.h> // Used for I2C (IMU and PCA9685)

GY_85 GY85; // create the IMU object

double interval; // time interval
double timer = 0; // Previous time

// ================== Variables for IMU =====================
int weight = 80; // weight of complementary filter
double gyro_roll = 0; // Roll angle calculated by gyroscope
double acce_roll = 0; // Roll angle calculated by accelerometer
double filter_roll = 0; // Roll angle after filtering
double delta_angle = 0;

double gyro_pitch = 0; // Roll angle calculated by gyroscope
double acce_pitch = 0; // Roll angle calculated by accelerometer
double filter_pitch = 0; // Roll angle after filtering
double delta_angle2 = 0;
// ==========================================================

// ================== Functions for IMU =====================
double read_roll();
double read_pitch();
// ==========================================================


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
  
  // Set time interval and timer
  interval = micros() - timer; // time interval = current time - previous time
  timer = micros(); // Set current time as previous time

  double roll = read_roll();
  double pitch = read_pitch();

  Serial.print("pitch = ");
  Serial.print(pitch);
  Serial.print(", roll = ");
  Serial.println(roll);
  

  delay(50);
}

double read_pitch() {

  // Read accelerometer
  double ax = GY85.accelerometer_x( GY85.readFromAccelerometer() ); // Acceleration in x direction
  double az = GY85.accelerometer_z( GY85.readFromAccelerometer() ); // Acceleration in z direction

  // Read gyroscope (rate of angular change)
  float gx = GY85.gyro_x( GY85.readGyro() );
  // Serial.print("gx = ");

  delta_angle = gx * (interval/1000000);
  gyro_pitch += delta_angle;
  
  acce_pitch = 90 - abs((atan2(az, ax) * 180/PI));        // Angle according to Accelerometer  (added the last element to make sure that it ended in zero degrees)

  // Complementary filter: combine gyrox (roll angle according to gyro) and roll (roll angle according to accelerometer)
  filter_pitch = (acce_pitch + weight * gyro_pitch) / (1 + weight);

  return filter_pitch;
}

double read_roll() {
  // Read accelerometer
  double ay = GY85.accelerometer_y( GY85.readFromAccelerometer() ); // Acceleration in y direction
  double az = GY85.accelerometer_z( GY85.readFromAccelerometer() ); // Acceleration in z direction

  // Read gyroscope (rate of angular change)
  float gy = GY85.gyro_y( GY85.readGyro() );

  delta_angle2 = gy * (interval/1000000);
  gyro_roll += delta_angle2;
  
  acce_roll = -(90 - abs((atan2(az, ay) * 180/PI)));

  // Complementary filter: combine gyrox (roll angle according to gyro) and roll (roll angle according to accelerometer)
  filter_roll = (acce_roll + weight * gyro_roll) / (1+ weight);

  return filter_roll;
}
