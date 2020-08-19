void setup() {
  // put your setup code here, to run once:
    int x0_F;
    int x0_B;

    int y0_R;
    int y0_L;

    int z0;

    int xf; // decides how Far to prepare the foot
    int zh; // decides how High to lift the foot
    int t_phase;    // decides how long between each phases

    int retract = 2;    // [1, inf], decide the extent of retracting foot
    int x_last;
    int y_last;     // the end of one step
}

void loop() {
  // put your main code here, to run repeatedly:
    // Phase 1: prepare RF
    set_leg(x0_F + xp, y0_R, z0, 0);
    set_leg(x0_F - xp, )
}