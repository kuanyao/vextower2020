#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"
using namespace okapi;

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

void opcontrol()
{
	chassis.stop();

	while (true)
	{
		// capflip control
		if (controllerPros.get_digital_new_press(DIGITAL_RIGHT)) // new cycle press, go to next preset
		{
			//capflipMotor.move_absolute(capflipTarget, 200);
		}
		else if (controllerPros.get_digital_new_press(DIGITAL_Y)) // reset capflip
		{
			//capflipMotor.move_absolute(0, 200);
		}

		if (controllerPros.get_digital(DIGITAL_L2)) // reverse intake
		{
			//intakeMotor.move_velocity(-200);
		}

		// debug
		// std::cout << chassis.getSensorVals()[0] << std::endl;
		// std::cout << chassis.getSensorVals()[1] << std::endl;
		// std::cout << capflipMotor.get_position() << std::endl;
		// std::cout << "temp " << flywheelController.getTemperature() << std::endl;
		// std::cout << "eff " << flywheelController.getEfficiency() << std::endl;
		// std::cout << "gyro " << gyro.get() << std::endl;
		// std::cout << "temp " << intakeMotor.get_temperature() << std::endl;
		// std::cout << "eff " << intakeMotor.get_efficiency() << std::endl;
		// if (triggerBR.get_value())
		// {
		// 	printf("BR\n");
		// }
		// if (triggerBL.get_value())
		// {
		// 	printf("BL\n");
		// }
		// if (triggerTR.get_value())
		// {
		// 	printf("TR\n");
		// }
		// if (triggerTL.get_value())
		// {
		// 	printf("TL\n");
		// }

		// chassis control
		chassis.tank((controllerPros.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 0.00787401574),
					 controllerPros.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 0.00787401574);

		pros::delay(20);
	}
}
