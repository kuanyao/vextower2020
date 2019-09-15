#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"
#include "auton/auton.h"

using namespace okapi;

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

void gyroTurn(int target, int timeoutVal)
{

    // tune vals
    float kP = 0.000;
    float kI = 0.000;
    float kD = 0.0000;
    int iDeadband = 400; // 0 for disable
    int tolerance = 0;

    // vars
    target = target + gyro.get(); // relative
    float p = 0;
    float i = 0;
    float d = 0;
    int gyroVal = 0;
    int error = 0;
    int lastError = 0;
    int drive = 0;
    bool timeout = false;
    bool stable = false;
    int startTime = pros::millis();

    while (!timeout && !stable)
    {

        // calculate error
        gyroVal = gyro.get();
        std::cout << "gyro " << gyro.get() << std::endl;
        error = (target - gyroVal);

        // calculate pid
        p = (error * kP);
        if (abs(error) < iDeadband || iDeadband == 0)
            i = ((i + error) * kI);
        else
            i = 0;
        d = ((error - lastError) * kD);

        // store last error
        lastError = error;

        // calculate drive
        drive = (p + i + d);

        // cap vals
        if (drive > 1)
            drive = 1;
        if (drive < -1)
            drive = -1;

        chassis.rotate(drive);

        if (startTime + timeoutVal < pros::millis()) // timeout
            timeout = true;

        if (abs(error) - tolerance <= 0 && abs(lastError) - tolerance <= 0)
            stable = true;

        pros::delay(10);
    }
    chassis.rotate(0);
}
/*void aligner()
{
    while(true){
        int screen_middle_x = 316/2; // 316/2 is mid
      if(vision_sensor.get_by_size(pros::Vision vision_sensor (11, E_VISION_ZERO_CENTER))

    }
}*/
void autonomous()
{
    int autonStart = pros::millis(); // note the start time
    chassis.resetSensors();
    int auton = 5;

    if (autonSelection != 10)
    {
        auton = autonSelection; // this is to enable auton selector
    }

    switch (auton)
    {
    case 5: // test
        //chassis.setMaxVelocity(150);
        //chassis.moveDistance(96_in);
        // chassis.moveDistance(72_in);

        // chassis.moveDistance(72_in);

        //auton_red_descore();
        flywheelController.moveVelocity(530);
        while (!(flywheelController.getActualVelocity() > 530))
        {
            pros::delay(20);
        }
    intakeMotor.move_relative(1000, 200);

        break;
    case 0: // skills 18
        auton_skill_route_1();
        break;
    case 100: // skills old
        auton_skill_route_2();
        break;
    case 1: // blue close, full post, scrape and mid post
        auton_blue_close();
        break;
    case 2: // blue descore (far and cap only)
        auton_blue_far();
        break;
    case 3: // blue descore (far only) works!!!
        auton_blue_descore();
        break;
    case -1: // red close, mid and top flag and park chassis.setMaxVelocity(180);
        auton_red_close();
        break;
    case -2: // red full post and park only
        auton_red_far();
        break;
    case -3: // red descore (far only)
        auton_red_descore();
        break;
    default:
        break;
    }
}