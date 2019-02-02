#include <string>
#include <cmath>
#include <algorithm>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include "tank_driver_helper.hpp"

BjorgTankDrive::BjorgTankDrive(
	frc::Spark* leftMotor, 
	frc::Spark* rightMotor, 
	frc::Joystick* controllerLeft, 
	frc::Joystick* controllerRight
)
{
	robotDrive = new frc::DifferentialDrive 
    { 
        *leftMotor, 
        *rightMotor 
    };

	driveControllerLeft = controllerLeft;
	driveControllerRight = controllerRight;
	robotDrive->SetExpiration(0.1);
}

void BjorgTankDrive::tankDrive()
{
	robotDrive->SetSafetyEnabled(true);
	setMovement();

	if(leftValue <= 0.1f && leftValue >= -0.1f)
	{
		leftValue = 0.0f;
	}

	if(rightValue <= 0.1f && rightValue >= -0.1f)
	{
		rightValue = 0.0f;
	}

	robotDrive->TankDrive(leftReverse * leftMultiplier * leftValue, rightReverse * rightMultiplier * rightValue, sqrInputs);
}

void BjorgTankDrive::tankDrive(double leftMovement, double rightMovement)
{
	robotDrive->SetSafetyEnabled(true);
	robotDrive->TankDrive(leftMovement, rightMovement);
}

void BjorgTankDrive::twoBtnLeft()
{
	leftValue = driveControllerLeft->GetRawAxis(leftFwd) - driveControllerLeft->GetRawAxis(leftBck);
}
	
void BjorgTankDrive::twoBtnRight()
{
	rightValue = driveControllerRight->GetRawAxis(rightFwd) - driveControllerRight->GetRawAxis(rightBck);
}
    
void BjorgTankDrive::setMovement()
{
	if(multiLeft)
	{
		twoBtnLeft();
	}
	else
	{
		leftValue = driveControllerLeft->GetRawAxis(leftCtrl);
	}

	if(multiRight)
	{
		twoBtnRight();
	}
	else
	{
		rightValue = driveControllerRight->GetRawAxis(rightCtrl);
	}
}
