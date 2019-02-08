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
	this->robotDrive = new frc::DifferentialDrive 
    { 
        *leftMotor, 
        *rightMotor 
    };

	this->driveControllerLeft = controllerLeft;
	this->driveControllerRight = controllerRight;
	this->robotDrive->SetExpiration(0.1);
}

void BjorgTankDrive::tankDrive()
{
	this->robotDrive->SetSafetyEnabled(true);
	this->setMovement();

	if(this->leftValue <= 0.1f && this->leftValue >= -0.1f)
	{
		this->leftValue = 0.0f;
	}

	if(this->rightValue <= 0.1f && this->rightValue >= -0.1f)
	{
		this->rightValue = 0.0f;
	}

	this->robotDrive->TankDrive(
        this->leftReverse * this->leftMultiplier * this->leftValue, 
        this->rightReverse * this->rightMultiplier * this->rightValue, 
        this->sqrInputs
    );
}

void BjorgTankDrive::tankDrive(double leftMovement, double rightMovement)
{
	this->robotDrive->SetSafetyEnabled(true);
	this->robotDrive->TankDrive(leftMovement, rightMovement);
}

void BjorgTankDrive::twoBtnLeft()
{
	this->leftValue = 
        this->driveControllerLeft->GetRawAxis(this->leftFwd) - 
        this->driveControllerLeft->GetRawAxis(this->leftBck);
}
	
void BjorgTankDrive::twoBtnRight()
{
	this->rightValue = 
        this->driveControllerRight->GetRawAxis(this->rightFwd) - 
        this->driveControllerRight->GetRawAxis(this->rightBck);
}
    
void BjorgTankDrive::setMovement()
{
	if(this->multiLeft)
	{
		this->twoBtnLeft();
	}
	else
	{
		this->leftValue = this->driveControllerLeft->GetRawAxis(this->leftCtrl);
	}

	if(this->multiRight)
	{
		this->twoBtnRight();
	}
	else
	{
		this->rightValue = this->driveControllerRight->GetRawAxis(this->rightCtrl);
	}
}
