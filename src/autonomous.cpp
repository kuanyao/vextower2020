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
        break;
    default:
        break;
    }
}