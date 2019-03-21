#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "BjorgMecanumDrive.hpp"

BjorgMecanumDrive::BjorgMecanumDrive(
    frc::SpeedController* frontLeftMotor, 
    frc::SpeedController* backLeftMotor, 
    frc::SpeedController* frontRightMotor, 
    frc::SpeedController* backRightMotor,
    frc::Joystick* moveController, 
    frc::Joystick* shiftController, 
    frc::Joystick* rotateController,
    frc::ADXRS450_Gyro* gyroSensor,
    AutoAlignment* autoAlignment
) 
{
    m_robotDrive = new frc::MecanumDrive(*frontLeftMotor, *backLeftMotor, *frontRightMotor, *backRightMotor );
    
    this->driveControllerMove = moveController;
    this->driveControllerShift = shiftController;
    this->driveControllerRotate = rotateController;
    
    m_gyroSensor = gyroSensor;
    m_autoAlignment = autoAlignment;
    m_robotDrive->SetExpiration(0.1);
}

void BjorgMecanumDrive::mecanumDrive()
{
    m_robotDrive->SetSafetyEnabled(true);
    setMovement();

    this->movementValue = this->movementValue <= DEADZONE && this->movementValue >= -DEADZONE
        ? 0.0
        : this->movementValue;

    this->shiftValue = this->shiftValue <= DEADZONE && this->shiftValue >= -DEADZONE
        ? 0.0
        : this->shiftValue;

    this->rotateValue = this->rotateValue <= DEADZONE && this->rotateValue >= -DEADZONE
        ? 0.0
        : this->rotateValue;

    if(UTILIZE_GYRO)
    {
        m_robotDrive->DriveCartesian(
            moveMultiplier * movementValue,
            shiftMultiplier * shiftValue, 
            rotateMultiplier * rotateValue,
            m_gyroSensor->GetAngle()
        );
    }
    else
    {
        std::cout << disableShift * moveMultiplier * movementValue << " : " \
                  <<  disableMove * shiftMultiplier * shiftValue << " : " \
                  << rotateMultiplier * rotateValue << std::endl;

        m_robotDrive->DriveCartesian(
            disableShift * moveMultiplier * movementValue,
            disableMove * shiftMultiplier * shiftValue,
            rotateMultiplier * rotateValue
        );
    }
}

void BjorgMecanumDrive::mecanumDrive(double movement, double shift, double rotate)
{
    m_robotDrive->SetSafetyEnabled(true);
    m_robotDrive->DriveCartesian(movement, shift, rotate);
}

void BjorgMecanumDrive::mecanumDriveAutoAlign()
{
    double xSpeed = 0.0;
    double ySpeed =  0.0;
    double rotation = 0.0;

    // ySpeed =  speedLimiter(m_autoAlignment->getMoveCorrection());
    // xSpeed = speedLimiter(m_autoAlignment->getShiftCorrection());
    rotation =  speedLimiter(m_autoAlignment->getRotateCorrection());

    // rotation = 0.23;
    // rotation = 0.0;

    m_robotDrive->SetSafetyEnabled(true);
    // m_robotDrive->SetSafetyEnabled(false);
    m_robotDrive->DriveCartesian( ySpeed, xSpeed, rotation);
    // m_robotDrive->DriveCartesian( 0, 0, 0);
    std::cout << std::endl;
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


double BjorgMecanumDrive::speedLimiter( double speed )
{
    return speedLimiter( speed, MAX_SPEED );
}


double BjorgMecanumDrive::speedLimiter( double speed, double max )
{
    int sign = 1;
    if ( speed < 0 )
    {
        sign = -1;
    }

    if ( abs(speed) > max )
    {    
        speed = max;
    }
    return speed * sign;
}