using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;

// Chassis
extern motor RightDriveA;
extern motor RightDriveB;
extern motor LeftDriveA;
extern motor LeftDriveB;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern smartdrive Drivetrain;
extern inertial DrivetrainInertial;

// Driver Control Function
extern int rc_auto_loop_function_Controller1();
void  vexcodeInit( void );