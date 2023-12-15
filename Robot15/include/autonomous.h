#include <iostream>
#include "constants.h"
#include "robot-config.h"
#include "vex_global.h"

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
  Drivetrain.setDriveVelocity(28, pct);
  
  //Primera ida
  Drivetrain.driveFor(fwd, 65, distanceUnits::cm);
  
  //Vuelta para empujar el trible
  Drivetrain.turnToHeading(-20, rotationUnits::deg, 110, rpm, true);
  IndexerLeft.set(true);
  Drivetrain.turnToHeading(-180, rotationUnits::deg, 100, rpm, true);
  IndexerLeft.set(false);

  //Ida al triable rojo
  Drivetrain.setDriveVelocity(28, pct);
  Drivetrain.driveFor(reverse, 60, distanceUnits::cm);

  //se acerca al trible rojo para agarrarlo
  Drivetrain.turnToHeading(-135, rotationUnits::deg, 100, rpm, true);
  Drivetrain.driveFor(reverse, 10, distanceUnits::cm);

  //Agarra el trible
  Climber.spin(reverse, 45, percent);
  wait(5.7, seconds);
  Climber.stop();

  //Saca el trible de su spot
  Drivetrain.driveFor(fwd, 30, distanceUnits::cm);

  //Giramos al direccion del gol
  Drivetrain.turnToHeading(-225, rotationUnits::deg, 100, rpm, true);

  //Levantamos el escalador para que no se atore con el gol
  Climber.spin(fwd, 50, percent);
  wait(3, seconds);
  Climber.stop();

  // Vuelta de 180 grados para golpear con alitas
  Drivetrain.turnToHeading(-45, rotationUnits::deg, 100, rpm, true);

  // Calibracion para no acumular error
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }

  // Abrir alitas
  IndexerLeft.set(true);
  IndexerRight.set(true);
  
  // Golpear triballs 
  Drivetrain.setDriveVelocity(35, pct);
  Drivetrain.driveFor(fwd, 38, distanceUnits::cm);
  IndexerLeft.set(false);
  IndexerRight.set(false);
  Drivetrain.setDriveVelocity(28, pct);

  // Regresar
  Drivetrain.driveFor(reverse, 50, distanceUnits::cm);

  // Dar vuelta hacia el pasillo
  Drivetrain.turnToHeading(50, rotationUnits::deg, 100, rpm, true);

  // Tocar poste
  Climber.stop(hold);
  Drivetrain.driveFor(reverse, 100, distanceUnits::cm);
}

void skills()
{
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  Drivetrain.setDriveVelocity(28, pct);
  
  //salida del pasillo
  Drivetrain.driveFor(fwd, 95, distanceUnits::cm);
  Drivetrain.turnToHeading(90, rotationUnits::deg, 100, rpm, true);

  // llegada  a red
  Drivetrain.driveFor(fwd, 45, distanceUnits::cm);

  // abrir alitas para atrapar triballs
  IndexerLeft.set(true);
  IndexerRight.set(true);
  wait(10, seconds);
  IndexerLeft.set(false);
  IndexerRight.set(false);

  // llegada al tubo
  Drivetrain.turnToHeading(180, rotationUnits::deg, 100, rpm, true);
  Drivetrain.driveFor(fwd, 50, distanceUnits::cm);
  Drivetrain.turnToHeading(90, rotationUnits::deg, 100, rpm, true);

  int i;
  for (i=0;i<4;i++){
    // vuelta a red
    Drivetrain.driveFor(fwd, 50, distanceUnits::cm);
    Drivetrain.turnToHeading(0, rotationUnits::deg, 100, rpm, true);
    IndexerLeft.set(true);
    IndexerRight.set(true);

    // golpe a la red
    Drivetrain.setDriveVelocity(60, pct);
    Drivetrain.driveFor(fwd, 50, distanceUnits::cm)
    Drivetrain.setDriveVelocity(28, pct);

    // regreso al tubo
    // IndexerLeft.set(false);
    // IndexerRight.set(false);
    Drivetrain.driveFor(reverse, 50, distanceUnits::cm);
    Drivetrain.turnToHeading(90, rotationUnits::deg, 100, rpm, true);
    Drivetrain.driveFor(reverse, 50, distanceUnits::cm);

    //esperar triballs
    wait(8, seconds);
  }

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
