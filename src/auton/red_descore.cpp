#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"

using namespace okapi;

void auton_red_descore() {
    chassis.setMaxVelocity(150);
    intakeMotor.move_velocity(200);
    chassis.moveDistance(36.15_in); // going to cap with ball under it
    chassis.moveDistanceAsync(-20_in);

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

    // aim for flag
    chassis.moveDistance(12_in);
    chassis.turnAngle(-90.00_deg);

    chassis.setMaxVelocity(75);
    chassis.forward(10);
    pros::delay(600);
    chassis.stop();

    chassis.setMaxVelocity(150);
    chassis.moveDistance(-6_in);

    chassis.turnAngle(48.0363514159_deg);

    // shoot first ball when ready
    while (!(flywheelController.getActualVelocity() > 560))
    {
        pros::delay(20);
    }
    intakeMotor.move_relative(1000, 200);

    // wait for first ball to get shot
    timeHold = pros::millis();
    while (!(flywheelController.getActualVelocity() <= 500) && (timeHold + 700 > pros::millis()))
    {
        pros::delay(20);
    }

    // quick switch to mid flag, so when flywheel power lowers cuz of stress of launch, we can use the decel to improve speed
    flywheelController.moveVelocity(500);

    // wait for spinup
    pros::delay(400);

    // shoot 2nd ball
    intakeMotor.move_relative(1200, 200);
    // wait for second ball to get shot
    pros::delay(400);
    chassis.setMaxVelocity(200);
    flywheelController.moveVelocity(0);

    // pros::delay(500);
    // chassis.turnAngle(86.5_deg);
    // chassis.moveDistance(-11_in);

    
    // chassis.turnAngle(-90_deg);
    // intakeMotor.move_velocity(200);
    // chassis.moveDistance(5_in);
    // capflipMotor.move_absolute(-555, 200);
    // pros::delay(300);
    // chassis.moveDistance(-5_in);
    //  // wait until we intake ball to bot
    // timeHold = pros::millis();
    // while (!isBallTouchBottomSensor())
    // {
    //     pros::delay(20);
    // }

    // // theres a ball at the top, we want to pull it down back to the trigger
    // intakeMotor.move_relative(500, 200);

    // pros::delay(300);

    // // theres a ball at the top, we want to pull it down back to the trigger
    // intakeMotor.move_relative(-400, 200);
    // pros::delay(200);
    // // there is now a ball in both positions

    // // back and turn into shooting position
    // flywheelController.moveVelocity(550);
    // chassis.waitUntilSettled();
    // chassis.turnAngle(45_deg);
    // while (!(flywheelController.getActualVelocity() > 500))
    // {
    //     pros::delay(20);
    // }
    // intakeMotor.move_relative(3000, 200);
    // pros::delay(1000);
    // chassis.turnAngle(-45_deg);
    // chassis.moveDistance(6_in);

    chassis.turnAngle(-43_deg);
    intakeMotor.move_velocity(200);
    chassis.moveDistance(40_in);


        
}