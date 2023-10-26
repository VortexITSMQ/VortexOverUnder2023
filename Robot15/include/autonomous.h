#include <iostream>
#include "constants.h"
#include "robot-config.h"

using namespace vex;
extern brain Brain;

//------- Aux function definition -------//

//--------- Main auton functions ---------//
void auton()
{
  Drivetrain.setDriveVelocity(80, percent);

  DrivetrainInertial.calibrate();
  task::sleep(2000);

  Drivetrain.driveFor(reverse, 30, distanceUnits::cm);
  Drivetrain.turnToHeading(45, rotationUnits::deg);
  Drivetrain.driveFor(fwd, 45, distanceUnits::cm);
  Drivetrain.driveFor(reverse, 45, distanceUnits::cm);
  Drivetrain.turnToHeading(0, rotationUnits::deg);
  Drivetrain.driveFor(fwd, 30, distanceUnits::cm);
  Drivetrain.turnToHeading(-78, rotationUnits::deg);
  Drivetrain.driveFor(fwd, 86, distanceUnits::cm);

  /*
  // Reinicia el sensor inercial
  DrivetrainInertial.resetRotation();
  //inertial_reset(DrivetrainInertial);

  // Espera un momento para que el sensor se estabilice
  task::sleep(1000);

  Brain.Screen.print(DrivetrainInertial.heading());
  Drivetrain.driveFor(reverse, 59.50, distanceUnits::in);

  Drivetrain.setDriveVelocity(20, percent);
  //Drivetrain.turnToHeading(90, rotationUnits::deg);

  // Gira el robot hasta que el sensor inercial alcance aproximadamente 90 grados
  while (fabs(DrivetrainInertial.heading() - 45.0) > 2.0) {
    Drivetrain.setTurnVelocity(10, percent);
    Drivetrain.turn(left); // Ajusta la dirección de giro según tus necesidades
  
    task::sleep(20); // Pequeña pausa para evitar que gire demasiado rápido
  }

  Drivetrain.driveFor(reverse, 3.50, distanceUnits::in);
  */

  /*
  // Detén el giro
  Drivetrain.stop();
  task::sleep(1000); 

  while (fabs(DrivetrainInertial.heading() - 180.0) > 2.0) {
    Drivetrain.setTurnVelocity(10, percent);
    Drivetrain.turn(left); // Ajusta la dirección de giro según tus necesidades
    task::sleep(20); // Pequeña pausa para evitar que gire demasiado rápido
  }*/

  Drivetrain.stop();

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