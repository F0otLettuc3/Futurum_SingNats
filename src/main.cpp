#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	Motor FL(FLPort,E_MOTOR_GEARSET_18,true,E_MOTOR_ENCODER_DEGREES);
	Motor ML(MLPort,E_MOTOR_GEARSET_18,false,E_MOTOR_ENCODER_DEGREES);
	Motor BL(BLPort,E_MOTOR_GEARSET_18,true,E_MOTOR_ENCODER_DEGREES);
	Motor FR(FRPort,E_MOTOR_GEARSET_18,false,E_MOTOR_ENCODER_DEGREES);
	Motor MR(MRPort,E_MOTOR_GEARSET_18,true,E_MOTOR_ENCODER_DEGREES);
	Motor BR(BRPort,E_MOTOR_GEARSET_18,false,E_MOTOR_ENCODER_DEGREES);

	Motor Catapult(CataPort,E_MOTOR_GEARSET_36,false,E_MOTOR_ENCODER_DEGREES);
	Motor Intake(IntakePort,E_MOTOR_GEARSET_06,true,E_MOTOR_ENCODER_DEGREES);
	ADIDigitalOut Expansion(ExpansionPort, HIGH);
	ADIDigitalOut Expansion2(Expansion2Port, HIGH);
	Rotation CataRot(CataSensor);




	Task catapultTask(catapultControl, (void*)"PROS",TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT);
 	Task debugTask(Debug, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task odometryTask(Odometry, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task sensorsTask(Sensors, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
void autonomous() {
	// ADIDigitalOut Expansion(ExpansionPort);
	// Expansion.set_value(HIGH);
	// int autonum = 1;
	// switch(autonum){
	// 	case 1: red1(); break;
	// 	case 2: red2(); break;
	// 	case 3: blue1(); break;
	// 	case 4: blue2(); break;
	// 	case 5: skills(); break;
	// }
	// delay(25);

	// Motor FL(FLPort);
	// Motor ML(MLPort);
	// Motor BL(BLPort);
	// Motor FR(FRPort);
	// Motor MR(MRPort);
	// Motor BR(BRPort);
	// Motor Intake(IntakePort);
	// ADIDigitalOut Expansion(ExpansionPort);
	//
	//
	// Task controlTask(Control, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	// double start = millis();
	// // Expansion.set_value(HIGH)	;
	// baseMove(-4);
	// Intake.move(-127);
	// baseMove(-4);
	// waitBase(500);
	// Intake.move(0);
	// baseMove(5);
	// waitBase(1000);
	// baseTurn(90);
	// waitBase(1000);
	// CataMove(true);
	// delay(500);
	// CataMove(false);
	// controlTask.remove();
	//
	// printf("end");


}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
		Controller master(pros::E_CONTROLLER_MASTER);
		Motor FL(FLPort);
		Motor ML(MLPort);
		Motor BL(BLPort);
		Motor FR(FRPort);
		Motor MR(MRPort);
		Motor BR(BRPort);
		Motor Catapult(CataPort);
		Motor Intake(IntakePort);

		Rotation CataRot(CataSensor);
		ADIDigitalOut Expansion(ExpansionPort);
		ADIDigitalOut Expansion2(Expansion2Port);



		auton = false;
		Expansion.set_value(HIGH);
		Expansion2.set_value(HIGH);
		double prevLeft, prevRight;
		double powerL, powerR;
		double setTime = millis();
		bool wall = false;
		bool climb = false;
		bool tank = true;
		double left, right;




		while (true) {

			if(master.get_digital_new_press(DIGITAL_Y)){tank = !tank;}
			
			if(tank){
			left = master.get_analog(ANALOG_LEFT_Y);
			right = master.get_analog(ANALOG_RIGHT_Y);
			}
			else{
			double power = master.get_analog(ANALOG_LEFT_Y);
			double turn = master.get_analog(ANALOG_RIGHT_X);
			left = power + turn;
			right = power - turn;
			
			}

			FL.move(left);
			ML.move(left);
			BL.move(left);
			FR.move(right);
			MR.move(right);
			BR.move(right);

		if(master.get_digital_new_press(DIGITAL_L1)){
			catapultTarg = 0;
			setTime = millis();
		}
		if((millis()-setTime)>500){
			catapultTarg = downTarg;
			setTime = millis();
		}

		if(master.get_digital(DIGITAL_R1)){Intake.move(127);}
		else if(master.get_digital(DIGITAL_R2)){Intake.move(-127);}
		else{Intake.move(-30);}

		if(master.get_digital_new_press(DIGITAL_L2)){wall = !wall;}
		Expansion.set_value(wall);

		if(master.get_digital_new_press(DIGITAL_X)){climb = !climb;}
		Expansion2.set_value(climb);


	delay(20);
	}
}
