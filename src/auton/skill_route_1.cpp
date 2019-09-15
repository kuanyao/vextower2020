#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"

using namespace okapi;

void auton_skill_route_1() {
    capflipMotor.move_absolute(-485, 200);
    intakeMotor.move_velocity(200);
    chassis.moveDistance(40_in); // going to cap with ball under it
    chassis.moveDistanceAsync(-48.625_in);

    // wait until we intake ball to bot
    timeHold = pros::millis();
    while (!isBallTouchBottomSensor())
    {
        pros::delay(20);
    }

    // theres a ball at the top, we want to pull it down back to the trigger
    intakeMotor.move_relative(500, 200);

    pros::delay(300);

    // theres a ball at the top, we want to pull it down back to the trigger
    intakeMotor.move_relative(-400, 200);
    pros::delay(200);
    // there is now a ball in both positions

    // back and turn into shooting position
    flywheelController.moveVelocity(560);
    chassis.waitUntilSettled();
    capflipMotor.move_absolute(0, 200);

    // aim for flag
    chassis.moveDistance(2.95_in);
    chassis.turnAngle(-86.75_deg);
    chassis.moveDistance(58.5_in);

    // shoot first ball when ready
    while (!(flywheelController.getActualVelocity() > 555))
    {
        pros::delay(20);
    }
    intakeMotor.move_relative(1000, 200);

    // wait for first ball to get shot
    timeHold = pros::millis();
    while (!(flywheelController.getActualVelocity() <= 435) && (timeHold + 700 > pros::millis()))
    {
        pros::delay(20);
    }

    // quick switch to mid flag, so when flywheel power lowers cuz of stress of launch, we can use the decel to improve speed
    flywheelController.moveVelocity(435);

    // wait for spinup
    pros::delay(400);

    // shoot 2nd ball
    intakeMotor.move_relative(1200, 200);
    // wait for second ball to get shot
    pros::delay(400);
    chassis.setMaxVelocity(150);
    flywheelController.moveVelocity(0);

    // flip bot flag
    chassis.setMaxVelocity(200);
    intakeMotor.move_velocity(200);
    chassis.turnAngle(-15.5_deg);
    chassis.moveDistance(50_in);
    pros::delay(800);

    chassis.moveDistanceAsync(-72_in);
    intakeMotor.move_relative(-500, 200);
    chassis.waitUntilSettled();
    chassis.turnAngle(90_deg);
    chassis.moveDistance(-4_in);

    intakeMotor.move_velocity(200);
    chassis.moveDistance(21.25_in);
    capflipMotor.move_absolute(-485, 200);

    chassis.moveDistanceAsync(-20_in);
    pros::delay(400);
    capflipMotor.move_absolute(0, 200);
    chassis.turnAngle(-55);

    // shoot first ball when ready
    while (!(flywheelController.getActualVelocity() > 555))
    {
        pros::delay(20);
    }
    intakeMotor.move_relative(1000, 200);

    // wait for first ball to get shot
    timeHold = pros::millis();
    while (!(flywheelController.getActualVelocity() <= 435) && (timeHold + 700 > pros::millis()))
    {
        pros::delay(20);
    }



}