//*****************************************************************************
// Filename:            motor_helper.cpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2018  Initial design.
//
// Description:
//    This class operates a PWM Motor such as the following drivers:
//        Spark, Talon, Victor, VictorSP
//    The class has the ability to drive the motor cw and ccw as well as
//        accelerating/decelerating and reading the current speed.
// 
// Dependencies:
//    None
//*****************************************************************************

/******************************************************************************
 * Include Files
 *****************************************************************************/
// System Includes //
#include <math.h>
#include <Timer.h>
#include <iostream>

// FIRST Includes //
#include <frc/Spark.h>
#include <frc/PWMSpeedController.h>
#include <frc/Victor.h>
#include <frc/VictorSP.h>
#include <frc/Talon.h>

// Our Includes //
#include "motor_helper.hpp"

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    Motor
 *---------------------------------------------------------------------------*/
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
};

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    GradualRotation
 *---------------------------------------------------------------------------*/
void Motor::GradualRotation(double motorMaxSpeed,
							double speedIncreaseDuration,
							Behavior_Type newBehavior)
{
	this->gradual_MaxSpeed = motorMaxSpeed;
	accelBehavior = newBehavior;

	if (firstRun) //First time called after ResetAccelerate()
	{
		this->gradual_CurrentSpeed = this->pwmMotor->Get();
		this->speedIncreaseRate = (gradual_MaxSpeed - gradual_CurrentSpeed) /
				(1000 * speedIncreaseDuration);
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

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    InstantaneousRotation
 *---------------------------------------------------------------------------*/
void Motor::InstantaneousRotation(double motorSpeed)
{
	motorState = Constant;
	this->pwmMotor->Set(motorSpeed);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    InstantaneousStop
 *---------------------------------------------------------------------------*/
void Motor::InstantaneousStop()
{
	motorState = Constant;
	this->pwmMotor->Set(0);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    GetSpeed
 *---------------------------------------------------------------------------*/
double Motor::GetSpeed()
{
	return this->pwmMotor->Get();
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    MaintainSpeed
 *---------------------------------------------------------------------------*/
void Motor::MaintainSpeed()
{
	InstantaneousRotation(GetSpeed());
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    ResetAccelerate
 *---------------------------------------------------------------------------*/
void Motor::ResetAccelerate(bool forceReset)
{
	firstRun = ((motorState == Constant || forceReset) ? true : false);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    AccelerateMotor
 *---------------------------------------------------------------------------*/
void Motor::AccelerateMotor()
{
	currentTime = (clock.Get() * 1000);
	if((currentTime - lastTime) >= 1)
	{
		motorState = Accelerate;
		//this->gradual_CurrentSpeed = this->motorSpark->Get();
		this->gradual_CurrentSpeed = this->gradual_CurrentSpeed + speedIncreaseRate;
		//this->gradual_RoundedSpeed = (floor(gradual_CurrentSpeed * 100)/100);

//		std::cout << currentTime << std::endl;

//			SmartDashboard::PutString("DB/String 9", std::to_string(speedIncreaseRate) + " " + std::to_string(gradual_CurrentSpeed));

		this->pwmMotor->Set(gradual_CurrentSpeed);
		this->lastTime = this->currentTime;
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    Brake
 *---------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    SlowSpeed
 *---------------------------------------------------------------------------*/
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
