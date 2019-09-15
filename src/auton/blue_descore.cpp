#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"

using namespace okapi;

void auton_blue_descore() {
    // setup
    chassis.setMaxVelocity(130);

    // actual auton
    intakeMotor.move_velocity(200);
    chassis.moveDistance(37_in); // going to cap with ball under it

    // wait until we intake ball to bot
    timeHold = pros::millis();
    while (!(triggerBL.get_new_press() || triggerBR.get_new_press()) && (timeHold + 2000 > pros::millis()))
    {
        pros::delay(20);
    }

    // theres a ball at the top, we want to pull it down back to the trigger
    pros::delay(100);
    intakeMotor.move_relative(-500, 200);
    // there is now a ball in both positions

    // back and turn for descore
    chassis.moveDistance(-4_in);
    flywheelController.moveVelocity(520);
    // gyroTurn(600, 1000);
    chassis.setMaxVelocity(180);
    chassis.turnAngle(59_deg);
    chassis.setMaxVelocity(130);
    pros::delay(3000); // wait for them to shoot
    if (autonPark == false) // we can afford to wait a little longer if we arent parking
        pros::delay(2000);
    intakeMotor.move_relative(1500, 200);
    pros::delay(300);

    // second ball
    flywheelController.moveVelocity(540);
    pros::delay(1500);
    intakeMotor.move_relative(1000, 200);
    pros::delay(500);
    flywheelController.moveVelocity(0);

    if (autonPark == false) 
        pros::delay(15000);

    // move and turn for park
    chassis.turnAngle(-59_deg);
    chassis.moveDistance(-5_in);
    chassis.turnAngle(270);

    // park
    chassis.moveDistance(7_in);
    chassis.moveDistance(26_in);
    
}