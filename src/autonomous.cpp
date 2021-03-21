#include "../include/main.h"
#include "okapi/api.hpp"
using namespace okapi;

pros::Motor aFl(1, true);
pros::Motor aBl(2, false);
pros::Motor aFr(12) ;
//Back Right drive motor is reversed
pros::Motor aBr(15, true);
pros::Motor aintakeL(11, pros::E_MOTOR_GEARSET_18);
//Right side lift motor is reversed
pros::Motor aintakeR(19, pros::E_MOTOR_GEARSET_18, true);
pros::Motor atrayLift(3, pros::E_MOTOR_GEARSET_36);
pros::Motor aArmsLift(8, false);
pros::ADIEncoder aTiltCheck(1, 2, false);

auto myChassis = ChassisControllerFactory::create(
  {-2, 1}, {15, -12},
  AbstractMotor::gearset::green,
  {4.13_in, 10_in}
);

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void aIntakeBrake(){
  aintakeL.move_velocity(0);
  aintakeR.move_velocity(0);
}

void aIntake(int x){
  aintakeR.move_velocity(x);
  aintakeL.move_velocity(x);
}

void outtake(){
  aintakeL.move_relative(-400, 200);
  aintakeR.move_relative(-400, 200);
}
void skills(){
  aIntake(200);
  myChassis.setMaxVelocity(100);
  myChassis.moveDistance(4_ft);
  myChassis.turnAngle(55_deg);
  myChassis.moveDistance(-4_ft);
  myChassis.turnAngle(-56_deg);
  myChassis.moveDistance(2_ft);
  myChassis.moveDistance(2_ft);
  myChassis.waitUntilSettled();
  myChassis.moveDistance(-1_ft);
  myChassis.turnAngle(-260_deg);
  outtake();
  myChassis.waitUntilSettled();
  myChassis.moveDistance(4_ft);
  myChassis.waitUntilSettled();
  atrayLift.move_absolute(2000, 30); // makes bot poop
  pros::delay(2000);
  aIntake(-50);
  pros::delay(1200);
  myChassis.moveDistance(-0.6_ft);
  //myChassis.turnAngle(-200_deg);
  myChassis.moveDistance(-1_ft);
}

void aTurnRight(int x){
  aFl.move_velocity(x);
  aFr.move_velocity(x*-1);
  aBl.move_velocity(x);
  aBr.move_velocity(x*-1);
}

void aTurnLeft(int x){
  aFl.move_velocity(x*-1);
  aFr.move_velocity(x);
  aBl.move_velocity(x*-1);
  aBr.move_velocity(x);
}

void aMove(int x){
  aFl.move_velocity(x);
  aFr.move_velocity(x);
  aBl.move_velocity(x);
  aBr.move_velocity(x);
}

void tareMotors(){
  aFl.tare_position();
  aFr.tare_position();
  aBl.tare_position();
  aBr.tare_position();
}

void aTilter_Forward(int x){
  atrayLift.move_velocity(21*(tanh(2.5-0.33*(x)))+47);
}

void aTilter_Backward(int x){
  atrayLift.move_velocity(x);
}

void aLiftStop(){
  atrayLift.move_velocity(0);
}

void aStrafeRight(int x){
  aBr.move_velocity(x);
  aFr.move_velocity(x * -1);
  aBl.move_velocity(x * -1);
  aFl.move_velocity(x);
}

void aStrafeLeft(int x){
  aBl.move_velocity(x);
  aFl.move_velocity(x * -1);
  aBr.move_velocity(x * -1);
  aFr.move_velocity(x);
}

void aArms(int x){
  aArmsLift.move_velocity(x);
}

void aArmsBrake(){
  aArmsLift.move_velocity(0);
  aArmsLift.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void aStop(){
  aFl.move_velocity(0);
  aFr.move_velocity(0);
  aBl.move_velocity(0);
  aBr.move_velocity(0);
}

void redSmall(){
  atrayLift.tare_position();
  while (atrayLift.get_position() < 300){
    atrayLift.move_velocity(127);
  }
  atrayLift.move_velocity(0);
  pros::delay(200);
  atrayLift.tare_position();
  while(atrayLift.get_position() > -285){
    atrayLift.move_velocity(-127);
  }
  atrayLift.move_velocity(0);
  pros::c::motor_set_voltage_limit(1, 11000);
  pros::c::motor_set_voltage_limit(11, 11000);
  pros::c::motor_set_current_limit(12, 2300);
  pros::c::motor_set_current_limit(13, 2300);
  myChassis.setMaxVoltage(11000);
  aIntake(127);
  myChassis.setMaxVelocity(80);
  myChassis.moveDistance(4_ft);
  myChassis.turnAngle(23.25_deg);
  myChassis.moveDistance(-4.25_ft);
  myChassis.turnAngle(-23.5_deg);
  myChassis.moveDistance(2_ft);
  myChassis.setMaxVelocity(50);
  myChassis.moveDistance(1.8_ft);
  pros::delay(500);
  myChassis.waitUntilSettled();
  myChassis.setMaxVelocity(80);
  myChassis.moveDistance(-2_ft);
  myChassis.turnAngle(-110_deg);
  pros::delay(100);
  outtake();
  myChassis.waitUntilSettled();
  myChassis.moveDistance(1.45_ft);
  aFl.set_brake_mode(MOTOR_BRAKE_COAST);
  aFr.set_brake_mode(MOTOR_BRAKE_COAST);
  aBl.set_brake_mode(MOTOR_BRAKE_COAST);
  aFr.set_brake_mode(MOTOR_BRAKE_COAST);
  aIntake(-127);
  pros::delay(100);
  aIntakeBrake();
  atrayLift.move_absolute(2100, 30); // makes bot poop
  pros::delay(4000);
  aFl.set_brake_mode(MOTOR_BRAKE_HOLD);
  aFr.set_brake_mode(MOTOR_BRAKE_HOLD);
  aBl.set_brake_mode(MOTOR_BRAKE_HOLD);
  aBr.set_brake_mode(MOTOR_BRAKE_HOLD);
  aMove(-50);
  aIntake(-127);
  pros::delay(1360);
  aIntakeBrake();
  aStop();
  myChassis.turnAngle(-112_deg);
  atrayLift.move_absolute(-2100, 30);
  aMove(-40);
  pros::delay(2500);
  aStop();
  aIntake(127);
  myChassis.moveDistance(3.52_ft);
  aStop();
  pros::delay(500);
  aIntakeBrake();
  pros::delay(100);
  outtake();
  myChassis.waitUntilSettled();
  myChassis.setMaxVelocity(30);
  myChassis.moveDistance(-0.5_ft);
  aArms(127);
  pros::delay(1250);
  aArmsBrake();
  myChassis.moveDistance(0.75_ft);
  aIntake(-127);
  pros::delay(1000);
  aIntakeBrake();
}

void blueSmall(){
  tareMotors();
  pros::delay(500);
  while(aFl.get_position() < 3150){
    aIntake(127);
    aMove(60);
  }
  aStop();
  aIntakeBrake();
  tareMotors();
  while(aFl.get_position() > -1925){
    aMove(-60);
  }
  aStop();
  tareMotors();
  while (aFl.get_position() > -2000){
    aTurnLeft(60);
  }
  aStop();
  tareMotors();
  aMove(60);
  pros::delay(1100);
  aStop();
  pros::delay(100);
  aStop();
  aintakeL.tare_position();
  aintakeR.tare_position();
  while (aintakeL.get_position() > -400){
    aIntake(-127);
  }
  aIntakeBrake();
  pros::delay(100);
  atrayLift.move_velocity(60);
  pros::delay(2500);
  atrayLift.move_velocity(0);
  aMove(60);
  pros::delay(200);
  aIntake(-127);
  pros::delay(500);
  aIntakeBrake();
  aMove(-60);
  aIntake(-60);
  pros::delay(1500);
  aStop();
  aIntakeBrake();
  atrayLift.move_velocity(-60);
  pros::delay(2500);
  atrayLift.move_velocity(0);

}

void bigNew(){
  myChassis.setMaxVelocity(100);
  myChassis.moveDistance(0.5_ft);
  myChassis.waitUntilSettled();
  myChassis.moveDistance(-0.6_ft);
  aArms(-127);
  pros::delay(500);
  aArms(127);
  pros::delay(500);
  aArmsLift.move_velocity(0);
  aIntake(100);
  myChassis.moveDistance(1.5_ft);
  pros::delay(50);
  myChassis.turnAngle(32_deg);
  myChassis.moveDistance(-1.8_ft);
  myChassis.turnAngle(-32_deg);
  myChassis.moveDistance(1.2_ft);
  myChassis.turnAngle(90_deg);
  myChassis.moveDistance(2.4_ft);
  myChassis.waitUntilSettled();
  myChassis.turnAngle(45_deg);
  myChassis.moveDistance(1_ft);
  aFl.set_brake_mode(MOTOR_BRAKE_COAST);
  aFr.set_brake_mode(MOTOR_BRAKE_COAST);
  aBl.set_brake_mode(MOTOR_BRAKE_COAST);
  aFr.set_brake_mode(MOTOR_BRAKE_COAST);
  outtake();
  aIntake(-127);
  pros::delay(100);
  aIntakeBrake();
  atrayLift.move_absolute(2100, 30); // makes bot poop
  pros::delay(4000);
  aFl.set_brake_mode(MOTOR_BRAKE_HOLD);
  aFr.set_brake_mode(MOTOR_BRAKE_HOLD);
  aBl.set_brake_mode(MOTOR_BRAKE_HOLD);
  aBr.set_brake_mode(MOTOR_BRAKE_HOLD);
  aMove(-50);
  aIntake(-127);
  pros::delay(1360);
  aIntakeBrake();
  aStop();



}

void autonomous(){
  //big();
  bigNew();
}
