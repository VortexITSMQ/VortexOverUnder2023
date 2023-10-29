#include <iostream>
#include "constants.h"
#include "robot-config.h"

using namespace vex;
extern brain Brain;

//------- Aux function definition -------//
void inertial_turn(double desired_angle){
  // Calibrar el sensor inercial
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    // Esperar hasta que la calibración se complete
  }

  while (fabs(DrivetrainInertial.heading() - desired_angle) > 2.0) {
    Drivetrain.setTurnVelocity(20, percent);
    Drivetrain.turn(left);
  }
}

//--------- Main auton functions ---------//
void auton()
{
  DrivetrainInertial.calibrate();
  //Drivetrain.setDriveVelocity(80, pct);
  //Complete route of ROBOT 24
  //DrivetrainInertial.calibrate();S
  Drivetrain.driveFor(reverse, 123, distanceUnits::cm);
  //inertial_turn(45);S
  Drivetrain.turnToHeading(43, rotationUnits::deg);
  Climber.spin(reverse, 60, percent);
  wait(4, seconds);
  Climber.stop();
  Drivetrain.driveFor(fwd, 20, distanceUnits::cm);
  Drivetrain.turnToHeading(-55, rotationUnits::deg);
  Climber.spin(fwd, 60, percent);
  wait(2, seconds);
  Climber.stop();
  Drivetrain.driveFor(reverse, 45, distanceUnits::cm);
  // Drivetrain.turnToHeading(-90, rotationUnits::deg);

}

void skills()
{
}

void move_to_coordinate(double target_x, double target_y, double target_heading)
{

  if (target_x == 0 && target_y != 0)
  {
    Drivetrain.driveFor(fwd, target_y, distanceUnits::cm);
  }
  if (target_y == 0 && target_x != 0)
  {
    double ang = 90;
    if (target_x > 0)
    {
      Drivetrain.turnToHeading(ang, rotationUnits::deg);
    }
    if (target_x < 0)
    {
      Drivetrain.turnToHeading(-ang, rotationUnits::deg);
    }
    Drivetrain.driveFor(fwd, target_x, distanceUnits::cm);
  }
  if (target_x != 0 && target_y != 0)
  {
    double ang = atan(target_y / target_x) * 180 / M_PI;
    double hyp = sqrt(target_x * target_x + target_y * target_y);
    // 1st quadrant
    if (target_x > 0 && target_y > 0)
    {
      Drivetrain.turnToHeading(ang, rotationUnits::deg);
    }
    // 2nd quadrant
    if (target_x < 0 && target_y > 0)
    {
      Drivetrain.turnToHeading(-ang, rotationUnits::deg);
    }
    // 3rd quadrant
    if (target_x < 0 && target_y < 0)
    {
      Drivetrain.turnToHeading(180 - ang, rotationUnits::deg);
    }
    // 4th quadrant
    if (target_x > 0 && target_y < 0)
    {
      Drivetrain.turnToHeading(180 + ang, rotationUnits::deg);
    }
    Drivetrain.driveFor(hyp, distanceUnits::cm);
  }
  DrivetrainInertial.resetHeading();
  if (target_heading != 0)
  {
    Drivetrain.turnToHeading(target_heading, rotationUnits::deg);
  }
  Drivetrain.stop(brakeType::hold);
}
