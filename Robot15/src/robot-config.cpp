#include "vex.h"
#include "constants.h"


using namespace vex;
using signature = vision::signature;
using code = vision::code;

// Global varible that checks if the wings are open
 bool WingAreOpen = false;
 bool BaseMotorActive = false;
 bool ArmMotorActive = false;

//---------------------- Devices ----------------------//
brain  Brain;
controller Controller1 = controller(primary);
// Collector
pneumatics IndexerRight = pneumatics(Brain.ThreeWirePort.A);
pneumatics IndexerLeft = pneumatics(Brain.ThreeWirePort.B);
// Climber
motor BaseMotor = motor(PORT5, ratio6_1, true);
motor ArmMotor = motor(PORT6, ratio6_1, true);
// Chassis
inertial DrivetrainInertial = inertial(PORT11);
motor RightDriveA = motor(PORT1, ratio18_1, true);
motor RightDriveB = motor(PORT2, ratio18_1, true);
motor LeftDriveA  = motor(PORT3, ratio18_1, false);
motor LeftDriveB  = motor(PORT4, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 
  WHEEL_TRAVEL, TRACK_WIDTH, TRACK_BASE, mm, EXT_GEAR_RATIO);


//---------------------- User control ----------------------//
bool RemoteControlCodeEnabled = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

void Collector_cb(){
    //If the wings are open then we close them
    if (WingAreOpen) {
        IndexerRight.set(false);
        IndexerLeft.set(false);
        WingAreOpen = false;
    }
    //If the wings are close then we open them
    else {
        IndexerRight.set(true);
        IndexerLeft.set(true);
        WingAreOpen = true;
  }
}

void BaseMotor_cb(){
  while(Controller1.ButtonA.pressing() && !BaseMotorActive)
    BaseMotor.spin(fwd, 180, rpm);
  while(Controller1.ButtonA.pressing() && BaseMotorActive)
    BaseMotor.spin(reverse, 180, rpm);
  BaseMotorActive = !BaseMotorActive;
  BaseMotor.stop(hold);
}

void ArmMotor_cb(){
  while(Controller1.ButtonB.pressing() && !ArmMotorActive){
    ArmMotor.spin(fwd, 180, rpm);
  }
  while(Controller1.ButtonB.pressing() && ArmMotorActive){
    ArmMotor.spin(reverse, 180, rpm);
  }
  ArmMotorActive = !ArmMotorActive;
  ArmMotor.stop(hold);
}

int rc_auto_loop_function_Controller1() {
  Controller1.ButtonR1.pressed(Collector_cb);
  Controller1.ButtonA.pressed(BaseMotor_cb);
  Controller1.ButtonB.pressed(ArmMotor_cb);
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
  BaseMotor.resetPosition();
  ArmMotor.resetPosition();
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