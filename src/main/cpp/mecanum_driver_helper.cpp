#include <string>
#include <cmath>
#include <algorithm>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include "mecanum_driver_helper.hpp"

BjorgMecanumDrive::BjorgMecanumDrive(
    frc::Spark* frontLeftMotor, 
    frc::Spark* backLeftMotor, 
    frc::Spark* frontRightMotor, 
    frc::Spark* backRightMotor,
    frc::Joystick* moveController, 
    frc::Joystick* shiftController, 
    frc::Joystick* rotateController
)
{
    robotDrive = new frc::MecanumDrive 
    { 
        *frontLeftMotor, 
        *backLeftMotor, 
        *frontRightMotor, 
        *backRightMotor 
    };
    
    driveControllerMove = moveController;
    driveControllerShift = shiftController;
    driveControllerRotate = rotateController;
    robotDrive->SetExpiration(0.1);
}

void BjorgMecanumDrive::mecanumDrive()
{
    robotDrive->SetSafetyEnabled(true);
    setMovement();
    robotDrive->DriveCartesian(moveMultiplier * movementValue, shiftMultiplier * shiftValue, rotateMultiplier * rotateValue);
}

void BjorgMecanumDrive::mecanumDrive(double movement, double shift, double rotate)
{
    robotDrive->SetSafetyEnabled(true);
    robotDrive->DriveCartesian(movement, shift, rotate);
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
        twoBtnRotate();
    }
    else
    {
        rotateValue = rotateEn 
            ? driveControllerRotate->GetRawAxis(rotateCtrl) 
            : 0;
    }
}
