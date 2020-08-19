///////////////////////// INITIALIZATION ////////////////////////////
int x0_F;
int x0_B;

int y0_R;
int y0_L;

int z0;

int xf; // decides how Far to prepare the foot
int zh; // decides how High to lift the foot
int t_phase;    // decides how long between each phases

float retract = 0.5;    // (0, 1), decide the extent of retracting foot
                        // the closer between it with 1, the weaker the retraction is
int x_last = -xf;
int y_last = 0;     // the end of one step

int kp_x, kp_y, kv_x, kv_y;
double phi_x, phi_y, phid_x, phid_y, angv_x, angv_y;
double xp, yp;
////////////////////////////////////////////////////////////////////
void setup() {

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
    // Phase 1: prepare RF
    set_leg(x0_F + xf, y0_R, z0, 0);
    set_leg(x0_F + x_last, y0_L + y_last, z0, 1);
    set_leg(x0_B + xf, y0_L, z0, 2);
    set_leg(x0_B + x_last, y0_R + y_last, z0, 3);
    // t1 <= time
    move_motor();


    // Get information from IMU
    phi_x;
    phi_y;
    angv_x;
    angv_y;

    // Calculate landing point
    xp = kp_x * (phi_x - phid_x) + kv_x * (angv_x);
    yp = kp_y * (phi_y - phid_y) + kv_y * (angv_y);

    // Phase 2: landing RF
    set_leg(x0_F + xp, y0_R + yp, z0 - zh, 0);
    set_leg(x0_F, y0_L, z0 + zh, 1);
    set_leg(x0_B + xp, y0_L + yp, z0 - zh, 2);
    set_leg(x0_B, y0_R, z0 - zh, 3);
    // t2 <= time
    // make sure t2 - t1 = t_phase
    move_motor();

    // Calculate where to retract foot
    x_last = (xp - (1-retract)*xf) / retract;
    y_last = (yp - (1-retract)*xf) / retract;

    // Phase 3: retract RF
    set_leg(x0_F + x_last, y0_R + y_last, z0, 0);
    set_leg(x0_F + xf, y0_L, z0, 1);
    set_leg(x0_B + x_last, y0_L + y_last, z0, 2);
    set_leg(x0_B + xf, y0_R, z0, 3);
    // t3 <= time
    move_motor();

    // Get information from IMU
    phi_x;
    phi_y;
    angv_x;
    angv_y;

    // Calculate landing point
    xp = kp_x * (phi_x - phid_x) + kv_x * (angv_x);
    yp = kp_y * (phi_y - phid_y) + kv_y * (angv_y);

    // Phase 4: lift RF
    set_leg(x0_F, y0_R, z0 + zh, 0);
    set_leg(x0_F + xp, y0_L + yp, z0 - zh, 1);
    set_leg(x0_B, y0_L, z0 + zh, 2);
    set_leg(x0_B + xp, y0_R + yp, z0 - zh, 3);
    // t4 <= time
    move_motor();

    // Calculate where to retract foot
    x_last = (xp - (1-retract)*xf) / retract;
    y_last = (yp - (1-retract)*xf) / retract;
    
}