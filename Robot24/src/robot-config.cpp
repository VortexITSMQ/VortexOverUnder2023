#include "vex.h"
#include "constants.h"


using namespace vex;
using signature = vision::signature;
using code = vision::code;

// Global varible that checks if the wings are open
 bool WingAreOpen = false;
 bool RailActive = false;

//---------------------- Devices ----------------------//
brain  Brain;
controller Controller1 = controller(primary);
// Catapult
limit CatapultSwitch = limit(Brain.ThreeWirePort.A);
motor CatapultLeft = motor(PORT10, ratio36_1, false);
motor CatapultRight = motor(PORT20, ratio36_1, false);
motor_group Catapult = motor_group(CatapultLeft, CatapultRight);
// Recolector
motor LeftRail = motor(PORT11, ratio18_1, false);
motor RightRail = motor(PORT11, ratio18_1, true);
motor_group Rail = motor_group(LeftRail, RightRail);
motor Collector = motor(PORT11, ratio18_1, true);
// Wings
motor Wing = motor(PORT10, ratio18_1, true);
// Chassis
inertial DrivetrainInertial = inertial(PORT12);
motor RightDriveA = motor(PORT2, ratio18_1, true);
motor RightDriveB = motor(PORT9, ratio18_1, true);
motor LeftDriveA  = motor(PORT11, ratio18_1, false);
motor LeftDriveB  = motor(PORT19, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 
  WHEEL_TRAVEL, TRACK_WIDTH, TRACK_BASE, mm, EXT_GEAR_RATIO);


//---------------------- User control ----------------------//
bool RemoteControlCodeEnabled = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

void Wings_cb(){
  //If the wings are open then we close them
  if (!WingAreOpen) {
    Wing.spinToPosition(100, degrees, true);
    WingAreOpen = true;
  }
  //If the wings are close then we open them
  else {
    Wing.spinToPosition(-100, degrees, true);
    WingAreOpen = false;
  }
}

void Rail_cb(){
  while(Controller1.ButtonA.pressing() && !RailActive)
    Rail.spin(fwd);
  while(Controller1.ButtonA.pressing() && RailActive)
    Rail.spin(reverse);
  RailActive = !RailActive;
  Rail.stop();
}

void Collector_cb(){
  while(Controller1.ButtonB.pressing())
    Collector.spin(fwd);
  Collector.stop(hold);
}

void CatapultSwitch_cb(){
  Catapult.stop(hold);
}

void ReleaseCatapult_cb(){
  Catapult.spin(fwd, 5, rpm);
}

int rc_auto_loop_function_Controller1() {
  Controller1.ButtonR1.pressed(Wings_cb);
  Controller1.ButtonA.pressed(Rail_cb);
  Controller1.ButtonB.pressed(Collector_cb);
  Controller1.ButtonX.pressed(ReleaseCatapult_cb);
  CatapultSwitch.pressed(CatapultSwitch_cb);
  Catapult.spin(fwd, 5, rpm);
  while(true) {
    chassis_control();
  }
    
  wait(20, msec);
  return 0;
}

void vexcodeInit( void ) {
  wait(200, msec);
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  wait(50, msec);
}

void chassis_control(){
  int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
  int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
  if (drivetrainLeftSideSpeed < JOYSTICK_DEADBAND && drivetrainLeftSideSpeed > -JOYSTICK_DEADBAND) {
    if (DrivetrainLNeedsToBeStopped_Controller1) {
      LeftDriveSmart.stop();
      DrivetrainLNeedsToBeStopped_Controller1 = false;
    }
  } else {
    DrivetrainLNeedsToBeStopped_Controller1 = true;
  }
  if (drivetrainRightSideSpeed < JOYSTICK_DEADBAND && drivetrainRightSideSpeed > -JOYSTICK_DEADBAND) {
    if (DrivetrainRNeedsToBeStopped_Controller1) {
      RightDriveSmart.stop();
      DrivetrainRNeedsToBeStopped_Controller1 = false;
    }
  } else {
    DrivetrainRNeedsToBeStopped_Controller1 = true;
  }
  
  if (DrivetrainLNeedsToBeStopped_Controller1) {
    LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
    LeftDriveSmart.spin(forward);
  }
  if (DrivetrainRNeedsToBeStopped_Controller1) {
    RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
    RightDriveSmart.spin(forward);
  }
}
