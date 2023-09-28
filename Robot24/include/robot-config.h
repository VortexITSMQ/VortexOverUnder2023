using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;

// Motores derecha
extern motor RightDriveA;
extern motor RightDriveB;

// Motores izquierda
extern motor LeftDriveA;
extern motor LeftDriveB;

extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );