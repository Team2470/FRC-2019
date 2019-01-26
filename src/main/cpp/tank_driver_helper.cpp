#include <string>
#include <cmath>
#include <algorithm>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include "tank_driver_helper.hpp"

BjorgTankDrive::BjorgTankDrive(
	frc::Spark* m_leftMotor, 
	frc::Spark* m_rightMotor, 
	frc::Joystick* controllerLeft, 
	frc::Joystick* controllerRight
)
{
	m_robotDrive = new frc::DifferentialDrive { *m_leftMotor, *m_rightMotor };
	driveControllerLeft = controllerLeft;
	driveControllerRight = controllerRight;
	m_robotDrive->SetExpiration(0.1);
}

void BjorgTankDrive::tankDrive()
{
	m_robotDrive->SetSafetyEnabled(true);
	setMovement();
	//setRotate(rotateEnable);

	if(leftValue <= 0.1f && leftValue >= -0.1f)
	{
		leftValue = 0.0f;
	}

	if(rightValue <= 0.1f && rightValue >= -0.1f)
	{
		rightValue = 0.0f;
	}

	m_robotDrive->TankDrive(leftReverse * leftMultiplier * leftValue, rightReverse * rightMultiplier * rightValue, sqrInputs);
}

void BjorgTankDrive::tankDrive(double leftMovement, double rightMovement)
{
	m_robotDrive->SetSafetyEnabled(true);
	m_robotDrive->TankDrive(leftMovement, rightMovement);
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
	if (multiLeft)
	{
		twoBtnLeft();
	}
	else
	{
		leftValue = driveControllerLeft->GetRawAxis(leftCtrl);
	}

	if (multiRight)
	{
		twoBtnRight();
	}
	else
	{
		rightValue = driveControllerRight->GetRawAxis(rightCtrl);
	}
}
