#include "GY_85.h"
#include <Wire.h> // Used for I2C
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685
#include "vec.hpp"
#include "IK.hpp"

#define CLAMP(x, low, high) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))
/****************** Declaration *********************/
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
GY_85 GY85;
float angle[16];
class Attitude{
public:
    double pitch = 0;
    double roll = 0;
    double pitch_v = 0;
    double roll_v = 0;
    
    double g_pitch = 0;
    double a_pitch = 0;
    double g_roll = 0;
    double a_roll = 0;
    double timer = 0;
    int weight = 30;
    Attitude(){};

};
Attitude att;
double kp, kv;

void getAttitude(GY_85 *GY85, Attitude *att);
int angletoPWM(int ang, int servonum);
void move_motor(int *angle);

/****************** Setup *********************/
void setup(){
  Wire.begin();
  delay(10);
  Serial.begin(9600);
  delay(10);
  GY85.init();
  delay(10);
  pwm.begin();
  pwm.setPWMFreq(60);

  for(int i=0; i<16; ++i){
    angle[i] = 90;
  }

  kp = 0.5;
  kv = 0.0;

  move_motor(angle, &pwm);
  delay(2000);
}
/****************** Loop *********************/
// Attempt 1
// void loop(){
//   getAttitude(&GY85, &att);
//   int diff_pitch = (int)(kp * att.pitch + kv * att.pitch_v);
//   int diff_roll = (int)(kp * att.roll + kv * att.roll_v);

//   // adjust pitch
//   {
//     angle[2] += diff_pitch;
//     angle[6] += diff_pitch;
//     angle[10] -= diff_pitch;
//     angle[14] -= diff_pitch;
//   }

//   // adjust roll
//   {
//     angle[1] += diff_roll;
//     angle[5] -= diff_roll;
//     angle[9] += diff_roll;
//     angle[13] -= diff_roll;
//   }

//   move_motor(angle);
//   delay(250);
// }

// Attempt 2
void loop(){
  getAttitude(&GY85, &att);
}
/****************** Implementation *********************/
void getAttitude(GY_85 *GY85, Attitude *att){
  double ax = GY85->accelerometer_x( GY85->readFromAccelerometer() ); // Acceleration in x direction
  double ay = GY85->accelerometer_y( GY85->readFromAccelerometer() ); // Acceleration in y direction
  double az = GY85->accelerometer_z( GY85->readFromAccelerometer() ); // Acceleration in z direction

  // Read gyroscope (rate of angular change) in the 3 axis
  double gx = GY85->gyro_x( GY85->readGyro() );
  double gy = GY85->gyro_y( GY85->readGyro() );
  double gz = GY85->gyro_z( GY85->readGyro() );
  
  // Set time interval and timer
  double interval = micros() - att->timer; // time interval = current time - previous time
  att->timer = micros(); // Set current time as previous time

  att->g_roll += gx * (interval/1000000);
  att->g_pitch += gy * (interval/1000000);

  att->a_roll = 90 - abs((atan2(az, ax) * 180/PI));        // Angle according to Accelerometer  (added the last element to make sure that it ended in zero degrees)
  att->a_pitch = -(90 - abs((atan2(az, ay) * 180/PI)));

  // Complementary filter: combine gyrox (roll angle according to gyro) and roll (roll angle according to accelerometer)
  att->roll = (att->a_roll + att->weight * att->g_roll) / (1 + att->weight);
  att->pitch = (att->a_pitch + att->weight * att->g_pitch) / (1 + att->weight);
  att->pitch_v = gy;
  att->roll_v = gx;

  Serial.print("acce_pitch = ");
  Serial.print(att->a_pitch);
  Serial.print(", gyro_pitch = ");
  Serial.print(att->g_pitch);
  Serial.print(", filter_pitch = ");
  Serial.print(att->pitch);
  Serial.print(", acce_roll = ");
  Serial.print(att->a_roll);
  Serial.print(", gyro_roll = ");
  Serial.print(att->g_roll);
  Serial.print(", filter_roll = ");
  Serial.println(att->roll);
  
  //delay(50);
}

