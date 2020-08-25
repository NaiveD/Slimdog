#include <math.h>

class Vec3{
public:
    double x;
    double y;
    double z;
    // Constructor
    Vec3():x(0.0),y(0.0),z(0.0){}
    Vec3(double x, double y, double z):x(x),y(y),z(z){}
    // Arithmetic
    double norm();
    Vec3 normalized();
    double dot(const Vec3);
    Vec3 cross(const Vec3);
    Vec3 operator+(const Vec3);
    Vec3 operator-(const Vec3);
    Vec3 operator-();
    void operator=(const Vec3);
    Vec3 operator*(double);
};

double find_angle(double cos_alpha, double zp);
Vec3 rotateVec(Vec3 OP, double theta_x, double theta_y, double theta_z);
// theta_x := radius rotating along x-axis
// theta_x > 0 when -y => +z => +y
// theta_y > 0 when -x => +z => +x
// theta_z > 0 when +y => +x => -y
Vec3 freezeRF(Vec3 init_O_RF, Vec3 init_IK_RF, double cur_pitch, double cur_roll, double cur_yaw);
// freezeRF() returns the appropriate IK(in vec3) for RF to freeze observed on CoM(point O)
// init_O_RF and init_IK_RF are both in IK system, angles are raw IMU outputs
// Note that pitch, roll and yaw are degrees rather than radians

/*************************** Implementation ****************/
double find_angle(double cos_alpha, double zp){
    if(zp!=0.0){
        return zp > 0.0 ? acos(cos_alpha) : -acos(cos_alpha);
    }
    else{
        return acos(cos_alpha);
    }
}

Vec3 rotateVec(Vec3 OP, double theta_x, double theta_y, double theta_z){
    // rotate along x-axis
    double cos_alpha_r = Vec3(0.0,-1.0,0.0).dot(Vec3(0.0,OP.y,OP.z).normalized());
    double alpha_r = find_angle(cos_alpha_r, OP.z);
    Vec3 OP_x;  // the result after rotating along x-axis
    OP_x = Vec3(OP.x, 0.0, 0.0) + Vec3(0.0, cos(alpha_r+theta_x), sin(alpha_r+theta_x)) * Vec3(0.0, OP.y, OP.z).norm();

    // rotate along y_axis
    double cos_alpha_p = Vec3(-1.0,0.0,0.0) .dot(Vec3(OP_x.x, 0.0, OP_x.z).normalized());
    double alpha_p = find_angle(cos_alpha_p, OP_x.z);
    Vec3 OP_xy;
    OP_xy = Vec3(0.0, OP_x.y, 0.0) + Vec3(cos(alpha_p+theta_y), 0.0, sin(alpha_p+theta_y)) * Vec3(OP_x.x, 0.0, OP_x.z).norm();

    // rotate along z_axis
    double cos_alpha_y = Vec3(0.0,1.0,0.0).dot(Vec3(OP_xy.x, OP_xy.y, 0.0).normalized());
    double alpha_y = find_angle(cos_alpha_y, OP_xy.x);
    Vec3 OP_xyz;
    OP_xyz = Vec3(0.0, 0.0, OP_xy.z) + Vec3(sin(alpha_y+theta_z), cos(alpha_y+theta_z), 0.0) * Vec3(OP_xy.x, OP_xy.y, 0.0).norm();
}

Vec3 freezeRF(Vec3 init_O_RF, Vec3 init_IK_RF, double cur_pitch, double cur_roll, double cur_yaw){
    Vec3 O_RFfoot = init_O_RF + init_IK_RF; // we should maintain this
    double pitch = cur_pitch * PI / 180.0;
    double roll = -cur_roll * PI / 180.0;   // these two are adjusted for IK coordinate system
    // waiting to handle yaw
    double yaw = 0.0; // should be cur_yaw - init_yaw; positive when +y => +x => -y
    Vec3 rot_O_RF;
    rot_O_RF = rotateVec(init_O_RF, roll, pitch, yaw);
    return rotateVec(O_RFfoot - rot_O_RF, -roll, -pitch, -yaw); // the new RF->RFfoot in rotated system(IK for RF)
}

double Vec3::norm(){
    return sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::normalized(){
    return Vec3(x/norm(), y/norm(), z/norm());
}

double Vec3::dot(const Vec3 b){
    return x*b.x + y*b.y + z*b.z;
}

Vec3 Vec3::cross(const Vec3 b){
    return Vec3(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);
}

Vec3 Vec3::operator+(const Vec3 b){
    return Vec3(x+b.x, y+b.y, z+b.z);
}

Vec3 Vec3::operator-(const Vec3 b){
    return Vec3(x-b.x, y-b.y, z-b.z);
}

Vec3 Vec3::operator-(){
    return Vec3(-x, -y, -z);
}

void Vec3::operator=(const Vec3 b){
    x = b.x;
    y = b.y;
    z = b.z;
    return;
}

Vec3 Vec3::operator*(double b){
    return Vec3(x*b, y*b, z*b);
}