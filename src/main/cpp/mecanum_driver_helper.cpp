#include <string>
#include <cmath>
#include <algorithm>
#include "mecanum_driver_helper.hpp"

BjorgMecanumDrive::BjorgMecanumDrive(
    frc::Spark* frontLeftMotor, 
    frc::Spark* backLeftMotor, 
    frc::Spark* frontRightMotor, 
    frc::Spark* backRightMotor,
    frc::Joystick* moveController, 
    frc::Joystick* shiftController, 
    frc::Joystick* rotateController,
    frc::AnalogGyro* gyroSensor,
    AutoAlignment* autoAlignment
) 
{
    this->robotDrive = new frc::MecanumDrive 
    { 
        *frontLeftMotor, 
        *backLeftMotor, 
        *frontRightMotor, 
        *backRightMotor 
    };
    
    this->driveControllerMove = moveController;
    this->driveControllerShift = shiftController;
    this->driveControllerRotate = rotateController;
    this->gyroSensor = gyroSensor;
    this->autoAlignment = autoAlignment;
    this->robotDrive->SetExpiration(0.1);
}

void BjorgMecanumDrive::mecanumDrive()
{
    this->robotDrive->SetSafetyEnabled(true);
    this->setMovement();

    if(UTILIZE_GYRO)
    {
        this->robotDrive->DriveCartesian(
            this->moveMultiplier * this->movementValue, 
            this->shiftMultiplier * this->shiftValue, 
            this->rotateMultiplier * this->rotateValue,
            this->gyroSensor->GetAngle()
        );
    }
    else
    {
        this->robotDrive->DriveCartesian(
            this->moveMultiplier * this->movementValue,
            this->shiftMultiplier * this->shiftValue,
            this->rotateMultiplier * this->rotateValue
        );
    }
}

void BjorgMecanumDrive::mecanumDrive(double movement, double shift, double rotate)
{
    this->robotDrive->SetSafetyEnabled(true);
    this->robotDrive->DriveCartesian(movement, shift, rotate);
}

void BjorgMecanumDrive::mecanumDriveAutoAlign()
{
    this->autoAlignment->updateVisionProcessing();
    this->autoAlignment->calculateResolution();

    while()
    {

    }
}

void BjorgMecanumDrive::twoBtnMove()
{
    this->movementValue = 
        this->driveControllerMove->GetRawAxis(this->fwdMove) - 
        this->driveControllerMove->GetRawAxis(this->bckMove);
}

void BjorgMecanumDrive::twoBtnShift()
{
    this->shiftValue = 
        this->driveControllerShift->GetRawAxis(this->fwdShift) - 
        this->driveControllerShift->GetRawAxis(this->bckShift);
}

void BjorgMecanumDrive::twoBtnRotate()
{
    this->rotateValue = 
        this->driveControllerRotate->GetRawAxis(this->fwdRotate) - 
        this->driveControllerRotate->GetRawAxis(this->bckRotate);
}
    
void BjorgMecanumDrive::setMovement()
{
    if(this->multiMove)
    {
        this->twoBtnMove();
    }
    else
    {
        this->movementValue = this->driveControllerMove->GetRawAxis(this->moveCtrl);
    }

    if(this->multiShift)
    {
        this->twoBtnShift();
    }
    else
    {
        this->shiftValue = this->driveControllerShift->GetRawAxis(this->shiftCtrl);
    }

    if(this->multiRotate)
    {
        this->twoBtnRotate();
    }
    else
    {
        this->rotateValue = this->driveControllerRotate->GetRawAxis(this->rotateCtrl);
    }
}

void BjorgMecanumDrive::setRotate(bool rotateEn)
{
    if(this->multiRotate)
    {
        this->twoBtnRotate();
    }
    else
    {
        this->rotateValue = rotateEn 
            ? this->driveControllerRotate->GetRawAxis(this->rotateCtrl) 
            : 0;
    }
}
