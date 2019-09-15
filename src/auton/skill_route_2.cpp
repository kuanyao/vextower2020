#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"

using namespace okapi;

void auton_skill_route_2() {
    // setup
    chassis.setMaxVelocity(150);

    // actual auton
    intakeMotor.move_velocity(200);
    capflipMotor.move_absolute(-450, 200);
    chassis.moveDistance(37_in); // going to cap with ball under it
    capflipMotor.move_absolute(0, 200);

    // wait until we intake ball to bot
    timeHold = pros::millis();
    while (!(triggerBL.get_new_press() || triggerBR.get_new_press()) && (timeHold + 2000 > pros::millis()))
    {
        pros::delay(20);
    }

    // theres a ball at the top, we want to pull it down back to the trigger
    pros::delay(100);
    intakeMotor.move_relative(-490, 200);
    // there is now a ball in both positions

    // back and turn for descore
    chassis.moveDistance(-4_in);
    flywheelController.moveVelocity(515);
    chassis.turnAngle(-54_deg);
    pros::delay(500);
    intakeMotor.move_relative(1500, 200);
    pros::delay(300);

    // second ball
    flywheelController.moveVelocity(540);
    pros::delay(1500);
    intakeMotor.move_relative(1000, 200);
    pros::delay(500);
    flywheelController.moveVelocity(0);

    // move and turn for 1st scrape cap
    chassis.turnAngle(60_deg);
    chassis.moveDistance(-7_in);
    chassis.turnAngle(270); // things are weird so 270 = 90_deg
    chassis.moveDistance(23.5_in);
    chassis.turnAngle(-80_deg);
    chassis.moveDistance(8_in);

    // scrape
    capflipMotor.move_absolute(-525, 200);
    intakeMotor.move_velocity(200);
    pros::delay(200);
    chassis.moveDistance(-10_in);
    chassis.moveDistanceAsync(-20_in);

    // wait for first ball to get to top pos
    while (!(triggerTL.get_value() || triggerTR.get_value()))
    {
        pros::delay(20);
    }
    ballTriggerTop = true;

    // wait for second ball to get to bot pos
    timeHold = pros::millis();
    while (!(triggerBL.get_value() || triggerBR.get_value()) && (timeHold + 5000 > pros::millis()))
    {
        pros::delay(20);
    }

    if (triggerBL.get_new_press() || triggerBR.get_new_press())
    {
        ballTriggerBottom = true;
    }

    // we got a second ball, let it pull up a bit
    intakeMotor.move_relative(400, 200);
    pros::delay(500);
    intakeMotor.move_relative(-500, 200);

    capflipMotor.move_absolute(0, 200);
    chassis.waitUntilSettled();
    chassis.turnAngle(-270);

    // align with wall
    chassis.forward(-1);
    pros::delay(300);
    chassis.forward(-0.2);
    pros::delay(500);
    chassis.stop(); // let it settle
    pros::delay(500);

    // move for front flags, start with closest to red
    flywheelController.moveVelocity(430);
    chassis.moveDistance(67_in);
    chassis.turnAngleAsync(10_deg);

    // shoot closest pole to red
    pros::delay(500);
    intakeMotor.move_relative(1500, 200);
    pros::delay(300);

    // second ball
    flywheelController.moveVelocity(540);
    pros::delay(1500);
    intakeMotor.move_relative(1000, 200);
    pros::delay(500);
    flywheelController.moveVelocity(0);

    // flip bot flag
    chassis.turnAngle(-12_deg);
    chassis.moveDistance(57_in);

    // move to line up with 2nd scrape cap
    chassis.moveDistance(-43_in);
    chassis.turnAngle(40_deg);
    chassis.moveDistance(14_in);

    // scrape
    capflipMotor.move_absolute(-530, 200);
    intakeMotor.move_velocity(200);
    pros::delay(200);
    chassis.moveDistance(-20_in);
    chassis.moveDistanceAsync(6_in);

    // wait for first ball to get to top pos
    while (!(triggerTL.get_value() || triggerTR.get_value()))
    {
        pros::delay(20);
    }
    ballTriggerTop = true;

    // wait for second ball to get to bot pos
    timeHold = pros::millis();
    while (!(triggerBL.get_value() || triggerBR.get_value()) && (timeHold + 5000 > pros::millis()))
    {
        pros::delay(20);
    }

    if (triggerBL.get_new_press() || triggerBR.get_new_press())
    {
        ballTriggerBottom = true;
    }

    // we got a second ball, let it pull up a bit
    intakeMotor.move_relative(400, 200);
    pros::delay(500);
    intakeMotor.move_relative(-500, 200);

    capflipMotor.move_absolute(-450, 200);
    chassis.waitUntilSettled();

    // line up for middle pole
    chassis.turnAngle(50_deg);

    // spin up and move close to 2nd cap with ball under
    chassis.moveDistance(34_in);
    flywheelController.moveVelocity(440);

    // turn and shoot mid pole
    chassis.turnAngle(-90_deg);
    capflipMotor.move_absolute(0, 200);

    // shoot closest pole to red
    pros::delay(500);
    intakeMotor.move_relative(1500, 200);
    pros::delay(300);

    // second ball
    flywheelController.moveVelocity(550);
    pros::delay(1500);
    intakeMotor.move_relative(1000, 200);
    pros::delay(500);
    flywheelController.moveVelocity(0);

    // back and turn for park
    chassis.turnAngle(90_deg);
    chassis.moveDistance(-8_in);
    chassis.turnAngle(90_deg);

    // align with wall
    chassis.forward(1);
    pros::delay(300);
    chassis.forward(0.2);

    chassis.moveDistance(26_in);
    chassis.turnAngle(-90_deg);
    chassis.moveDistance(30_in);
}