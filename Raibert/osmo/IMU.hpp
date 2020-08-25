#include "GY_85.h"
#include <Wire.h> // Used for I2C

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
    double interval = 0;
    int weight = 30;
    Attitude(){};

    void getInterval_resetTimer();
    // this should be called before getAttitude()

    void getAttitude(GY_85 *GY85);

};

void Attitude::getInterval_resetTimer(){
    interval = micros() - timer;
    timer = micros();
    return;
}

void Attitude::getAttitude(GY_85 *GY85){
  double ax = GY85->accelerometer_x( GY85->readFromAccelerometer() ); // Acceleration in x direction
  double ay = GY85->accelerometer_y( GY85->readFromAccelerometer() ); // Acceleration in y direction
  double az = GY85->accelerometer_z( GY85->readFromAccelerometer() ); // Acceleration in z direction

  // Read gyroscope (rate of angular change) in the 3 axis
  double gx = GY85->gyro_x( GY85->readGyro() );
  double gy = GY85->gyro_y( GY85->readGyro() );
  double gz = GY85->gyro_z( GY85->readGyro() );
  
  // Set time interval and timer
//   double interval = micros() - att->timer; // time interval = current time - previous time
//   att->timer = micros(); // Set current time as previous time

  g_roll += gx * (interval/1000000);
  g_pitch += gy * (interval/1000000);

  a_roll = 90 - abs((atan2(az, ax) * 180/PI));        // Angle according to Accelerometer  (added the last element to make sure that it ended in zero degrees)
  a_pitch = -(90 - abs((atan2(az, ay) * 180/PI)));

  // Complementary filter: combine gyrox (roll angle according to gyro) and roll (roll angle according to accelerometer)
  roll = (a_roll + weight * g_roll) / (1 + weight);
  pitch = (a_pitch + weight * g_pitch) / (1 + weight);
  pitch_v = gy;
  roll_v = gx;

  Serial.print("acce_pitch = ");
  Serial.print(a_pitch);
  Serial.print(", gyro_pitch = ");
  Serial.print(g_pitch);
  Serial.print(", filter_pitch = ");
  Serial.print(pitch);
  Serial.print(", acce_roll = ");
  Serial.print(a_roll);
  Serial.print(", gyro_roll = ");
  Serial.print(g_roll);
  Serial.print(", filter_roll = ");
  Serial.println(roll);
}