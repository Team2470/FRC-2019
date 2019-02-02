#include <string>
#include <cmath>
#include <algorithm>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include "mecanum_driver_helper.hpp"

BjorgMecanumDrive::BjorgMecanumDrive(
    frc::Spark* m_frontleftMotor, 
    frc::Spark* m_backleftMotor, 
    frc::Spark* m_frontrightMotor, 
    frc::Spark* m_backrightMotor,
    frc::Joystick* moveController, 
    frc::Joystick* shiftController, 
    frc::Joystick* rotateController
)
{
    m_robotDrive = new frc::MecanumDrive 
    { 
        *m_frontleftMotor, 
        *m_backleftMotor, 
        *m_frontrightMotor, 
        *m_backrightMotor 
    };
    
    driveControllerMove = moveController;
    driveControllerShift = shiftController;
    driveControllerRotate = rotateController;
    m_robotDrive->SetExpiration(0.1);
}

void BjorgMecanumDrive::mecanumDrive()
{
    m_robotDrive->SetSafetyEnabled(true);
    setMovement();
    m_robotDrive->DriveCartesian(moveMultiplier * movementValue, shiftMultiplier * shiftValue, rotateMultiplier * rotateValue);
}

void BjorgMecanumDrive::mecanumDrive(double movement, double shift, double rotate)
{
    m_robotDrive->SetSafetyEnabled(true);
    m_robotDrive->DriveCartesian(movement, shift, rotate);
}

void BjorgMecanumDrive::mecanumDriveAutoAlign()
{
    
}

void BjorgMecanumDrive::twoBtnMove()
{
    movementValue = driveControllerMove->GetRawAxis(fwdMove) - driveControllerMove->GetRawAxis(bckMove);
}

void BjorgMecanumDrive::twoBtnShift()
{
    shiftValue = driveControllerShift->GetRawAxis(fwdShift) - driveControllerShift->GetRawAxis(bckShift);
}

void BjorgMecanumDrive::twoBtnRotate()
{
    rotateValue = driveControllerRotate->GetRawAxis(fwdRotate) - driveControllerRotate->GetRawAxis(bckRotate);
}
    
void BjorgMecanumDrive::setMovement()
{
    if(multiMove)
    {
        twoBtnMove();
    }
    else
    {
        movementValue = driveControllerMove->GetRawAxis(moveCtrl);
    }

    if(multiShift)
    {
        twoBtnShift();
    }
    else
    {
        shiftValue = driveControllerShift->GetRawAxis(shiftCtrl);
    }

    if(multiRotate)
    {
        twoBtnRotate();
    }
    else
    {
        rotateValue = driveControllerRotate->GetRawAxis(rotateCtrl);
    }
}

void BjorgMecanumDrive::setRotate(bool rotateEn)
{
    if(multiRotate)
    {
        //twoBtnRotate();
    }
    else
    {
        //rotationValue = (rotateEn ? driveController2->GetRawAxis(rotateCtrl) : 0);
    }
}
