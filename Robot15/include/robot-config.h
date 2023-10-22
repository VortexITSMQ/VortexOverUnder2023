using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
//Derecha
extern motor RightDriveA;
extern motor RightDriveB;

//Izquierda
extern motor LeftDriveA;
extern motor LeftDriveB;

extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

//Catapulta
extern motor catapult;

//Recolector 15(alitas)
extern pneumatics Indexer;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );