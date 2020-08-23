#include "GY_85.h"
#include <Wire.h> // Used for I2C
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685

#define CLAMP(x, low, high) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))
/****************** Declaration *********************/
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
GY_85 GY85;
int angle[16];
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

  move_motor(angle);
  delay(2000);
}
/****************** Loop *********************/
void loop(){
  getAttitude(&GY85, &att);
  int diff_pitch = (int)(kp * att.pitch + kv * att.pitch_v);
  int diff_roll = (int)(kp * att.roll + kv * att.roll_v);

  // adjust pitch
  {
    angle[2] += diff_pitch;
    angle[6] += diff_pitch;
    angle[10] -= diff_pitch;
    angle[14] -= diff_pitch;
  }

  // adjust roll
  {
    angle[1] += diff_roll;
    angle[5] -= diff_roll;
    angle[9] += diff_roll;
    angle[13] -= diff_roll;
  }

  move_motor(angle);
  delay(250);
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

void move_motor(int *angle){
  // clamp the angle[]
  {
    angle[0] = CLAMP(angle[0], 30, 150);
    angle[1] = CLAMP(angle[1], 6, 144);
    angle[2] = CLAMP(angle[2], 9, 165);
    angle[4] = CLAMP(angle[4], 30, 150);
    angle[5] = CLAMP(angle[5], 6, 144);
    angle[6] = CLAMP(angle[6], 9, 165);
    angle[8] = CLAMP(angle[8], 18, 141);
    angle[9] = CLAMP(angle[9], 0, 133);
    angle[10] = CLAMP(angle[10], 0, 180);
    angle[12] = CLAMP(angle[12], 9, 147);
    angle[13] = CLAMP(angle[13], 68, 164);
    angle[14] = CLAMP(angle[14], 11, 180);
  }

  // Move the Yellow motors (1, 5, 9, 13)
  pwm.setPWM(1, 0, angletoPWM(angle[1], 1)); // RF
  pwm.setPWM(5, 0, angletoPWM(angle[5], 5)); // RB
  pwm.setPWM(9, 0, angletoPWM(angle[9], 9)); // LF
  pwm.setPWM(13, 0, angletoPWM(angle[13], 13)); // LB

  // Move the Orange motors (2, 6, 10, 14)
  pwm.setPWM(2, 0, angletoPWM(angle[2], 2)); // RF
  pwm.setPWM(6, 0, angletoPWM(angle[6], 6)); // RB
  pwm.setPWM(10, 0, angletoPWM(angle[10], 10)); // LF
  pwm.setPWM(14, 0, angletoPWM(angle[14], 14)); // LB

  // Move the Green motors (0, 4, 8, 12)
  pwm.setPWM(0, 0, angletoPWM(angle[0], 0)); // RF
  pwm.setPWM(4, 0, angletoPWM(angle[4], 4)); // RB
  pwm.setPWM(8, 0, angletoPWM(angle[8], 8)); // LF
  pwm.setPWM(12, 0, angletoPWM(angle[12], 12)); // LB
}
