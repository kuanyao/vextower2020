#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"

using namespace okapi;

void auton_blue_far() {
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
    intakeMotor.move_relative(-400, 200);

    // there is now a ball in both positions, shoot
    chassis.moveDistance(-4_in);
    flywheelController.moveVelocity(520);
    chassis.turnAngle(61_deg);
    pros::delay(2000); // wait for them to shoot
    intakeMotor.move_relative(1500, 200);
    pros::delay(300);

    // second ball
    flywheelController.moveVelocity(545);
    pros::delay(1000);
    intakeMotor.move_relative(1000, 200);
    pros::delay(500);
    flywheelController.moveVelocity(0);

    // CAPFLIP TIME! SUPRISUWU
    chassis.setMaxVelocity(180);
    chassis.turnAngle(-60_deg);
    chassis.moveDistance(7_in);
    chassis.turnAngle(-90_deg);
    capflipMotor.move_absolute(-700, 200);

    // flip and come back
    chassis.moveDistance(10_in);
    capflipMotor.move_absolute(0, 200);

    chassis.driveVector(0.5, 0.8);
    pros::delay(500);
    // chassis.turnAngle(-180_deg);
    // chassis.moveDistance(15_in);

    // // move and turn for park
    // chassis.turnAngle(-90_deg);
    // chassis.moveDistance(-10_in);
    chassis.turnAngle(270);

    // park
    chassis.moveDistance(7_in);
    chassis.moveDistance(26_in);
    
}