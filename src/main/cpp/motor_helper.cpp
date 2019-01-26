#include <math.h>
#include <frc/Timer.h>
#include <iostream>
#include <frc/Spark.h>
#include <frc/PWMSpeedController.h>
#include <frc/Victor.h>
#include <frc/VictorSP.h>
#include <frc/Talon.h>
#include "motor_helper.hpp"

Motor::Motor(int motorChannel, Motor_Type motorType)
{
	firstRun = true;
	accelBehavior = Maintain;
	motorState = Constant;
	motorFamily = motorType;
	clock.Start();
	
	switch(motorFamily)
	{
		case TALON :
			motorTalon = new frc::Talon(motorChannel);
			pwmMotor = motorTalon;
			break;

		case VICTOR :
			motorVictor = new frc::Victor(motorChannel);
			pwmMotor = motorVictor;
			break;

		case VICTOR_SP :
			motorVictorSP = new frc::VictorSP(motorChannel);
			pwmMotor = motorVictorSP;
			break;

		case SPARK :
			motorSpark = new frc::Spark(motorChannel);
			pwmMotor = motorSpark;
			break;

		default :
			break;
	}
}

void Motor::GradualRotation(
	double motorMaxSpeed,
	double speedIncreaseDuration,
	Behavior_Type newBehavior
)
{
	this->gradual_MaxSpeed = motorMaxSpeed;
	accelBehavior = newBehavior;

	if (firstRun)
	{
		this->gradual_CurrentSpeed = this->pwmMotor->Get();
		this->speedIncreaseRate = (gradual_MaxSpeed - gradual_CurrentSpeed) / (1000 * speedIncreaseDuration);
		firstRun = false;
		lastTime = 0;
	}
	if (speedIncreaseRate >= 0)
	{
		testSpeed = 1;
	}
	else
	{
		testSpeed = -1;
	}

	if ((gradual_CurrentSpeed * testSpeed) >= fabs(gradual_MaxSpeed))
	{
		InstantaneousRotation(accelBehavior ? gradual_MaxSpeed : 0);
	}
	else
	{
		AccelerateMotor();
	}

}

void Motor::InstantaneousRotation(double motorSpeed)
{
	motorState = Constant;
	this->pwmMotor->Set(motorSpeed);
}

void Motor::InstantaneousStop()
{
	motorState = Constant;
	this->pwmMotor->Set(0);
}

double Motor::GetSpeed()
{
	return this->pwmMotor->Get();
}

void Motor::MaintainSpeed()
{
	InstantaneousRotation(GetSpeed());
}

void Motor::ResetAccelerate(bool forceReset)
{
	firstRun = ((motorState == Constant || forceReset) ? true : false);
}

void Motor::AccelerateMotor()
{
	currentTime = (clock.Get() * 1000);
	if((currentTime - lastTime) >= 1)
	{
		motorState = Accelerate;
		//this->gradual_CurrentSpeed = this->motorSpark->Get();
		this->gradual_CurrentSpeed = this->gradual_CurrentSpeed + speedIncreaseRate;
		//this->gradual_RoundedSpeed = (floor(gradual_CurrentSpeed * 100)/100);
		//std::cout << currentTime << std::endl;
		//SmartDashboard::PutString("DB/String 9", std::to_string(speedIncreaseRate) + " " + std::to_string(gradual_CurrentSpeed));
		this->pwmMotor->Set(gradual_CurrentSpeed);
		this->lastTime = this->currentTime;
	}
}

void Motor::Brake()
{
	brakeTimeCurrent = (clock.Get() * 1000);
	if ((brakeTimeCurrent - brakeTimeLast) >= 5)
	{
		InstantaneousRotation(brakeMotorSpeed);
		brakeMotorSpeed = -brakeMotorSpeed;
		brakeTimeLast = brakeTimeCurrent;
	}
}

void Motor::SlowSpeed(double period, double changeSpeed, double multiplier)
{
	timeOff = ((period / 2) * multiplier);
	timeOn = (period / 2);
	slowTimeCurrent = (clock.Get() * 1000);

	if ((slowTimeCurrent - slowTimeLast) >= timeOff && slowStatus)
	{
		InstantaneousRotation(0.0);
		slowTimeLast = slowTimeCurrent;
	}
	else if ((slowTimeCurrent - slowTimeLast) >= timeOn && !slowStatus)
	{
		InstantaneousRotation(changeSpeed);
		slowTimeLast = slowTimeCurrent;
	}
}
