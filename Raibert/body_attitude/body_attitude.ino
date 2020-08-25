#include "GY_85.h" // IMU
#include <Wire.h> // Used for I2C (IMU and PCA9685)
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685

// The pwm object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
GY_85 GY85; // create the IMU object

double interval; // time interval
double timer = 0; // Previous time

// ================== Variables for IMU =====================
int weight = 30; // weight of complementary filter
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

float angle0 = 96.14, angle1 = 98.02, angle2 = 50.88, angle4 = 88.41, angle5 = 84.42, angle6 = 44.47, angle8 = 91.76, angle9 = 82.29, angle10 = 132.76, angle12 = 90.42, angle13 = 99.12, angle14 = 136.39;

// Helper functions
int angletoPWM(int ang);

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // For I2C
  delay(10);
  Serial.begin(9600);
  delay(10);
  GY85.init();
  delay(10);
  
  Serial.println("Begin setting initial body attitude...");
  
  // Move the Yellow motors (1, 5, 9, 13)
  pwm.setPWM(1, 0, angletoPWM(angle1, 1)); // RF
  pwm.setPWM(5, 0, angletoPWM(angle5, 5)); // RB
  pwm.setPWM(9, 0, angletoPWM(angle9, 9)); // LF
  pwm.setPWM(13, 0, angletoPWM(angle13, 13)); // LB

  // Move the Orange motors (2, 6, 10, 14)
  pwm.setPWM(2, 0, angletoPWM(angle2, 2)); // RF
  pwm.setPWM(6, 0, angletoPWM(angle6, 6)); // RB
  pwm.setPWM(10, 0, angletoPWM(angle10, 10)); // LF
  pwm.setPWM(14, 0, angletoPWM(angle14, 14)); // LB

  // Move the Green motors (0, 4, 8, 12)
  pwm.setPWM(0, 0, angletoPWM(angle0, 0)); // RF
  pwm.setPWM(4, 0, angletoPWM(angle4, 4)); // RB
  pwm.setPWM(8, 0, angletoPWM(angle8, 8)); // LF
  pwm.setPWM(12, 0, angletoPWM(angle12, 12)); // LB

  delay(5000);
  Serial.println("Begin testing body attitude...");
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

  if (pitch > 45)
    pitch = 45;

  if (pitch < -45)
    pitch = -45;

  if (roll > 45)
    roll = 45;

  if (roll < -45)
    roll = -45;
    
  // Control pitch (orange motors: 2, 6, 10, 14)
  angle2 += pitch; // RF orange
  angle6 += pitch; // RB orange
  angle10 -= pitch; // LF orange
  angle14 -= pitch; // LB orange
  // Move the Orange motors (2, 6, 10, 14)
  pwm.setPWM(2, 0, angletoPWM(angle2, 2)); // RF
  pwm.setPWM(6, 0, angletoPWM(angle6, 6)); // RB
  pwm.setPWM(10, 0, angletoPWM(angle10, 10)); // LF
  pwm.setPWM(14, 0, angletoPWM(angle14, 14)); // LB 
  

  // Control roll (yellow motors: 1, 5, 9, 13)
  angle1 += roll; // RF yellow
  angle5 -= roll; // RB yellow
  angle9 += roll; // LF yellow
  angle13 -= roll; // LB yellow

  // Move the Yellow motors (1, 5, 9, 13)
  pwm.setPWM(1, 0, angletoPWM(angle1, 1)); // RF
  pwm.setPWM(5, 0, angletoPWM(angle5, 5)); // RB
  pwm.setPWM(9, 0, angletoPWM(angle9, 9)); // LF
  pwm.setPWM(13, 0, angletoPWM(angle13, 13)); // LB

  delay(50);

  // Reset motor angles
  angle2 = 50.88;
  angle6 = 44.47;
  angle10 = 132.76;
  angle14 = 136.39;

  angle1 = 98.02;
  angle5 = 84.42;
  angle9 = 82.29;
  angle13 = 99.12;
}

double read_pitch() {

  // Read accelerometer
  double ax = GY85.accelerometer_x( GY85.readFromAccelerometer() ); // Acceleration in x direction
  double az = GY85.accelerometer_z( GY85.readFromAccelerometer() ); // Acceleration in z direction

  // Read gyroscope (rate of angular change)
  float gx = GY85.gyro_x( GY85.readGyro() );

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

// Convert angle to PWM
int angletoPWM(int ang, int servonum) {
  int pulse;
  
  if (servonum == 0)
    pulse = map(ang, 0, 180, 135, 675); // map the angle into the PWM

  else if (servonum == 1)
    pulse = map(ang, 0, 180, 110, 680); // map the angle into the PWM

  else if (servonum == 2)
    pulse = map(ang, 0, 180, 180, 660); // map the angle into the PWM

  else if (servonum == 4)
    pulse = map(ang, 0, 180, 130, 670); // map the angle into the PWM

  else if (servonum == 5)
    pulse = map(ang, 0, 180, 95, 565); // map the angle into the PWM

  else if (servonum == 6)
    pulse = map(ang, 0, 180, 84, 636); // map the angle into the PWM

  else if (servonum == 8)
    pulse = map(ang, 0, 180, 80, 680); // map the angle into the PWM

  else if (servonum == 9)
    pulse = map(ang, 0, 180, 325, 805); // map the angle into the PWM

  else if (servonum == 10)
    pulse = map(ang, 0, 180, 150, 630); // map the angle into the PWM

  else if (servonum == 12)
    pulse = map(ang, 0, 180, 135, 655); // map the angle into the PWM

  else if (servonum == 13)
    pulse = map(ang, 0, 180, -50, 510); // map the angle into the PWM

  else if (servonum == 14)
    pulse = map(ang, 0, 180, 120, 640); // map the angle into the PWM
    
  return pulse;
}
