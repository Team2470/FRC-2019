//*****************************************************************************
// Filename:            mecanum_driver_helper.hpp
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
#include <Drive/DifferentialDrive.h>
#include <Joystick.h>
#include <Spark.h>

// Our Includes //
#include "driver_helper.hpp"

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    BjorgMecanumDrive
 *---------------------------------------------------------------------------*/
BjorgMecanumDrive::BjorgMecanumDrive(frc::Spark *m_frontleftMotor, frc::Spark *m_backleftMotor, frc::Spark *m_frontrightMotor, frc::Spark *m_backrightMotor,
    frc::Joystick *moveController, frc::Joystick *shiftController, frc::Joystick *rotateController)
{
    m_robotDrive = new frc::MecanumDrive { *m_frontleftMotor, *m_backleftMotor, *m_frontrightMotor, *m_backrightMotor };
    driveControllerMove = moveController;
    driveControllerShift = shiftController;
    driveControllerRotation = rotateController;
    m_robotDrive->SetExpiration(0.1);
};


/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    mecanumDrive
 *---------------------------------------------------------------------------*/
void BjorgDrive::mecanumDrive()
{
    m_robotDrive->SetSafetyEnabled(true);

    setMovement();    
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    mecanumDrive
 *---------------------------------------------------------------------------*/
void BjorgDrive::mecanumDrive(double movement, double shift, double rotate)
{
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    twoBtnDrive
 *---------------------------------------------------------------------------*/
void BjorgDrive::twoBtnDrive()
{
    // Combines two inputs into one value
    movementValue = driveController1->GetRawAxis(fwdDrive) - driveController1->GetRawAxis(bckDrive);
}
	
/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    twoBtnRotate
 *---------------------------------------------------------------------------*/
void BjorgDrive::twoBtnRotate()
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
}
    
/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    setMovement
 *---------------------------------------------------------------------------*/
void BjorgDrive::setMovement()
{
    if (multiMove)
    {
        twoBtnDrive();
    }

    else
    {
        movementValue = driveController1->GetRawAxis(moveCtrl);
        shiftValue = 
        rotationValue
    }
};

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    setRotate
 *---------------------------------------------------------------------------*/
void BjorgDrive::setRotate(bool rotateEn)
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
