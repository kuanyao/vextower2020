#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"

okapi::MotorGroup flywheelController({-FLY_MTR1, -FLY_MTR2});
pros::Motor intakeMotor(INTAKE_MTR, pros::E_MOTOR_GEARSET_18, false);
pros::Motor capflipMotor(CAPFLIP_MTR, pros::E_MOTOR_GEARSET_18, false);

// intake triggers
pros::ADIDigitalIn triggerBL(TRIGGER_BL);
pros::ADIDigitalIn triggerBR(TRIGGER_BR);
pros::ADIDigitalIn triggerTL(TRIGGER_TL);
pros::ADIDigitalIn triggerTR(TRIGGER_TR);

pros::ADIAnalogIn trackerHigh(TRACK_HIGH);
pros::ADIAnalogIn trackerLow(TRACK_LOW);

// other
pros::Controller controllerPros(pros::E_CONTROLLER_MASTER);

// okapi factories
using namespace okapi;

okapi::ChassisControllerPID chassis = okapi::ChassisControllerFactory::create(
    {LEFT_MTR2, LEFT_MTR1},     // Left motors (the sensor vals are read from first motor on each side)
    {-RIGHT_MTR2, -RIGHT_MTR1}, // Right motors

    IterativePosPIDController::Gains{0.002, 0.0003, 0.000000}, // distance args
    IterativePosPIDController::Gains{0.000, 0.0000, 0.0000},  // angle args (keeps robot straight)
    IterativePosPIDController::Gains{0.002, 0.0060, 0.000045},  // turn args

    AbstractMotor::gearset::green, // normal gearset
    {4.2_in, 11.95_in}                // 4 inch wheels, 12.5 inch wheelbase width
);
