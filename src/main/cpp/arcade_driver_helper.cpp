#include <string>
#include <cmath>
#include <algorithm>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include "arcade_driver_helper.hpp"

BjorgArcadeDrive::BjorgArcadeDrive(
	frc::Spark* m_leftMotor, 
	frc::Spark* m_rightMotor, 
    	frc::Joystick* controllerMovement,
	frc::Joystick* controllerRotate
)
{
	m_robotDrive = new frc::DifferentialDrive { *m_leftMotor, *m_rightMotor };
	driveControllerMovement = controllerMovement;
	driveControllerRotate = controllerRotate;
	m_robotDrive->SetExpiration(0.1);
}

void BjorgArcadeDrive::arcadeDrive()
{
	m_robotDrive->SetSafetyEnabled(true);
	setMovement();
	setRotate(rotateEnable);

	if(movementValue <= 0.1f && movementValue >= -0.1f)
	{
		movementValue = 0.0f;
	}

	if(rotationValue <= 0.1f && rotationValue >= -0.1f)
	{
		rotationValue = 0.0f;
	}

	m_robotDrive->ArcadeDrive(reverseDrive * motorMultiplier * movementValue, rotateMult * rotationValue, sqrInputs);
}

void BjorgArcadeDrive::arcadeDrive(double movement, double rotate)
{
    	m_robotDrive->SetSafetyEnabled(true);
    	m_robotDrive->ArcadeDrive(movement, rotate, sqrInputs);
}

void BjorgArcadeDrive::stop()
{
    	m_robotDrive->ArcadeDrive(0, 0, sqrInputs);
}

void BjorgArcadeDrive::twoBtnDrive()
{
    	movementValue = driveControllerMovement->GetRawAxis(fwdDrive) - driveControllerMovement->GetRawAxis(bckDrive);
}
	
void BjorgArcadeDrive::twoBtnRotate()
{
	float triggerVal = 0.0;
	float maxVal = 0.0;
	float addVal = 0.0;

    	// Combines the trigger values so if the right trigger is pressed the robot 
    	// turns right and if the left trigger is pressed the robot turns left.
    	triggerVal = driveControllerMovement->GetRawAxis(lftTurn) - driveControllerMovement->GetRawAxis(rtTurn);
    	
	// Finds the max value from the combined trigger value and right joystick 
    	// x-axis.
    	maxVal = std::max(double(std::abs(triggerVal)), std::abs(driveControllerMovement->GetRawAxis(joystickInt)));
    
	// Adds the combined trigger value and the right joystick x-axis to find the
    	// sign (positive or negative) of the max value.
    	addVal = triggerVal + driveControllerMovement->GetRawAxis(joystickInt);

	// Combines the max value and the add value to decide the rotate value so it
	// turns correctly.
	if (addVal < 0)
	{
		rotationValue = -1 * maxVal;
	}
	else
	{
		rotationValue = maxVal;
	}
}
    
void BjorgArcadeDrive::setMovement()
{
	if (multiMove)
	{
		twoBtnDrive();
	}

	else
	{
		movementValue = driveControllerMovement->GetRawAxis(moveCtrl);
	}
}

void BjorgArcadeDrive::setRotate(bool rotateEn)
{
	if (multiRotate)
	{
		twoBtnRotate();
	}

	else
	{
		rotationValue = (rotateEn ? driveControllerRotate->GetRawAxis(rotateCtrl) : 0);
	}
}
