#include <iostream>
#include "constants.h"
#include "robot-config.h"

using namespace vex;
extern brain Brain;


//--------- Main auton functions ---------//
void auton()
{
  //Complete route of ROBOT 24
  //Drivetrain.setDriveVelocity(45, pct);
  
  //DESCOMENTAR CUANDO JALE LOS ENGRANES
  //CatapultSwitch.pressed(CatapultSwitch_cb);
  //Catapult.spin(fwd);
  
  //Ida a triball
  Drivetrain.driveFor(reverse, 35, distanceUnits::cm);
  Drivetrain.turnToHeading(45, rotationUnits::deg);
  Drivetrain.driveFor(fwd, 46, distanceUnits::cm);

  //Recoger el triball
  CollectorFront.spin(fwd);
  CollectorBack.spin(fwd, 80, percent);
  Rail.spin(reverse);
  wait(3.5, seconds);

  Rail.stop(hold);

  Rail.spin(fwd, 90, percent);
  wait(.6, seconds);
  Rail.stop(hold);

  //IDA AL TUBO NEGRO
  Drivetrain.driveFor(reverse, 68, distanceUnits::cm);
  Drivetrain.turnToHeading(90, rotationUnits::deg);
  Drivetrain.driveFor(reverse, 60, distanceUnits::cm);
  CollectorBack.stop();
  CollectorFront.stop();

  Drivetrain.setDriveVelocity(10, pct);

  //LANZA EL TRIBALL
  //Catapult.spin(fwd, 40, rpm);

  wait(6, seconds);

  //SE HACE PARA ATRAS PARA QUE EL RECOLECTOR TOQUE EL TUBO
  Drivetrain.driveFor(fwd, 20, distanceUnits::cm);
  Drivetrain.turnToHeading(-70., rotationUnits::deg);
  //Drivetrain.driveFor(fwd, 5, distanceUnits::cm);
  Rail.spin(reverse);
  wait(4, seconds);
  Rail.stop(hold);
  Drivetrain.driveFor(fwd, 10, distanceUnits::cm);




}

void skills()
{
  //Complete route of ROBOT 24
  //Drivetrain.setDriveVelocity(45, pct);
  
  //DESCOMENTAR CUANDO JALE LOS ENGRANES
  CatapultSwitch.pressed(CatapultSwitch_cb);
  Catapult.spin(fwd);
  
  //Ida a triball
  Drivetrain.driveFor(reverse, 38, distanceUnits::cm);
  Drivetrain.turnToHeading(45, rotationUnits::deg);
  Drivetrain.driveFor(fwd, 46.5, distanceUnits::cm);


  for(int i =0; i<10;i++){
    //Recoger el triball
    CollectorFront.spin(fwd);
    CollectorBack.spin(fwd, 80, percent);
    Rail.spin(reverse);
    wait(3.5, seconds);

    Rail.stop(hold);

    Rail.spin(fwd, 90, percent);
    wait(.6, seconds);
    Rail.stop(hold);

    CollectorBack.stop();
    CollectorFront.stop();

    // int first_angle =  Drivetrain.heading();
    Drivetrain.driveFor(reverse, 38, distanceUnits::cm);
    Catapult.spin(fwd);
    wait(3, sec);

    Drivetrain.driveFor(fwd, 38.5, distanceUnits::cm);

  }
  //---------------------------










  
  /*
  //Complete route of ROBOT 24
  Drivetrain.setDriveVelocity(45, pct);
  
  //DESCOMENTAR CUANDO JALE LOS ENGRANES
  CatapultSwitch.pressed(CatapultSwitch_cb);
  Catapult.spin(fwd);
  
  //Ida a triball
  Drivetrain.driveFor(reverse, 35, distanceUnits::cm);
  Drivetrain.turnToHeading(45, rotationUnits::deg);
  Drivetrain.driveFor(fwd, 46, distanceUnits::cm);

  // recolectar y lanzar triballs
  int i;
  for(i=0;i<10;i++){ 
    //Recoger el triball
    CollectorFront.spin(fwd);
    CollectorBack.spin(fwd, 80, percent);
    Rail.spin(reverse);
    wait(3.5, seconds);

    Rail.stop(hold);

    Rail.spin(fwd, 90, percent);
    wait(.6, seconds);
    Rail.stop(hold);

    // Avanzar y lanzar triball
    Drivetrain.driveFor(reverse, 60, distanceUnits::cm);
    Drivetrain.stop();

    //LANZA EL TRIBALL
    wait(2, seconds);
    Catapult.spin(fwd, 40, rpm);

    Drivetrain.driveFor(fwd, 60, distanceUnits::cm);*/


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
