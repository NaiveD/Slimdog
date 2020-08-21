#include "GY_85.h"
#include <Wire.h> // Used for I2C
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685

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

}
void getAttitude(GY_85 *GY85, Attitude *att);




void getAttitude(GY_85 *GY85, Attitude *att){
  double ax = GY85->accelerometer_x( GY85->readFromAccelerometer() ); // Acceleration in x direction
  double ay = GY85->accelerometer_y( GY85->readFromAccelerometer() ); // Acceleration in y direction
  double az = GY85->accelerometer_z( GY85->readFromAccelerometer() ); // Acceleration in z direction

  // Read gyroscope (rate of angular change) in the 3 axis
  float gx = GY85->gyro_x( GY85->readGyro() );
  float gy = GY85->gyro_y( GY85->readGyro() );
  float gz = GY85->gyro_z( GY85->readGyro() );
  
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
  
//   Serial.print("acce_pitch = ");
//   Serial.print(acce_pitch);
//   Serial.print(", gyro_pitch = ");
//   Serial.print(gyro_pitch);
//   Serial.print(", filter_pitch = ");
//   Serial.print(filter_pitch);
//   Serial.print(", acce_roll = ");
//   Serial.print(acce_roll);
//   Serial.print(", gyro_roll = ");
//   Serial.print(gyro_roll);
//   Serial.print(", filter_roll = ");
//   Serial.println(filter_roll);
  
  delay(50);
}