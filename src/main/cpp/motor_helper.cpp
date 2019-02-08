#include <math.h>
#include <frc/Timer.h>
#include <iostream>
#include <frc/Spark.h>
#include <frc/PWMSpeedController.h>
#include <frc/Victor.h>
#include <frc/VictorSP.h>
#include <frc/Talon.h>
#include "motor_helper.hpp"

Motor::Motor(int motorChannel, MotorType motorType)
{
	this->firstRun = true;
	this->accelBehavior = BehaviorType::MAINTAIN;
	this->motorState = VelocityState::CONSTANT;
	this->motorFamily = motorType;
	this->clock.Start();
	
	switch(this->motorFamily)
	{
		case MotorType::TALON:
			this->motorTalon = new frc::Talon(motorChannel);
			this->pwmMotor = this->motorTalon;
			break;

		case MotorType::VICTOR:
			this->motorVictor = new frc::Victor(motorChannel);
			this->pwmMotor = this->motorVictor;
			break;

		case MotorType::VICTOR_SP:
			this->motorVictorSP = new frc::VictorSP(motorChannel);
			this->pwmMotor = this->motorVictorSP;
			break;

		case MotorType::SPARK:
			this->motorSpark = new frc::Spark(motorChannel);
			this->pwmMotor = this->motorSpark;
			break;

		default:
			break;
	}
}

void Motor::gradualRotation(
	double motorMaxSpeed,
	double speedIncreaseDuration,
	BehaviorType newBehavior
)
{
	this->gradualMaxSpeed = motorMaxSpeed;
	this->accelBehavior = newBehavior;

	if(this->firstRun)
	{
		this->gradualCurrentSpeed = this->pwmMotor->Get();
		this->speedIncreaseRate = (this->gradualMaxSpeed - this->gradualCurrentSpeed) / (1000 * speedIncreaseDuration);
		this->firstRun = false;
		this->lastTime = 0;
	}

    this->testSpeed = this->speedIncreaseRate >= 0 
        ? 1 
        : -1;

	if((this->gradualCurrentSpeed * this->testSpeed) >= fabs(this->gradualMaxSpeed))
	{
		this->instantaneousRotation(
            this->accelBehavior 
                ? this->gradualMaxSpeed 
                : 0
        );
	}
	else
	{
		this->accelerateMotor();
	}
}

void Motor::instantaneousRotation(double motorSpeed)
{
	this->motorState = VelocityState::CONSTANT;
	this->pwmMotor->Set(motorSpeed);
}

void Motor::instantaneousStop()
{
	this->motorState = VelocityState::CONSTANT;
	this->pwmMotor->Set(0);
}

double Motor::getSpeed()
{
	return this->pwmMotor->Get();
}

void Motor::maintainSpeed()
{
	this->instantaneousRotation(this->getSpeed());
}

void Motor::resetAccelerate(bool forceReset)
{
	this->firstRun = this->motorState == VelocityState::CONSTANT || forceReset;
}

void Motor::accelerateMotor()
{
	this->currentTime = this->clock.Get() * 1000;
	if((this->currentTime - this->lastTime) >= 1)
	{
		this->motorState = VelocityState::ACCELERATE;
		this->gradualCurrentSpeed = this->gradualCurrentSpeed + this->speedIncreaseRate;
		this->pwmMotor->Set(this->gradualCurrentSpeed);
		this->lastTime = this->currentTime;
	}
}

void Motor::brake()
{
	this->brakeTimeCurrent = this->clock.Get() * 1000;
	if((this->brakeTimeCurrent - this->brakeTimeLast) >= 5)
	{
		this->instantaneousRotation(this->brakeMotorSpeed);
		this->brakeMotorSpeed = -this->brakeMotorSpeed;
		this->brakeTimeLast = this->brakeTimeCurrent;
	}
}

void Motor::slowSpeed(double period, double changeSpeed, double multiplier)
{
	this->timeOff = (period / 2) * multiplier;
	this->timeOn = period / 2;
	this->slowTimeCurrent = this->clock.Get() * 1000;

	if((this->slowTimeCurrent - this->slowTimeLast) >= this->timeOff && this->slowStatus)
	{
		this->instantaneousRotation(0.0);
		this->slowTimeLast = this->slowTimeCurrent;
	}
	else if((this->slowTimeCurrent - this->slowTimeLast) >= this->timeOn && !this->slowStatus)
	{
		this->instantaneousRotation(changeSpeed);
		this->slowTimeLast = this->slowTimeCurrent;
	}
}
