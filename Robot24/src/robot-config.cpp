#include "vex.h"
#include "constants.h"


using namespace vex;
using signature = vision::signature;
using code = vision::code;

//---------------------- Devices ----------------------//
brain  Brain;
controller Controller1 = controller(primary);

// Chassis
inertial DrivetrainInertial = inertial(PORT13);
motor RightDriveA = motor(PORT1, ratio18_1, true);
motor RightDriveB = motor(PORT2, ratio18_1, true);
motor LeftDriveA  = motor(PORT3, ratio18_1, false);
motor LeftDriveB  = motor(PORT4, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 
  WHEEL_TRAVEL, TRACK_WIDTH, TRACK_BASE, mm, EXT_GEAR_RATIO);

// VEXcode generated functions
// Enable/Disable controller
bool RemoteControlCodeEnabled = true;

// Stop with controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
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

    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

//task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);

void auton_func() {
  Drivetrain.setDriveVelocity(80, pct);
  /*Drivetrain.driveFor(reverse, 20, distanceUnits::cm);
  Drivetrain.turnFor(right, 45, degrees);
  Drivetrain.driveFor(forward, 43.01, distanceUnits::cm);
  Drivetrain.driveFor(reverse, 63.01, distanceUnits::cm);
  Drivetrain.turnFor(left, 45, degrees);
  Drivetrain.driveFor(forward, 50.73, distanceUnits::cm);
  Drivetrain.turnFor(left, 90, degrees);*/
  Drivetrain.driveFor(forward, 10, distanceUnits::cm);
  Brain.Screen.print("Hello, VEX!");
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // Nothing to initialize
}