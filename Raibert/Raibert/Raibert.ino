#include "GY_85.h" // IMU
#include <Wire.h> // Used for I2C (IMU and PCA9685)
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685

// The pwm object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
GY_85 GY85; // create the IMU object

// Handle time
long intervals[] = {50, 400, 400}; // Time intervals
long last[] = {0, 5500, 5700}; // Previous time 

//long intervals[] = {50, 4000, 4000}; // Time intervals
//long last[] = {0, 1500, 3500}; // Previous time 

// ================== Variables for IMU =====================
double interval; // time interval
double timer = 0; // Previous time

int weight = 20; // weight of complementary filter
double gyro_roll = 0; // Roll angle calculated by gyroscope
double acce_roll = 0; // Roll angle calculated by accelerometer
double filter_roll = 0; // Roll angle after filtering
double delta_angle = 0; // Delta angle used to calculate gyro_roll

double gyro_pitch = 0; // Roll angle calculated by gyroscope
double acce_pitch = 0; // Roll angle calculated by accelerometer
double filter_pitch = 0; // Roll angle after filtering
double delta_angle2 = 0; // Delta angle used to calculate gyro_pitch
// ==========================================================

// ================== Functions for IMU =====================
double read_roll();
double read_pitch();
// ==========================================================

// Servo number
//     G   Y   O   /
// RF: 0,  1,  2,  3
// RB: 4,  5,  6,  7
// LF: 8,  9,  10, 11
// LB: 12, 13, 14, 15

// =================== Variables for IK =====================
// The angles for the 12 servo motors
float angle0, angle1, angle2, angle4, angle5, angle6, angle8, angle9, angle10, angle12, angle13, angle14;
float x, y, z; // End point P(x, y, z)
float xrf, yrf, zrf, xrb, yrb, zrb, xlf, ylf, zlf, xlb, ylb, zlb;
/* ============= Constants ============== */
// lengths (mm)
float H = 266.0747;
float coxa = 22.42;
float femur = 34.9;
float deltax = 6.26;
float deltas = 19.0;
float l1 = 266;
float l2 = 261;
float l2p = 223.85;
float l2pp = 37.15;
float l3 = 278;
float l4 = 12.45;

// angles (degree)
float theta0 = 44.4674;
float theta1 = 43.4193;
/* ====================================== */
// ==========================================================

// =================== Functions for IK =====================
// Inverse Kiematics (IK) functions
float servo1_solver(float x, float y, float z, int leg); // Yellow Servo
float servo2_solver(float x, float y, float z, int leg, float servo1_angle); // Orange Servo
float servo3_solver(float x, float y, float z, int leg); // Green Servo

// Set the leg to position (x, y, z)
float set_leg(float x, float y, float z, int leg);

// Move all the 12 motors according to the calculated angles
void move_motor();

// Helper functions
int angletoPWM(int ang);
// ==========================================================

/* ===================== Parameters ======================= */
float x0 = 59.191540329180185; // x0: the lifted height of the legs 
float x1 = 0.4406489868843162;  // x1: gain kp for controlling pitch (Orange motors)
float x2 = -0.9997712503653102;  // x2: gain kv for controlling pitch (Orange motors)
float x3 = -0.39533485473632046;  // x3: gain kp for controlling roll (Yellow motors)
float x4 = -0.7064882183657739;  // x4: gain kv for controlling roll (Yellow motors)
// int x5 = 0; // x5: The forward distance of the legs during flight phase

int height = x0;  
int angleO1; // angle of the Orange motors of RF/LB during stance
int angleY1; // angle of the Yellow motors of RF/LB during stance
int angleO2; // angle of the Orange motors of LF/RB during stance
int angleY2; // angle of the Yellow motors of LF/RB during stance
// int forwardDistance = x5; 

double objective_function = 0;
double sum_roll = 0;
double sum_pitch = 0;
double counter = 0;
int time_limit = 30000; // Run for 30s
/* ======================================================== */

// Main body
void setup() {
  Wire.begin(); // For I2C
  delay(10);
  
  Serial.begin(9600); // For serial data transmission
  Serial.println("16 channel servo test!");
  delay(10);

  GY85.init(); // For IMU
  delay(10);
  
  pwm.begin(); // For PWM
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates

  // Set initial position
  Serial.println("Begin setting initial position...");
  // x = 0, y = 0, z = -420;
  xrf = 80, yrf = -40, zrf = -410;
  xrb = -40, yrb = -20, zrb = -400;
  xlf = 80, ylf = 35, zlf = -400;
  xlb = -50, ylb = 0, zlb = -400;
  
  set_leg(xrf, yrf, zrf, 0); // Right Front
  set_leg(xlf, ylf, zlf, 1); // Left Front
  set_leg(xlb, ylb, zlb, 2); // Left Back
  set_leg(xrb, yrb, zrb, 3); // Right Back  
  move_motor();

  delay(5000);
  Serial.println("Begin testing...");
}

// Trotting gait loop
void loop() {
  long now = millis(); // Get current time
  if (now <= time_limit)
  {
    // Read IMU data
    if (now - last[0] >= intervals[0])
    {
      last[0] = now;

      interval = micros() - timer;
      timer = micros();
      
      // Read roll and pitch from IMU
      filter_roll = read_roll();
      filter_pitch = read_pitch();
      // Serial.print("pitch = ");
      // Serial.print(filter_pitch);
      // Serial.print(", roll = ");
      // Serial.println(filter_roll);
    }

    // Trotting Phase 1
    // Phase 1 (180 ms)
    // RF/LB during flight, LF/RB during stance
    // LF/RB should lower, RF/LB should lift
    // LF/RB should rotate the Orange and Yellow motors to adjust the body attitude
    if (now - last[1] >= intervals[1])
    {
  //    Serial.print("In phase1: now = ");
  //    Serial.print(now);
  //    Serial.print(", last[1] = ");
  //    Serial.print(last[1]);
  //    Serial.print(", now - last[1] = ");
  //    Serial.println(now - last[1]);
      
      last[1] = now;

      // Lower LF/RB
      set_leg(xlf, ylf, zlf, 1); // Left Front
      set_leg(xrb, yrb, zrb, 3); // Right Back
      // Orange Motors
      pwm.setPWM(6, 0, angletoPWM(angle6, 6)); // RB
      pwm.setPWM(10, 0, angletoPWM(angle10, 10)); // LF
      // Green Motors
      pwm.setPWM(4, 0, angletoPWM(angle4, 4)); // RB
      pwm.setPWM(8, 0, angletoPWM(angle8, 8)); // LF  

      // Lift RF/LB
      set_leg(xrf, yrf, zrf + height, 0); // Right Front
      set_leg(xlb, ylb, zlb + height, 2); // Left Back
      // Orange Motors
      pwm.setPWM(2, 0, angletoPWM(angle2, 2)); // RF
      pwm.setPWM(14, 0, angletoPWM(angle14, 14)); // LB
      // Green Motors
      pwm.setPWM(0, 0, angletoPWM(angle0, 0)); // RF
      pwm.setPWM(12, 0, angletoPWM(angle12, 12)); // LB
      // Yellow Motors
      pwm.setPWM(1, 0, angletoPWM(angle1, 1)); // RF
      pwm.setPWM(13, 0, angletoPWM(angle13, 13)); // LB

      // Adjust body attitude with LF/RB 
      // Need to use IMU data here
      Serial.print("In phase1: ");
      Serial.print("pitch = ");
      Serial.print(filter_pitch);
      Serial.print(", roll = ");
      Serial.println(filter_roll);

      float roll_velocity = GY85.gyro_y( GY85.readGyro() ); // Roll: gyro_y
      float pitch_velocity = GY85.gyro_x( GY85.readGyro() ); // Pitch: gyro_x

      angleY2 = -x3 * (filter_roll - 0) - x4 * (roll_velocity);
      angleO2 = -x1 * (filter_pitch - 0) - x2 * (pitch_velocity);

      Serial.print("Adjust Body Attitude: Yellow motor: ");
      Serial.print(angleY2);
      Serial.print(", Orange motor: ");
      Serial.print(angleO2);

      if (angleY2 > 20)
        angleY2 = 20;
      if (angleY2 < -20)
        angleY2 = -20;
      if (angleO2 > 20)
        angleO2 = 20;
      if (angleO2 < -20)
        angleO2 = -20;

      // Rotate Yellow motors
      pwm.setPWM(5, 0, angletoPWM(angle5-angleY2, 5)); // RB
      pwm.setPWM(9, 0, angletoPWM(angle9+angleY2, 9)); // LF;
      // Rotate Orange motors
      pwm.setPWM(6, 0, angletoPWM(angle6+angleO2, 6)); // RB
      pwm.setPWM(10, 0, angletoPWM(angle10-angleO2, 10)); // LF;
    }

    // Trotting Phase 2
    // Phase 2 (180 ms)
    // RF/LB during stance, LF/RB during flight
    // RF/LB should lower, LF/RB should lift
    // RF/LB should rotate the Orange and Yellow motors to adjust the body attitude   
    if (now - last[2] >= intervals[2])
    {
  //    Serial.print("In phase2: now = ");
  //    Serial.print(now);
  //    Serial.print(", last[2] = ");
  //    Serial.print(last[2]);
  //    Serial.print(", now - last[2] = ");
  //    Serial.println(now - last[2]);
      last[2] = now; 

      // Lower RF/LB
      set_leg(xrf, yrf, zrf, 0); // Right Front
      set_leg(xlb, ylb, zlb, 2); // Left Back
      // Orange Motors
      pwm.setPWM(2, 0, angletoPWM(angle2, 2)); // RF
      pwm.setPWM(14, 0, angletoPWM(angle14, 14)); // LB
      // Green Motors
      pwm.setPWM(0, 0, angletoPWM(angle0, 0)); // RF
      pwm.setPWM(12, 0, angletoPWM(angle12, 12)); // LB

      // Lift LF/RB
      set_leg(xlf, ylf, zlf + height, 1); // Left Front
      set_leg(xrb, yrb, zrb + height, 3); // Right Back
      // Orange Motors
      pwm.setPWM(6, 0, angletoPWM(angle6, 6)); // RB
      pwm.setPWM(10, 0, angletoPWM(angle10, 10)); // LF
      // Green Motors
      pwm.setPWM(4, 0, angletoPWM(angle4, 4)); // RB
      pwm.setPWM(8, 0, angletoPWM(angle8, 8)); // LF
      // Yellow Motors
      pwm.setPWM(5, 0, angletoPWM(angle5, 5)); // RB
      pwm.setPWM(9, 0, angletoPWM(angle9, 9)); // LF

      // Adjust body attitude with LF/RB 
      // Need to use IMU data here
      Serial.print("In phase2: ");
      Serial.print("pitch = ");
      Serial.print(filter_pitch);
      Serial.print(", roll = ");
      Serial.println(filter_roll);

      float roll_velocity = GY85.gyro_y( GY85.readGyro() ); // Roll: gyro_y
      float pitch_velocity = GY85.gyro_x( GY85.readGyro() ); // Pitch: gyro_x

      angleY1 = - (-x3 * (filter_roll - 0) - x4 * (roll_velocity) );
      angleO1 = - (-x1 * (filter_pitch - 0) - x2 * (pitch_velocity) );

      Serial.print("Adjust Body Attitude: Yellow motor: ");
      Serial.print(angleY1);
      Serial.print(", Orange motor: ");
      Serial.print(angleO1);
      
      if (angleY1 > 20)
        angleY1 = 20;
      if (angleY1 < -20)
        angleY1 = -20;
      if (angleO1 > 20)
        angleO1 = 20;
      if (angleO1 < -20)
        angleO1 = -20;

      // Rotate Yellow motors
      pwm.setPWM(1, 0, angletoPWM(angle1+angleY1, 1)); // RF
      pwm.setPWM(13, 0, angletoPWM(angle13-angleY1, 13)); // LB
      // Rotate Orange motors
      pwm.setPWM(2, 0, angletoPWM(angle2+angleO1, 2)); // RF
      pwm.setPWM(14, 0, angletoPWM(angle14-angleO1, 14)); // LB;

      sum_roll += abs(filter_roll);
      sum_pitch += abs(filter_pitch);
      counter += 1;
      objective_function = 100 - 4 * (0.5 * sum_roll/counter + 0.5 * sum_pitch/counter);

      Serial.print("objective_function = ");
      Serial.println(objective_function);
    }
  }
  else
  {
    Serial.print("objective_function = ");
    Serial.println(objective_function);
    delay(1000000);
  }
}


/* ================ IK functions ================ */
// the yellow servo
// Parameters: (x, y, z) - 3d coordinate;
//             leg: 0 for right leg, 1 for left leg.
float servo1_solver(float x, float y, float z, int leg) {
  float servo1_angle;
  float gamma1, gamma2;
  float OyPyz;
  
  if (y == 0)
    OyPyz = abs(z);
  else
    OyPyz = pow(y*y+z*z, 0.5);

  gamma1 = acos(-z/OyPyz) * 180/PI;
  gamma2 = acos(deltas/OyPyz) * 180/PI;
  
  if (leg == 0) { // right leg
    if (y >= 0)
       servo1_angle = gamma1 + gamma2;
    else if (y < 0)
       servo1_angle = gamma2 - gamma1;
    // Range of the yellow servos on the right legs (50 - 130 degrees)
    if (servo1_angle > 130)
      servo1_angle = 130;
    else if (servo1_angle < 50)
      servo1_angle = 50;
  }
  else if (leg == 1) { // left leg
    if (y >= 0)
       servo1_angle = 180 - (gamma2 - gamma1);
    else if (y < 0)
       servo1_angle = 180 - (gamma1 + gamma2);
    // Range of the yellow servos on the left legs (50 - 130 degrees)
    if (servo1_angle > 130)
      servo1_angle = 130;
    else if (servo1_angle < 50)
      servo1_angle = 50;
  }
  
  return servo1_angle;
}

// the orange servo
// Parameters: (x, y, z) - 3d coordinate;
//             leg: 0 for right leg, 1 for left leg.
//             servo1_angle: angle of the yellow servo
float servo2_solver(float x, float y, float z, int leg, float servo1_angle) {
  float servo2_angle;
  float alpha, beta;
  float OP, x2d, y2d;
  
  float Zmo = deltas * cos(servo1_angle);

  // Convert 3d coordinate (x, y, z) to new 2d coordinate (x2d, y2d)
  x2d = x;
  if (z >= Zmo)
    y2d = pow(y*y+z*z-deltas*deltas, 0.5);
  else  
    y2d = -pow(y*y+z*z-deltas*deltas, 0.5);
  
  OP = pow((x2d*x2d + y2d*y2d), 0.5);

  if (H+l2 <= OP)
    alpha = 0;
  else
    alpha = acos((H*H+OP*OP-l2*l2)/(2*H*OP)) * 180/PI; // degree
  beta = acos(x/OP) * 180/PI; //degree

  if (leg == 0) {// right leg
    if (y2d >= 0)
      servo2_angle = 180 - (alpha-beta);
    else
      servo2_angle = 180 - (alpha+beta);

    // Range of the orange servos on the right legs (0 - 180 degrees)
    if (servo2_angle > 140)
      servo2_angle = 140;
    else if (servo2_angle < 40)
      servo2_angle = 40;
  }
  else if (leg == 1) { // left leg
    if (y2d >= 0)
      servo2_angle = alpha - beta;
    else
      servo2_angle = alpha + beta;

    // Range of the orange servos on the left legs (0 - 180 degrees)
    if (servo2_angle > 140)
      servo2_angle = 140;
    else if (servo2_angle < 40)
      servo2_angle = 40;
  }

  return servo2_angle;
}

// the green servo
// Parameters: (x, y, z) - 3d coordinate;
//             leg: 0 for right leg, 1 for left leg.
float servo3_solver(float x, float y, float z, int leg) {
  float servo3_angle;
  float alphaG1p, alphaG2p, epsilon, angdelta, thetaB1, thetaB2, thetaB;
  float H1, H2, H3, OP;

  H1 = pow((l2pp*l2pp+l4*l4), 0.5);
  OP = pow((x*x + y*y + z*z - deltas*deltas), 0.5);

  thetaB1 = atan2(l4, l2pp) * 180/PI; // degree
  if (H+l2 >= OP)
    thetaB = acos((H*H + l2*l2 - OP*OP)/(2*H*l2)) * 180/PI; // degree
  else
    thetaB = 180;
    
  thetaB2 = thetaB - thetaB1; // degree
  H2 = pow((H1*H1 + H*H - 2*H1*H * cos(thetaB2 * PI/180)), 0.5); // radian
  
  angdelta = acos((H*H + H2*H2 - H1*H1)/(2*H*H2)) * 180/PI; // degree
  
  epsilon = 180 - theta1 - angdelta; // degree
  H3 = pow((coxa*coxa + H2*H2 - 2*coxa*H2 * cos(epsilon * PI/180)), 0.5); // radian

  if (coxa + H3 < H2)
    alphaG1p = 180;
  else
    alphaG1p = acos((coxa*coxa + H3*H3 - H2*H2)/(2*coxa*H3)) * 180/PI; // degree
  
  if (femur + l3 < H3)
    alphaG2p = 180;
  else 
    alphaG2p = acos((femur*femur + H3*H3 - l3*l3)/(2*femur*H3)) * 180/PI;  //degree

  servo3_angle = 180 - (alphaG1p + alphaG2p); //degree 
  
  if (leg == 0) { // right leg 
    servo3_angle = servo3_angle + theta0;
    // Range of the green servos on the right legs (40 - 170 degrees)
    if (servo3_angle > 160)
      servo3_angle = 160;
    else if (servo3_angle < 20)
      servo3_angle = 20;
  } 
  else if (leg == 1) { // left leg
    servo3_angle = 180 - (servo3_angle + theta0);
    // Range of the green servos on the left legs (10 - 140 degrees)
    if (servo3_angle > 160)
      servo3_angle = 160;
    else if (servo3_angle < 20)
      servo3_angle = 20;
  }
  
  return servo3_angle;
}

/* ================================================ */

/* ================================================ */
/* Given the end point (X, Y, Z) and the LEG number,  
 * set the angles of the servo motors.
   LEG: 0 - Right Front
        1 - Left Front
        2 - Left Back
        3 - Right Back                   */
float set_leg(float x, float y, float z, int leg) {
  if (leg == 0) { // Right Front
    // Green motor
    angle0 = servo3_solver(x, y, z, 0);

    // Yellow motor
    angle1 = servo1_solver(x, y, z, 0);
    angle1 = 180 - angle1;

    // Orange motor
    angle2 = servo2_solver(x, y, z, 0, angle1);
    
    return;
  }

  else if (leg == 1) { // Left Front
    // Green motor
    angle8 = servo3_solver(x, y, z, 1);

    // Yellow motor
    angle9 = servo1_solver(x, y, z, 1);
    angle9 = 180 - angle9;

    // Orange motor
    angle10 = servo2_solver(x, y, z, 1, angle9);

    return;
  }

  else if (leg == 2) { // Left Back
    // Green motor
    angle12 = servo3_solver(x, y, z, 1);

    // Yellow motor
    angle13 = servo1_solver(x, y, z, 1);

    // Orange motor
    angle14 = servo2_solver(x, y, z, 1, angle13);

    return;
  }

  else if (leg == 3) { // Right Back
    // Green motor
    angle4 = servo3_solver(x, y, z, 0);

    // Yellow motor
    angle5 = servo1_solver(x, y, z, 0);

    // Orange motor
    angle6 = servo2_solver(x, y, z, 0, angle5);

    return;
  }
}

// Move all the 12 motors according to the calculated angles
void move_motor() {
  
//  Serial.print("angle0 = ");
//  Serial.print(angle0);
//  Serial.print(", angle1 = ");
//  Serial.print(angle1);
//  Serial.print(", angle2 = ");
//  Serial.print(angle2);
//  Serial.print(", angle4 = ");
//  Serial.print(angle4);
//  Serial.print(", angle5 = ");
//  Serial.print(angle5);
//  Serial.print(", angle6 = ");
//  Serial.print(angle6);
//  Serial.print(", angle8 = ");
//  Serial.print(angle8);
//  Serial.print(", angle9 = ");
//  Serial.print(angle9);
//  Serial.print(", angle10 = ");
//  Serial.print(angle10);
//  Serial.print(", angle12 = ");
//  Serial.print(angle12);
//  Serial.print(", angle13 = ");
//  Serial.print(angle13);
//  Serial.print(", angle14 = ");
//  Serial.println(angle14);
  
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

/* ================================================ */

/* ================ IMU functions ================ */
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
/* ================================================ */
