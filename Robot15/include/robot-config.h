using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern smartdrive Drivetrain;

// Chassis
extern motor RightDriveA;
extern motor RightDriveB;
extern motor LeftDriveA;
extern motor LeftDriveB;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern inertial DrivetrainInertial;

// Collector
 extern pneumatics IndexerRight;
 extern pneumatics IndexerLeft;

// Climber
extern motor BaseMotor;
extern motor ArmMotor;

// Driver Control Function
extern int rc_auto_loop_function_Controller1();
void  vexcodeInit( void );
void  chassis_control();