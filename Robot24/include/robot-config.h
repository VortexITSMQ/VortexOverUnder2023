using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;

// Right motors
extern motor RightDriveA;
extern motor RightDriveB;

// Left motors
extern motor LeftDriveA;
extern motor LeftDriveB;

// Motors Group
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

// Wings
extern pneumatics IndexerRight;
extern pneumatics IndexerLeft;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );