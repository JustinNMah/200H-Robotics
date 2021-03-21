 /*----------------------------------------------------------------------------*/
/*                       Name: Mecanum Drive Control                          */
/*                           Created: August 2019                             */
/*                          Author: Chris Katsaros                            */
/*                          For use by: Team 200H                             */
/*                            Revisions made by:                              */
/*                                                                            */
/*    About: Simple abstraction of a standard 4 motor V5 mecanum drive.       */
/*           Gyroscope code still needs to be added to implement              */
/*           field-oriented control.                                          */
/*----------------------------------------------------------------------------*/
#include "main.h"
#include "rcLib.cpp"

// Macro guards
#ifndef _DRIVE_
#define _DRIVE_

//#include <memory> seems to be uneeded now

// int x = 0;
// int y = 0;

// Struct for holding drive information
struct RobotDrive{
  pros::Controller rcDrive;
  pros::Motor* fl = nullptr;
  pros::Motor* bl = nullptr;
  pros::Motor* fr = nullptr;
  pros::Motor* br = nullptr;

  // Init pros::Controller with ID master on new RobotDrive
  RobotDrive() : rcDrive(RCM) {}
};

static RobotDrive d1;
// Function to run drive motors
void runDrive(int lefty, int rightx){
  // Calculate motor power.
  int frontLeft  = lefty + 0.75*rightx;
  int backLeft   = lefty + 0.75*rightx;
  int frontRight = lefty - 0.75*rightx;
  int backRight  = lefty - 0.75*rightx;

  // Normalize motor power (completely took this from jpearman, thank ya kindly jpearman).
  int max = abs(frontLeft);

  if(abs(backLeft) > max){
    max = abs(backLeft);
  }
  if(abs(backRight) > max){
    max = abs(backRight);
  }
  if(abs(frontRight) > max){
    max = abs(frontRight);
  }
  if(max>127){
    frontLeft  = 127 * frontLeft / max;
    backLeft   = 127 * backLeft  / max;
    backRight  = 127 * backRight  / max;
    frontRight = 127 * frontRight / max;
  }

  // Set power to motors.
  d1.fl->move(frontLeft);
  d1.bl->move(backLeft);
  d1.fr->move(frontRight);
  d1.br->move(backRight);
}
// //BrakeMode but bad
//   if (rcGDV(d1.rcDrive, DIGITAL_X)){
//     if (y == 0){
//       x++;
//       y = 1;
//     }
//   }
//   else{
//     y = 0;
//   }
//   if (x%2 == 1){
//     if (frontLeft == 0 && frontRight == 0 && backLeft == 0 && backRight == 0){
//       d1.fl->move_velocity(0);
//       d1.bl->move_velocity(0);
//       d1.fr->move_velocity(0);
//       d1.br->move_velocity(0);
//       d1.fl->set_brake_mode(MOTOR_BRAKE_HOLD);
//       d1.bl->set_brake_mode(MOTOR_BRAKE_HOLD);
//       d1.fr->set_brake_mode(MOTOR_BRAKE_HOLD);
//       d1.br->set_brake_mode(MOTOR_BRAKE_HOLD);
//     }
//   }
//   else if (x%2 == 0){
//     if (frontLeft == 0 && frontRight == 0 && backLeft == 0 && backRight == 0){
//       d1.fl->move_velocity(0);
//       d1.bl->move_velocity(0);
//       d1.fr->move_velocity(0);
//       d1.br->move_velocity(0);
//       d1.fl->set_brake_mode(MOTOR_BRAKE_COAST);
//       d1.bl->set_brake_mode(MOTOR_BRAKE_COAST);
//       d1.fr->set_brake_mode(MOTOR_BRAKE_COAST);
//       d1.br->set_brake_mode(MOTOR_BRAKE_COAST);
//     }
//   }
// }


// Function to get user input from controller joysticks, called in opcontrol
void rcDriveInput(){
  // Get joystick input values.
  int ly = rcGAV(d1.rcDrive, ALY, false);
  int rx = rcGAV(d1.rcDrive, ARX, false);

  runDrive(ly, rx);
}


// Function to initialize a mecanum drive, called in opcontrol
void MecanumDriveInit(pros::Controller rcName, int mfl, int mbl, int mfr, int mbr){
  d1.rcDrive = rcName;
  d1.fl = new pros::Motor(mfl);
  d1.bl = new pros::Motor(mbl);
  d1.fr = new pros::Motor(mfr);
  d1.br = new pros::Motor(mbr);
}
#endif
