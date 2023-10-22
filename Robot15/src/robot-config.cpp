#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

bool RecolectorIsActive = false;

//DERECHA
motor RightDriveA = motor(PORT1, ratio18_1, true);
motor RightDriveB = motor(PORT2, ratio18_1, true);

//IZQUIERDA
motor LeftDriveA = motor(PORT4, ratio18_1, false);
motor LeftDriveB = motor(PORT3, ratio18_1, false);

//MOTOR PARA CATAPULTA
motor catapult = motor(PORT15, ratio18_1, false);

//GRUPO DE MOTORES DE LA IZQUIERDA
motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);

//GRUPO DE MOTORES DE LA DERECHA
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);

//Drivetrain (COMPUESTO POR GRUPO DE LA DERECHA Y GRUPO IZQUIERDO)
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 295, 40, mm, 1);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// Set pneumatic indexer
pneumatics Indexer = pneumatics(Brain.ThreeWirePort.B);
pneumatics IndexerRight = pneumatics(Brain.ThreeWirePort.C);
pneumatics IndexerLeft = pneumatics(Brain.ThreeWirePort.D);
int cont = 0;

void R1callback(){
  printf("cont ${cont}");
  if (RecolectorIsActive){
    IndexerLeft.set(false);
    IndexerRight.set(false);
    RecolectorIsActive = false;
  }
  else{
    IndexerLeft.set(true);
    IndexerRight.set(true);
    RecolectorIsActive = true;
  }
}

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  Controller1.ButtonR1.pressed(R1callback);
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }

      // This is for the PISTON RECOLECTORS
      // check the ButtonR2 status to control indexer
      //if (Controller1.ButtonR1.pressing()) { Indexer.set(true); }
      //else { Indexer.set(false); }


      // This is for the CATAPULT
      // check the ButtonR2 status to control indexer
      if (Controller1.ButtonA.pressing()) { catapult.spin(forward); }
      else { catapult.stop(); }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}