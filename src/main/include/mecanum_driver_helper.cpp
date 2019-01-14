//*****************************************************************************
// Filename:            mecanum_driver_helper.cpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2019  Initial design.
//
// Description:
//    This class operates a SpeedController group using Mecanum Drive.
//    The class has the ability to drive using mecanum wheels.
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
#include "mecanum_driver_helper.hpp"

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    BjorgMecanumDrive
 *---------------------------------------------------------------------------*/
BjorgMecanumDrive::BjorgMecanumDrive(frc::Spark *m_frontleftMotor, frc::Spark *m_backleftMotor, frc::Spark *m_frontrightMotor, frc::Spark *m_backrightMotor,
    frc::Joystick *moveController, frc::Joystick *shiftController, frc::Joystick *rotateController)
{
    m_robotDrive = new frc::MecanumDrive { *m_frontleftMotor, *m_backleftMotor, *m_frontrightMotor, *m_backrightMotor };
    driveControllerMove = moveController;
    driveControllerShift = shiftController;
    driveControllerRotate = rotateController;
    m_robotDrive->SetExpiration(0.1);
};


/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    mecanumDrive
 *---------------------------------------------------------------------------*/
void BjorgMecanumDrive::mecanumDrive()
{
    m_robotDrive->SetSafetyEnabled(true);

    setMovement();

    m_robotDrive->DriveCartesian(moveMultiplier * movementValue, shiftMultiplier * shiftValue, rotateMultiplier * rotateValue);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    mecanumDrive
 *---------------------------------------------------------------------------*/
void BjorgMecanumDrive::mecanumDrive(double movement, double shift, double rotate)
{
    m_robotDrive->SetSafetyEnabled(true);

    m_robotDrive->DriveCartesian(movement, shift, rotate);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    twoBtnMove
 *---------------------------------------------------------------------------*/
void BjorgMecanumDrive::twoBtnMove()
{
    // Combines two inputs into one value
    movementValue = driveControllerMove->GetRawAxis(fwdMove) - driveControllerMove->GetRawAxis(bckMove);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    twoBtnShift
 *---------------------------------------------------------------------------*/
void BjorgMecanumDrive::twoBtnShift()
{
    // Combines two inputs into one value
    shiftValue = driveControllerShift->GetRawAxis(fwdShift) - driveControllerShift->GetRawAxis(bckShift);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    twoBtnRotate
 *---------------------------------------------------------------------------*/
void BjorgMecanumDrive::twoBtnRotate()
{
    // Combines two inputs into one value
    rotateValue = driveControllerRotate->GetRawAxis(fwdRotate) - driveControllerRotate->GetRawAxis(bckRotate);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    twoBtnRotateOLD
 *---------------------------------------------------------------------------*/
/*void BjorgMecanumDrive::twoBtnRotate()
{
    float triggerVal = 0.0;
    float maxVal = 0.0;
    float addVal = 0.0;

    //Combines the trigger values so if the right trigger is pressed the robot 
    //turns right and if the left trigger is pressed the robot turns left
    triggerVal = driveController1->GetRawAxis(lftTurn) -
        driveController1->GetRawAxis(rtTurn);
    //Finds the max value from the combined trigger value and right joystick 
    //x-axis
    maxVal = std::max(double(std::abs(triggerVal)), std::abs(driveController1->GetRawAxis(joystickInt)));
    //Adds the combined trigger value and the right joystick x-axis to find the
    //sign (positive or negative) of the max value
    addVal = triggerVal + driveController1->GetRawAxis(joystickInt);

    //Combines the max value and the add value to decide the rotate value so it
    //turns correctly
    if (addVal < 0)
    {
        rotationValue = -1 * maxVal;
    }
    else
    {
        rotationValue = maxVal;
    }
}*/
    
/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    setMovement
 *---------------------------------------------------------------------------*/
void BjorgMecanumDrive::setMovement()
{
    if (multiMove)
    {
        twoBtnMove();
    }
    else
    {
        movementValue = driveControllerMove->GetRawAxis(moveCtrl);
    }

    if (multiShift)
    {
        twoBtnShift();
    }
    else
    {
        shiftValue = driveControllerShift->GetRawAxis(shiftCtrl);
    }
    
    if (multiRotate)
    {
        twoBtnRotate();
    }
    else
    {
        rotateValue = driveControllerRotate->GetRawAxis(rotateCtrl);
    }
};

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    setRotate
 *---------------------------------------------------------------------------*/
void BjorgMecanumDrive::setRotate(bool rotateEn)
{
    if (multiRotate)
    {
        //twoBtnRotate();
    }

    else
    {
        //rotationValue = (rotateEn ? driveController2->GetRawAxis(rotateCtrl) : 0);
    }
};