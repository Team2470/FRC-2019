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
	firstRun = true;
	accelBehavior = Maintain;
	motorState = Constant;
	motorFamily = motorType;
	clock.Start();
	
	switch(motorFamily)
	{
		case TALON:
			motorTalon = new frc::Talon(motorChannel);
			pwmMotor = motorTalon;
			break;

		case VICTOR:
			motorVictor = new frc::Victor(motorChannel);
			pwmMotor = motorVictor;
			break;

		case VICTOR_SP:
			motorVictorSP = new frc::VictorSP(motorChannel);
			pwmMotor = motorVictorSP;
			break;

		case SPARK:
			motorSpark = new frc::Spark(motorChannel);
			pwmMotor = motorSpark;
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
	accelBehavior = newBehavior;

	if(firstRun)
	{
		this->gradualCurrentSpeed = this->pwmMotor->Get();
		this->speedIncreaseRate = (gradualMaxSpeed - gradualCurrentSpeed) / (1000 * speedIncreaseDuration);
		firstRun = false;
		lastTime = 0;
	}

    testSpeed = speedIncreaseRate >= 0 
        ? 1 
        : -1;

	if((gradualCurrentSpeed * testSpeed) >= fabs(gradualMaxSpeed))
	{
		instantaneousRotation(accelBehavior ? gradualMaxSpeed : 0);
	}
	else
	{
		accelerateMotor();
	}
}

void Motor::instantaneousRotation(double motorSpeed)
{
	motorState = Constant;
	this->pwmMotor->Set(motorSpeed);
}

void Motor::instantaneousStop()
{
	motorState = Constant;
	this->pwmMotor->Set(0);
}

double Motor::getSpeed()
{
	return this->pwmMotor->Get();
}

void Motor::maintainSpeed()
{
	instantaneousRotation(getSpeed());
}

void Motor::resetAccelerate(bool forceReset)
{
	firstRun = (motorState == Constant || forceReset) 
        ? true 
        : false;
}

void Motor::accelerateMotor()
{
	currentTime = (clock.Get() * 1000);
	if((currentTime - lastTime) >= 1)
	{
		motorState = Accelerate;
		//this->gradualCurrentSpeed = this->motorSpark->Get();
		this->gradualCurrentSpeed = this->gradualCurrentSpeed + speedIncreaseRate;
		//this->gradualRoundedSpeed = (floor(gradualCurrentSpeed * 100)/100);
		//std::cout << currentTime << std::endl;
		//SmartDashboard::PutString("DB/String 9", std::to_string(speedIncreaseRate) + " " + std::to_string(gradualCurrentSpeed));
		this->pwmMotor->Set(gradualCurrentSpeed);
		this->lastTime = this->currentTime;
	}
}

void Motor::brake()
{
	brakeTimeCurrent = (clock.Get() * 1000);
	if((brakeTimeCurrent - brakeTimeLast) >= 5)
	{
		instantaneousRotation(brakeMotorSpeed);
		brakeMotorSpeed = -brakeMotorSpeed;
		brakeTimeLast = brakeTimeCurrent;
	}
}

void Motor::slowSpeed(double period, double changeSpeed, double multiplier)
{
	timeOff = ((period / 2) * multiplier);
	timeOn = (period / 2);
	slowTimeCurrent = (clock.Get() * 1000);

	if((slowTimeCurrent - slowTimeLast) >= timeOff && slowStatus)
	{
		instantaneousRotation(0.0);
		slowTimeLast = slowTimeCurrent;
	}
	else if((slowTimeCurrent - slowTimeLast) >= timeOn && !slowStatus)
	{
		instantaneousRotation(changeSpeed);
		slowTimeLast = slowTimeCurrent;
	}
}
