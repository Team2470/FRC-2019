#include <string>
#include <cmath>
#include <algorithm>
#include "mecanum_driver_helper.hpp"

BjorgMecanumDrive::BjorgMecanumDrive(
    frc::SpeedController* frontLeftMotor, 
    frc::SpeedController* backLeftMotor, 
    frc::SpeedController* frontRightMotor, 
    frc::SpeedController* backRightMotor,
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
    if(!this->resolutionNeeded)
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
                -1 * this->moveMultiplier * this->movementValue,
                -1 * this->shiftMultiplier * this->shiftValue,
                this->rotateMultiplier * this->rotateValue
            );
        }
    }
}

void BjorgMecanumDrive::mecanumDrive(double movement, double shift, double rotate)
{
    this->robotDrive->SetSafetyEnabled(true);
    this->robotDrive->DriveCartesian(movement, shift, rotate);
}

void BjorgMecanumDrive::mecanumDriveAutoAlign()
{
    if(this->resolutionNeeded)
    {
        this->autoAlignment->updateVisionProcessing();
        this->autoAlignment->calculateResolution();

        double averageEncoderValue = (
            this->encoderFrontLeft->getDistance() +
            this->encoderFrontRight->getDistance() +
            this->encoderBackLeft->getDistance() +
            this->encoderBackRight->getDistance()
        ) / 4.0; 

        this->distanceResolved = averageEncoderValue < this->autoAlignment->distanceToResolve;
        this->rotationResolved = 
            (this->gyroSensor->GetAngle() > 89.5 && this->gyroSensor->GetAngle() < 90.5) || 
            (this->gyroSensor->GetAngle() > 269.5 && this->gyroSensor->GetAngle() < 270.5); // TODO: Set appropriate threshold?

        if(!this->rotationResolved)
        {
            this->robotDrive->SetSafetyEnabled(true);
            this->robotDrive->DriveCartesian(0.0, 0.0, 1.0, this->gyroSensor->GetAngle()); // TODO: Figure appropriate rotation value?
        }

        if(this->rotationResolved && !this->distanceResolved)
        {
            double xSpeed = this->autoAlignment->distanceToResolveParallel / fabs(this->autoAlignment->distanceToResolveParallel);
            double ySpeed = this->autoAlignment->distanceToResolvePerpendicular / fabs(this->autoAlignment->distanceToResolvePerpendicular);
            
            this->robotDrive->SetSafetyEnabled(true);
            this->robotDrive->DriveCartesian(ySpeed, xSpeed, 0.0, this->gyroSensor->GetAngle());
        }

        this->resolutionNeeded = !(this->distanceResolved && this->rotationResolved);
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
