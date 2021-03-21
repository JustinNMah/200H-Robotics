/*----------------------------------------------------------------------------*/
/*                       Name: Remote Control Library                         */
/*                           Created: August 2019                             */
/*                          Author: Chris Katsaros                            */
/*                          For use by: Team 200H                             */
/*                            Revisions made by:                              */
/*                                                                            */
/*    About: rlly simple "library" lol right.. for abstraction of a standard  */
/*           VEX V5 controller.                                               */
/*----------------------------------------------------------------------------*/

// Macro guards to prevent recursive includes.
#include "main.h"
#ifndef _RCLIB_
#define _RCLIB_



// Easy Names for controls
#define A DIGITAL_A
#define B DIGITAL_B
#define X DIGITAL_X
#define Y DIGITAL_Y
#define UP DIGITAL_UP
#define DOWN DIGITAL_DOWN
#define LEFT DIGITAL_LEFT
#define RIGHT DIGITAL_RIGHT
#define L1 DIGITAL_L1
#define L2 DIGITAL_L2
#define R1 DIGITAL_R1
#define R2 DIGITAL_R2
#define ALX ANALOG_LEFT_X
#define ALY ANALOG_LEFT_Y
#define ARX ANALOG_RIGHT_X
#define ARY ANALOG_RIGHT_Y
#define RCM CONTROLLER_MASTER
#define RCP CONTROLLER_PARTNER
#define THRESHOLD 15


// Gets digital value of a button on the controller
int rcGDV(pros::Controller rcName, pros::controller_digital_e_t b1){
  //variable to hold controller value from user input
  int ctlVal;

  // Buttons
  ctlVal = rcName.get_digital(b1);
  return(ctlVal);
}


// Gets analog value of a joystick on the controller
int rcGAV(pros::Controller rcName, pros::controller_analog_e_t j1, bool deadzone){
  //variable to hold controller value from user input
  int ctlVal;

  // Buttons
  if(deadzone == false){
    ctlVal = rcName.get_analog(j1);
  }

  // If a threshold is to be used, this code runs.
  else{
     ctlVal = rcName.get_analog(j1);

     if(abs(rcName.get_analog(j1)) < THRESHOLD){
       ctlVal = 0;
     }
  }
  return(ctlVal);
}
#endif
