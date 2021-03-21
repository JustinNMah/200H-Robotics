#include "main.h"
#include "drive.cpp"
#include "lift.cpp"

//port 6 dead
#define DFL_PRT 1
#define DBL_PRT 2
#define DFR_PRT 12
#define DBR_PRT 15
#define IL_PRT 11
#define IR_PRT 19
#define LIFT_PRT 8
#define TILT_PRT 3
#define QTP 2
#define QTB 1


//Controller ctrl1 uses master
pros::Controller ctrl1(pros::E_CONTROLLER_MASTER);
//Front Left drive motor is reversed
pros::Motor dFl(DFL_PRT, false);
pros::Motor dBl(DBL_PRT, false);
pros::Motor dFr(DFR_PRT, true);
//Back Right drive motor is reversed
pros::Motor dBr(DBR_PRT, true);
pros::Motor intakeL(IL_PRT,false);
//Right side lift motor is reversed
pros::Motor intakeR(IR_PRT, true);
pros::Motor armsL(LIFT_PRT, true);
pros::Motor trayLift(TILT_PRT, pros::E_MOTOR_GEARSET_36, false);
pros::ADIEncoder tilter(QTP, QTB, false);

void opcontrol(){
	//pros::c::motor_set_voltage_limit(11, 11000);
	//pros::c::motor_set_voltage_limit(12, 11000);
	//pros::c::motor_set_voltage_limit(14, 11000);
	//pros::c::motor_set_voltage_limit(20, 11000);
	//pros::c::motor_set_voltage_limit(8, 11000);
	//pros::c::motor_set_voltage_limit(16, 11000);
	//pros::c::motor_set_current_limit(11, 2300);
	//pros::c::motor_set_current_limit(12, 2300);
	//pros::c::motor_set_current_limit(14, 2300);
	//pros::c::motor_set_current_limit(20, 2300);
	//pros::c::motor_set_current_limit(8, 2300);
	//pros::c::motor_set_current_limit(16, 2300);
	tilter.reset();
	LiftInit(ctrl1, IL_PRT, IR_PRT, TILT_PRT, LIFT_PRT, QTP, QTB);
	MecanumDriveInit(ctrl1, DFL_PRT, DBL_PRT, DFR_PRT, DBR_PRT);
	while (true){
		rcLiftInput();
		rcDriveInput();
	pros::delay(20);
	}
}
