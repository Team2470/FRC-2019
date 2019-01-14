//*****************************************************************************
// Filename:            tank_driver_helper.cpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2019  Initial design.
//
// Description:
//    This class operates a SpeedController group using Differential Drive.
//    The class has the ability to drive using tele-operated Tank Drive, 
//        autonomous tank drive, and should be updated for other versions of 
//        as needed (tank, H, etc.).
// 
// Dependencies:
//    None
//*****************************************************************************

/******************************************************************************
 * Include Files
 *****************************************************************************/
// System Includes //
#include <string>
#include <cmath>
#include <algorithm>

// FIRST Includes //
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>

// Our Includes //
#include "tank_driver_helper.hpp"

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    BjorgTankDrive
 *---------------------------------------------------------------------------*/
BjorgTankDrive::BjorgTankDrive(frc::Spark *m_leftMotor, frc::Spark *m_rightMotor, 
    frc::Joystick *controllerLeft, frc::Joystick *controllerRight)
{
    m_robotDrive = new frc::DifferentialDrive { *m_leftMotor, *m_rightMotor };
    driveControllerLeft = controllerLeft;
    driveControllerRight = controllerRight;
    m_robotDrive->SetExpiration(0.1);
};


/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    tankDrive
 *---------------------------------------------------------------------------*/
void BjorgTankDrive::tankDrive()
{
    m_robotDrive->SetSafetyEnabled(true);

    setMovement();
    //setRotate(rotateEnable);

    //joystick debounce
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

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    tankDrive
 *---------------------------------------------------------------------------*/
void BjorgTankDrive::tankDrive(double leftMovement, double rightMovement)
{
    m_robotDrive->SetSafetyEnabled(true);
    m_robotDrive->TankDrive(leftMovement, rightMovement);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    twoBtnDriveLeft
 *---------------------------------------------------------------------------*/
void BjorgTankDrive::twoBtnLeft()
{
    // Combines two inputs into one value
    leftValue = driveControllerLeft->GetRawAxis(leftFwd) - driveControllerLeft->GetRawAxis(leftBck);
}
	
/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    twoBtnRight
 *---------------------------------------------------------------------------*/
void BjorgTankDrive::twoBtnRight()
{
    // Combines two inputs into one value
    rightValue = driveControllerRight->GetRawAxis(rightFwd) - driveControllerRight->GetRawAxis(rightBck);
}
    
/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    setMovement
 *---------------------------------------------------------------------------*/
void BjorgArcadeDrive::setMovement()
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
};

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    setRotate
 *---------------------------------------------------------------------------*/
void BjorgTankDrive::setRotate(bool rotateEn)
{
    if (multiRotate)
    {
        twoBtnRotate();
    }

    else
    {
        rotationValue = (rotateEn ? driveController2->GetRawAxis(rotateCtrl) : 0);
    }
};
