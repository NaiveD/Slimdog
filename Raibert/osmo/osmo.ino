#include "GY_85.h"
#include <Wire.h> // Used for I2C
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685
#include "IK.hpp"
#include "IMU.hpp"

#define DOG_LENGTH 406
#define DOG_WIDTH 280
#define CLAMP(x, low, high) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))
/****************** Declaration *********************/
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
GY_85 GY85;
float angle[16];
Attitude att;
double kp, kv;
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
  att.getInterval_resetTimer();;
  att.getAttitude(&GY85);
  Vec3 dynamic_IK_RF = freezeRF(Vec3(DOG_LENGTH/2, DOG_WIDTH/2, 0),
                                Vec3(-20,-40,-420),
                                att.pitch, att.roll, 0.0);
  set_leg(angle, dynamic_IK_RF, 0);
  move_motor(angle, &pwm);
  delay(100);
}
