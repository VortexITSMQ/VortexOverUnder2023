/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       constants.h                                               */
/*    Author:       C:\Users\nerij                                            */
/*    Created:      Wed Apr 19 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <math.h>

//----------------- Robot constants -----------------//
const double WHEEL_DIAMETER = 82.55;    //mm
const double WHEEL_TRAVEL   = M_PI * WHEEL_DIAMETER;
const double TRACK_WIDTH    = 300;      //mm
const double TRACK_BASE     = 230;      //mm
const double EXT_GEAR_RATIO = 1.666;    

//----------------- Autonomous time -----------------//
const double DISTANCE_FOR_ROLLER = 7;       //cm
const double VEL_FOR_CHASSIS_ROL = 20;      //pct
const double TURN_FOR_ROLLER     = 100;     //degrees
const double VEL_FOR_ROLLER      = 60;      //pct

const double DIST_FOR_TWO_DISKS  = 20;      //cm
const double VEL_CHASSIS_TWO_D   = 20;      //cm
const double HEADING_SETPOINT    = -6;      //degrees + is for left
const double VEL_FOR_HEADING     = 15;      //pct
const double FIRST_DISK_VEL      = 86;      //pct
const double SECOND_DISK_VEL     = 88;      //pct

const double TURN_TO_STACK_DEG   = -125;
const double TURN_TO_STACK_VEL   = 50;
const double DIST_FOR_STACK      = 80;      //cm
const double DIST_FOR_BACK       = 12;
const double VEL_FOR_STACK_CHAS  = 100;
const double VEL_INTAKE_STACK    = 80;

const double DIST_FOR_COLLECT_STACK =70;
const double VEL_COLLECT_STACK   = 20;

const double TURN_FOR_BAS = 138;

const double THIRD_DISK_VEL      = 71;      //pct
const double FOURHT_DISK_VEL     = 73;
const double FIFTH_DISK_VEL      = 76; 
const double INDEXER_WAIT        = 500;     //ms
const double WAIT_UNTIL_LAUNCH   = 2500;    //ms   

//------------------ User control -------------------//
const double JOYSTICK_DEADBAND    = 10;
const double CONTROL_FLYWHEEL_VEL = 11000;  //max 12000  (mV, milivolts)  
const double INTAKE_VEL           = 85;
const double EXPANSOR_DEG         = -90;
const double EXPANSOR_LAUNCH_VEL  = 95;