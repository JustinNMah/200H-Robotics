// Not commented bc not gonna bother if won't be used.
// Situation: finish the fucking lift.
//b
#include "main.h"
#include "rcLib.cpp"
#ifndef _LIFT_
#define _LIFT_

struct RobotLift{
  pros::Controller rcLift;
  pros::Motor* intakeL = nullptr;
  pros::Motor* intakeR = nullptr;
  pros::Motor* trayLift = nullptr;
  pros::Motor* armsLift = nullptr;
  pros::ADIEncoder* tilter_encoder = nullptr;

  RobotLift() : rcLift(RCM) {}
};

static RobotLift l1;

void LiftInit(pros::Controller rcName, int ml, int mr, int tray, int arms, int tilt1, int tilt2){
  l1.intakeL = new pros::Motor (ml);
  l1.intakeR = new pros::Motor (mr);
  l1.rcLift = rcName;
  l1.trayLift = new pros::Motor (tray);
  l1.armsLift = new pros::Motor (arms);
  l1.tilter_encoder = new pros::ADIEncoder (tilt1, tilt2, false);
}

void intake(int x){
  l1.intakeL->move(x);
  l1.intakeR->move(x);
}

void intakeTare(){
	l1.intakeL->tare_position();
	l1.intakeR->tare_position();
}


void intakeBrake(){
	l1.intakeL->move_velocity(0);
	l1.intakeR->move_velocity(0);
	l1.intakeL->set_brake_mode(MOTOR_BRAKE_HOLD);
	l1.intakeR->set_brake_mode(MOTOR_BRAKE_HOLD);
}

void armsLift(){
  l1.armsLift->move(-127);
}

void armsLower(){
  l1.armsLift->move(127);
}

void armsBrake(){
  l1.armsLift->move_velocity(0);
  l1.armsLift->set_brake_mode(MOTOR_BRAKE_HOLD);
}

void Tilter_Forward(int x){
    l1.trayLift->move_velocity(21*(tanh(2.5-0.33*(x)))+47);
}

void Tilter_Backward(int x){
  l1.trayLift->move_velocity(x);
}

void runLift(){
  if(rcGDV(l1.rcLift, R1)){
    intake(127);
  }
  else if(rcGDV(l1.rcLift, R2)){
    intake(-127);
  }
  else{
    intakeBrake();
  }
  if (rcGDV(l1.rcLift, DIGITAL_A)){
    Tilter_Forward(l1.tilter_encoder->get_value());
  }
  else if(rcGDV(l1.rcLift, DIGITAL_B)){
    Tilter_Backward(-90);
  }
  else{
    l1.trayLift->move_velocity(0);
    l1.trayLift->set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  if (rcGDV(l1.rcLift, L1)){
    armsLift();
  }
  else if (rcGDV(l1.rcLift, L2)){
    armsLower();
  }
  else{
    armsBrake();
  }
  if (rcGDV(l1.rcLift, UP)){
    l1.trayLift->tare_position();
    while (l1.trayLift->get_position() < 230){
      l1.trayLift->move_velocity(127);
    }
    l1.trayLift->move_velocity(0);
    pros::delay(200);
    l1.trayLift->tare_position();
    while(l1.trayLift->get_position() > -205){
      l1.trayLift->move_velocity(-127);
    }
    l1.trayLift->move_velocity(0);
  }
}

void rcLiftInput(){
  runLift();
}

#endif
