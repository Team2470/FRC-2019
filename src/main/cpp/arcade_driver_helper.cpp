#include <string>
#include <cmath>
#include <algorithm>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include "arcade_driver_helper.hpp"

BjorgArcadeDrive::BjorgArcadeDrive(
	frc::Spark* leftMotor, 
	frc::Spark* rightMotor, 
    frc::Joystick* controllerMovement,
	frc::Joystick* controllerRotate
)
{
	this->robotDrive = new frc::DifferentialDrive 
    { 
        *leftMotor, 
        *rightMotor 
    };

	this->driveControllerMovement = controllerMovement;
	this->driveControllerRotate = controllerRotate;
	this->robotDrive->SetExpiration(0.1);
}

void BjorgArcadeDrive::arcadeDrive()
{
	this->robotDrive->SetSafetyEnabled(true);
	this->setMovement();
	this->setRotate(rotateEnable);

	if(this->movementValue <= 0.1f && this->movementValue >= -0.1f)
	{
		this->movementValue = 0.0f;
	}

	if(this->rotationValue <= 0.1f && this->rotationValue >= -0.1f)
	{
		this->rotationValue = 0.0f;
	}

	this->robotDrive->ArcadeDrive(
        this->reverseDrive * this->motorMultiplier * this->movementValue, 
        this->rotateMult * this->rotationValue, 
        this->sqrInputs
    );
}

void BjorgArcadeDrive::arcadeDrive(double movement, double rotate)
{
    this->robotDrive->SetSafetyEnabled(true);
    this->robotDrive->ArcadeDrive(movement, rotate, this->sqrInputs);
}

void BjorgArcadeDrive::stop()
{
    this->robotDrive->ArcadeDrive(0, 0, this->sqrInputs);
}

void BjorgArcadeDrive::twoBtnDrive()
{
    this->movementValue = 
        this->driveControllerMovement->GetRawAxis(this->fwdDrive) - 
        this->driveControllerMovement->GetRawAxis(this->bckDrive);
}
	
void BjorgArcadeDrive::twoBtnRotate()
{
	float triggerVal = 0.0;
	float maxVal = 0.0;
	float addVal = 0.0;

    // Combines the trigger values so if the right trigger is pressed the robot 
    // turns right and if the left trigger is pressed the robot turns left.
    triggerVal = 
        this->driveControllerMovement->GetRawAxis(this->lftTurn) - 
        this->driveControllerMovement->GetRawAxis(this->rtTurn);
    	
	// Finds the max value from the combined trigger value and right joystick 
    // x-axis.
    maxVal = std::max(
        double(std::abs(triggerVal)), 
        std::abs(this->driveControllerMovement->GetRawAxis(this->joystickInt))
    );
    
	// Adds the combined trigger value and the right joystick x-axis to find the
    // sign (positive or negative) of the max value.
    addVal = triggerVal + this->driveControllerMovement->GetRawAxis(this->joystickInt);

	// Combines the max value and the add value to decide the rotate value so it
	// turns correctly.
    this->rotationValue = addVal < 0
        ? -1 * maxVal
        : maxVal;
}
    
void BjorgArcadeDrive::setMovement()
{
	if(this->multiMove)
	{
		this->twoBtnDrive();
	}
	else
	{
		this->movementValue = this->driveControllerMovement->GetRawAxis(this->moveCtrl);
	}
}

void BjorgArcadeDrive::setRotate(bool rotateEn)
{
	if(this->multiRotate)
	{
		this->twoBtnRotate();
	}
	else
	{
		this->rotationValue = rotateEn 
            ? this->driveControllerRotate->GetRawAxis(this->rotateCtrl) 
            : 0;
	}
}
