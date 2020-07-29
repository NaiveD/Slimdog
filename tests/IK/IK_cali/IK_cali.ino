#include <Wire.h> // Used for I2C (IMU and PCA9685)
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685

// Might need to define SERVOMIN and SERVOMAX for each of the 12 servos
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

// Inverse Kiematics (IK) functions
float servo1_solver(float x, float y, float z, int leg); // Yellow Servo
float servo2_solver(float x, float y, float z, int leg, float servo1_angle); // Orange Servo
float servo3_solver(float x, float y, float z, int leg); // Green Servo

// Set the leg to position (x, y, z)
float set_leg(float x, float y, float z, int leg);

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

  float x, y, z; // End point P(x, y, z)  
  float angle1_r, angle2_r, angle3_r, angle1_l, angle2_l, angle3_l; // angles of the 3 motors for right and left legs

  // Given an end point (x, y, z)
  // Test (0, 0, -500) and (0, 0, -400) for each of the 4 legs
  x = -50, y = 0, z = -450;

  set_leg(x, y, z, 0); // Right Front
  set_leg(x, y, z, 1); // Left Front
  set_leg(x, y, z, 2); // Left Back
  set_leg(x, y, z, 3); // Right Back
}

void loop() {
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

//  Serial.print("Zmo = ");
//  Serial.print(Zmo);
//  Serial.print(", y2d = ");
//  Serial.print(y2d);
//  Serial.print(", OP = ");
//  Serial.print(OP);
//  Serial.print(", alpha = ");
//  Serial.print(alpha);
//  Serial.print(", beta = ");
//  Serial.println(beta);
  
  if (leg == 0) {// right leg
    if (y2d >= 0)
      servo2_angle = 180 - (alpha-beta);
    else
      servo2_angle = 180 - (alpha+beta);

    // Range of the orange servos on the right legs (0 - 180 degrees)
    if (servo2_angle > 170)
      servo2_angle = 170;
    else if (servo2_angle < 10)
      servo2_angle = 10;
  }
  else if (leg == 1) { // left leg
    if (y2d >= 0)
      servo2_angle = alpha - beta;
    else
      servo2_angle = alpha + beta;

    // Range of the orange servos on the left legs (0 - 180 degrees)
    if (servo2_angle > 170)
      servo2_angle = 170;
    else if (servo2_angle < 10)
      servo2_angle = 10;
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

/* Set the LEG leg to position (X, Y, Z) 
   LEG: 0 - Right Front
        1 - Left Front
        2 - Left Back
        3 - Right Back                   */
float set_leg(float x, float y, float z, int leg) {
  float angle1, angle2, angle3; // angles of the 3 motors for both right and left legs
  
  if (leg == 0) { // Right Front   
    angle1 = servo1_solver(x, y, z, 0); // Yellow
    angle2 = servo2_solver(x, y, z, 0, angle1); // Orange
    angle3 = servo3_solver(x, y, z, 0); // Green

    pwm.setPWM(0+1, 0, angletoPWM(180-angle1, 0+1)); // Yellow
    pwm.setPWM(0+2, 0, angletoPWM(angle2, 0+2)); // Orange
    pwm.setPWM(0, 0, angletoPWM(angle3, 0)); // Green

    Serial.print("RF: angle1 = ");
    Serial.print(180-angle1);
    Serial.print(", angle2 = ");
    Serial.print(angle2);
    Serial.print(", angle3 = ");
    Serial.println(angle3);

  }

  else if (leg == 1) { // Left Front
    angle1 = servo1_solver(x, y, z, 1); // Yellow
    angle2 = servo2_solver(x, y, z, 1, angle1); // Orange
    angle3 = servo3_solver(x, y, z, 1); // Green

    pwm.setPWM(8+1, 0, angletoPWM(180-angle1, 8+1)); // Yellow
    pwm.setPWM(8+2, 0, angletoPWM(angle2, 8+2)); // Orange
    pwm.setPWM(8, 0, angletoPWM(angle3, 8)); // Green

    Serial.print("LF: angle1 = ");
    Serial.print(180-angle1);
    Serial.print(", angle2 = ");
    Serial.print(angle2);
    Serial.print(", angle3 = ");
    Serial.println(angle3);
  }

  else if (leg == 2) { // Left Back
    angle1 = servo1_solver(x, y, z, 1); // Yellow
    angle2 = servo2_solver(x, y, z, 1, angle1); // Orange
    angle3 = servo3_solver(x, y, z, 1); // Green

    pwm.setPWM(12+1, 0, angletoPWM(angle1, 12+1)); // Yellow
    pwm.setPWM(12+2, 0, angletoPWM(angle2, 12+2)); // Orange
    pwm.setPWM(12, 0, angletoPWM(angle3, 12)); // Green

    Serial.print("LB: angle1 = ");
    Serial.print(angle1);
    Serial.print(", angle2 = ");
    Serial.print(angle2);
    Serial.print(", angle3 = ");
    Serial.println(angle3);
  }

  else if (leg == 3) { // Right Back
    angle1 = servo1_solver(x, y, z, 0); // Yellow
    angle2 = servo2_solver(x, y, z, 0, angle1); // Orange
    angle3 = servo3_solver(x, y, z, 0); // Green

    pwm.setPWM(4+1, 0, angletoPWM(angle1, 4+1)); // Yellow
    pwm.setPWM(4+2, 0, angletoPWM(angle2, 4+2)); // Orange
    pwm.setPWM(4, 0, angletoPWM(angle3, 4)); // Green

    Serial.print("RB: angle1 = ");
    Serial.print(angle1);
    Serial.print(", angle2 = ");
    Serial.print(angle2);
    Serial.print(", angle3 = ");
    Serial.println(angle3);
  }
}

/* ================================================ */

// Convert angle to PWM
int angletoPWM(int ang, int servonum) {
  int pulse;
  
  if (servonum == 0)
    pulse = map(ang, 0, 180, 160, 640); // map the angle into the PWM

  else if (servonum == 1)
    pulse = map(ang, 0, 180, 110, 630); // map the angle into the PWM

  else if (servonum == 2)
    pulse = map(ang, 0, 180, 130, 640); // map the angle into the PWM

  else if (servonum == 4)
    pulse = map(ang, 0, 180, 155, 655); // map the angle into the PWM

  else if (servonum == 5)
    pulse = map(ang, 0, 180, 120, 650); // map the angle into the PWM

  else if (servonum == 6)
    pulse = map(ang, 0, 180, 130, 650); // map the angle into the PWM

  else if (servonum == 8)
    pulse = map(ang, 0, 180, 145, 635); // map the angle into the PWM

  else if (servonum == 9)
    pulse = map(ang, 0, 180, 155, 675); // map the angle into the PWM

  else if (servonum == 10)
    pulse = map(ang, 0, 180, 140, 640); // map the angle into the PWM

  else if (servonum == 12)
    pulse = map(ang, 0, 180, 145, 645); // map the angle into the PWM

  else if (servonum == 13)
    pulse = map(ang, 0, 180, 125, 625); // map the angle into the PWM

  else if (servonum == 14)
    pulse = map(ang, 0, 180, 125, 635); // map the angle into the PWM

  else
    pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map the angle into the PWM
       
  return pulse;
}
