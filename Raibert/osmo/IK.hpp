#include <Wire.h> // Used for I2C
#include <Adafruit_PWMServoDriver.h> // Used for the PCA9685
#define CLAMP(x, low, high) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

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
/* ============== Declaration ============== */

float servo1_solver(float x, float y, float z, int leg);
float servo2_solver(float x, float y, float z, int leg, float servo1_angle);
float servo3_solver(float x, float y, float z, int leg);
void set_leg(float *angle, float x, float y, float z, int leg);
void move_motor(float *angle, Adafruit_PWMServoDriver *pwm);
int angletoPWM(float ang, int servonum);



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
void set_leg(float *angle, float x, float y, float z, int leg) {
  if (leg == 0) { // Right Front
    // Green motor
    angle[0] = servo3_solver(x, y, z, 0);

    // Yellow motor
    angle[1] = servo1_solver(x, y, z, 0);
    angle[1] = 180 - angle[1];

    // Orange motor
    angle[2] = servo2_solver(x, y, z, 0, angle[1]);
    
    return;
  }

  else if (leg == 1) { // Left Front
    // Green motor
    angle[8] = servo3_solver(x, y, z, 1);

    // Yellow motor
    angle[9] = servo1_solver(x, y, z, 1);
    angle[9] = 180 - angle[9];

    // Orange motor
    angle[10] = servo2_solver(x, y, z, 1, angle[9]);

    return;
  }

  else if (leg == 2) { // Left Back
    // Green motor
    angle[12] = servo3_solver(x, y, z, 1);

    // Yellow motor
    angle[13] = servo1_solver(x, y, z, 1);

    // Orange motor
    angle[14] = servo2_solver(x, y, z, 1, angle[13]);

    return;
  }

  else if (leg == 3) { // Right Back
    // Green motor
    angle[4] = servo3_solver(x, y, z, 0);

    // Yellow motor
    angle[5] = servo1_solver(x, y, z, 0);

    // Orange motor
    angle[6] = servo2_solver(x, y, z, 0, angle[5]);

    return;
  }
  return;
}

// Move all the 12 motors according to the calculated angles
void move_motor(float *angle, Adafruit_PWMServoDriver *pwm) {
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
  pwm->setPWM(1, 0, angletoPWM(angle[1], 1)); // RF
  pwm->setPWM(5, 0, angletoPWM(angle[5], 5)); // RB
  pwm->setPWM(9, 0, angletoPWM(angle[9], 9)); // LF
  pwm->setPWM(13, 0, angletoPWM(angle[13], 13)); // LB

  // Move the Orange motors (2, 6, 10, 14)
  pwm->setPWM(2, 0, angletoPWM(angle[2], 2)); // RF
  pwm->setPWM(6, 0, angletoPWM(angle[6], 6)); // RB
  pwm->setPWM(10, 0, angletoPWM(angle[10], 10)); // LF
  pwm->setPWM(14, 0, angletoPWM(angle[14], 14)); // LB

  // Move the Green motors (0, 4, 8, 12)
  pwm->setPWM(0, 0, angletoPWM(angle[0], 0)); // RF
  pwm->setPWM(4, 0, angletoPWM(angle[4], 4)); // RB
  pwm->setPWM(8, 0, angletoPWM(angle[8], 8)); // LF
  pwm->setPWM(12, 0, angletoPWM(angle[12], 12)); // LB
}

/* ================================================ */

// Convert angle to PWM
int angletoPWM(float ang, int servonum) {
  int pulse;
  
  if (servonum == 0)
    pulse = (int)map(ang, 0, 180, 135, 675); // map the angle into the PWM

  else if (servonum == 1)
    pulse = (int)map(ang, 0, 180, 110, 680); // map the angle into the PWM

  else if (servonum == 2)
    pulse = (int)map(ang, 0, 180, 180, 660); // map the angle into the PWM

  else if (servonum == 4)
    pulse = (int)map(ang, 0, 180, 130, 670); // map the angle into the PWM

  else if (servonum == 5)
    pulse = (int)map(ang, 0, 180, 95, 565); // map the angle into the PWM

  else if (servonum == 6)
    pulse = (int)map(ang, 0, 180, 84, 636); // map the angle into the PWM

  else if (servonum == 8)
    pulse = (int)map(ang, 0, 180, 80, 680); // map the angle into the PWM

  else if (servonum == 9)
    pulse = (int)map(ang, 0, 180, 325, 805); // map the angle into the PWM

  else if (servonum == 10)
    pulse = (int)map(ang, 0, 180, 150, 630); // map the angle into the PWM

  else if (servonum == 12)
    pulse = (int)map(ang, 0, 180, 135, 655); // map the angle into the PWM

  else if (servonum == 13)
    pulse = (int)map(ang, 0, 180, -50, 510); // map the angle into the PWM

  else if (servonum == 14)
    pulse = (int)map(ang, 0, 180, 120, 640); // map the angle into the PWM
    
  return pulse;
}