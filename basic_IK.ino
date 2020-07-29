#include <Wire.h> // Used for I2C
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685

#define SERVOMIN 110 // minimum pulse length count
#define SERVOMAX 620 // maximum  pulse length count

// The pwm object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo number
//     G   Y   O   /
// RF: 0,  1,  2,  3
// RB: 4,  5,  6,  7
// LF: 8,  9,  10, 11
// LB: 12, 13, 14, 15
uint8_t servonum;

// IK functions
float servo1_solver(float x, float y, float z, int leg);
float servo2_solver(float x, float y, float z, int leg, float servo1_angle);
float servo3_solver(float x, float y, float z, int leg);

// Helper functions
int angletoPWM(int ang);

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

void setup() {
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission
  Serial.println("16 channel servo test!");
  
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates
}

void loop() {
  float x, y, z; // End point P(x, y, z)  
  float angle1_r, angle2_r, angle3_r, angle1_l, angle2_l, angle3_l; // angles of the 3 motors for right and left legs

  // Given an end point (x, y, z)
  x = -30, y = 0, z = -500;
  
  // Right Front
  int xf = 30;
  angle1_r = servo1_solver(xf, y, z, 0); // Yellow
  angle2_r = servo2_solver(xf, y, z, 0, angle1_r); //Orange
  angle3_r = servo3_solver(xf, y, z, 0); // Green

  pwm.setPWM(0+1, 0, angletoPWM(angle1_r)); // Yellow
  pwm.setPWM(0+2, 0, angletoPWM(angle2_r)); // Orange
  pwm.setPWM(0, 0, angletoPWM(angle3_r)); // Green

  // Right Back
  angle1_r = servo1_solver(x, y+80, z, 0); // Yellow
  angle2_r = servo2_solver(x, y+80, z, 0, angle1_r); //Orange
  angle3_r = servo3_solver(x, y+80, z, 0); // Green

  pwm.setPWM(4+1, 0, angletoPWM(angle1_r)); // Yellow
  pwm.setPWM(4+2, 0, angletoPWM(angle2_r)); // Orange
  pwm.setPWM(4, 0, angletoPWM(angle3_r)); // Green

  // Left Front
  angle1_l = servo1_solver(xf-50, y+160, z+50, 1); // Yellow
  angle2_l = servo2_solver(xf-50, y+160, z+50, 1, angle1_r); //Orange
  angle3_l = servo3_solver(xf-50, y+160, z+50, 1); // Green

  pwm.setPWM(8+1, 0, angletoPWM(angle1_l)); // Yellow
  pwm.setPWM(8+2, 0, angletoPWM(angle2_l)); // Orange
  pwm.setPWM(8, 0, angletoPWM(angle3_l)); // Green

  // Left Back
  angle1_l = servo1_solver(x, y+50, z+30, 1); // Yellow
  angle2_l = servo2_solver(x, y+50, z+30, 1, angle1_r); //Orange
  angle3_l = servo3_solver(x, y+50, z+30, 1); // Green

  pwm.setPWM(12+1, 0, angletoPWM(angle1_l)); // Yellow
  pwm.setPWM(12+2, 0, angletoPWM(angle2_l)); // Orange
  pwm.setPWM(12, 0, angletoPWM(angle3_l)); // Green
}


/* ================ IK functions ================ */
// the yellow servo
// Parameters: (x, y, z) - 3d coordinate;
//             leg: 0 for right leg, 1 for left leg.
float servo1_solver(float x, float y, float z, int leg) {
  float servo1_angle;
  float gamma1, gamma2;
  float OPyz;
  
  OPyz = pow(y*y+z*z, 0.5);
  if (y == 0)
    OPyz = abs(z);

  gamma1 = acos(-z/OPyz) *180/PI;
  gamma2 = acos(deltas/OPyz) *180/PI;
  
  if (leg == 0) { // right leg
    if (y >= 0)
       servo1_angle = gamma1 + gamma2;
    else if (y < 0)
       servo1_angle = gamma2 - gamma1;
    // Range of the yellow servos on the right legs (0 - 180 degrees)
    if (servo1_angle > 180)
      servo1_angle = 180;
    else if (servo1_angle < 0)
      servo1_angle = 0;
  }
  else if (leg == 1) { // left leg
    if (y >= 0)
       servo1_angle = 180 - (gamma2 - gamma1);
    else if (y < 0)
       servo1_angle = 180 - (gamma1 + gamma2);
    // Range of the yellow servos on the left legs (0 - 180 degrees)
    if (servo1_angle > 180)
      servo1_angle = 180;
    else if (servo1_angle < 0)
      servo1_angle = 0;
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
 
  alpha = acos((H*H+OP*OP-l2*l2)/(2*H*OP)) * 180/PI; // degree
  beta = acos(x/OP) * 180/PI; //degree

  if (leg == 0) {// right leg
    if (y2d >= 0)
      servo2_angle = 180 - (alpha-beta);
    else
      servo2_angle = 180 - (alpha+beta);

    // Range of the orange servos on the right legs (0 - 180 degrees)
    if (servo2_angle > 180)
      servo2_angle = 180;
    else if (servo2_angle < 0)
      servo2_angle = 0;
  }
  else if (leg == 1) { // left leg
    if (y2d >= 0)
      servo2_angle = alpha - beta;
    else
      servo2_angle = alpha + beta;

    // Range of the orange servos on the left legs (0 - 180 degrees)
    if (servo2_angle > 180)
      servo2_angle = 180;
    else if (servo2_angle < 0)
      servo2_angle = 0;
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
  thetaB = acos((H*H + l2*l2 - OP*OP)/(2*H*l2)) * 180/PI; // degree
    
  thetaB2 = thetaB - thetaB1; // degree
  H2 = pow((H1*H1 + H*H - 2*H1*H * cos(thetaB2 * PI/180)), 0.5); // radian
  
  angdelta = acos((H*H + H2*H2 - H1*H1)/(2*H*H2)) * 180/PI; // degree
  
  epsilon = 180 - theta1 - angdelta; // degree
  H3 = pow((coxa*coxa + H2*H2 - 2*coxa*H2 * cos(epsilon * PI/180)), 0.5); // radian

  alphaG1p = acos((coxa*coxa + H3*H3 - H2*H2)/(2*coxa*H3)) * 180/PI; // degree
  alphaG2p = acos((femur*femur + H3*H3 - l3*l3)/(2*femur*H3)) * 180/PI;  //degree
  
  servo3_angle = 180 - (alphaG1p + alphaG2p); //degree 
  
  if (leg == 0) { // right leg 
    servo3_angle = servo3_angle + theta0;
    // Range of the green servos on the right legs (40 - 170 degrees)
    if (servo3_angle > 170)
      servo3_angle = 170;
    else if (servo3_angle < 40)
      servo3_angle = 40;
  } 
  else if (leg == 1) { // left leg
    servo3_angle = 180 - (servo3_angle + theta0);
    // Range of the green servos on the left legs (10 - 140 degrees)
    if (servo3_angle > 140)
      servo3_angle = 140;
    else if (servo3_angle < 10)
      servo3_angle = 10;
  }
  
  return servo3_angle;
}

/* ================================================ */

// Convert angle to PWM
int angletoPWM(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map the angle into the PWM
  return pulse;
}
