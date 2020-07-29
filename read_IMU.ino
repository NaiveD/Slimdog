#include "GY_85.h"
#include <Wire.h>
 
GY_85 GY85;     //create the object
    int weight = 30;
    double interval;
    double timer = 0;
   
    double roll = 0;
    double filterroll = 0;
    double gyrox = 0;
    double debug = 0;
 
void setup()
{
    Wire.begin();
    delay(10);
    Serial.begin(9600);
    delay(10);
    GY85.init();
    delay(10);
 
}
 
void loop()
{
    double ax = GY85.accelerometer_x( GY85.readFromAccelerometer() );
    double ay = GY85.accelerometer_y( GY85.readFromAccelerometer() );
    double az = GY85.accelerometer_z( GY85.readFromAccelerometer() );
   
//    int cx = GY85.compass_x( GY85.readFromCompass() );
//    int cy = GY85.compass_y( GY85.readFromCompass() );
//    int cz = GY85.compass_z( GY85.readFromCompass() );
 
    float gx = GY85.gyro_x( GY85.readGyro() );
    float gy = GY85.gyro_y( GY85.readGyro() );
    float gz = GY85.gyro_z( GY85.readGyro() );
    float gt = GY85.temp  ( GY85.readGyro() );
 
    interval = micros() - timer;            //TIMING
    timer = micros();

//    Serial.print("interval = ");
//    Serial.print(interval);
//    Serial.print(", ");
//
//    Serial.print("gyrox1 = ");
//    Serial.print(gyrox);
//    Serial.print(", ");

    // interval is around 81000 (microsecond) = 81000/1000 (millisecond) = 81000/1000000 (second)
    debug = gx*(interval/1000000);             // delta angle (debug) = angular rate(gx) * time interval(interval)  (in degree)
    gyrox += debug;                            // Angle according to gyro
 
    roll = (atan2(-ax, az) * 180/PI) -2.90f;     // Angle according to Accelerometer  (added the last element to make sure that it ended in zero degrees)
 
    filterroll += debug;
    filterroll = (roll + weight* filterroll) / (1 + weight);  // Filtered angle

//    Serial.print("gx = ");
//    Serial.print(gx);
//    Serial.print(", ");
//
//    Serial.print("debug = ");
//    Serial.print(debug);
//
//    Serial.print(", gyrox2 = ");
//    Serial.println(gyrox);

    //Serial.print  ( filterroll ); // roll using complementary filter 
    //Serial.print  ( " , " );
    //Serial.print  ( gyrox ); // 
//    Serial.print  ( " , " );
//    Serial.print  ( debug ); //
//    Serial.print  ( " , " );
//    Serial.print  ( gx ); // 
//    Serial.print  ( " , " );
//    Serial.println  ( roll ); // roll by accelerometer  
    
    delay(50);
}
