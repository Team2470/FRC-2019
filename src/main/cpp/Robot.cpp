#include <iostream>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"

Robot::Robot()
{
    // Note SmartDashboard is not initialized here, wait until RobotInit() to make
    // SmartDashboard calls
    //robotDrive.SetExpiration(0.1);
}

void Robot::RobotInit()
{
    //prefs = Preferences::GetInstance();
    chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
    chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
    //chooser.AddOption();
    frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

void Robot::Autonomous() 
{
    std::string autoSelected = chooser.GetSelected();
    // std::string autoSelected = frc::SmartDashboard::GetString(
    // "Auto Selector", kAutoNameDefault);
    std::cout << "Auto selected: " << autoSelected << std::endl;
}

/**
 * Runs the motors with arcade steering.
 */
void Robot::OperatorControl() 
{
    // Drive system variables
    driveSystem->moveCtrl = AxisXbox::XBOX_RIGHT_JOYSTICK_Y;
    driveSystem->shiftCtrl = AxisXbox::XBOX_RIGHT_JOYSTICK_X;
    driveSystem->rotateCtrl = AxisXbox::XBOX_LEFT_JOYSTICK_X;
    driveSystem->multiMove = false;
    driveSystem->multiShift = false;
    driveSystem->multiRotate = false;

    // Intake system variables
    //m_intakeSystem->moveCtrl = FlightJoystick.GetYChannel();
    //m_intakeSystem->multiMove = false;
    //m_intakeSystem->multiRotate = false;
    //m_intakeSystem->rotateEnable = false;
    //m_intakeSystem->reverseDrive = -1;

    while (IsOperatorControl() && IsEnabled())
    {
        //PDP
        inputVoltage = pdp->GetVoltage();
        totalCurrent = pdp->GetTotalCurrent();
        temp = pdp->GetTemperature();
        totalEnergy = pdp->GetTotalEnergy();
        totalPower = pdp->GetTotalPower();

        //Compressor
        compressorCurrent = compressor->getCurrent();
        compressorEnabled = compressor->getVal();

        //Sensor
        //hatchReady = ultrasonicHatch->sonarRange() <= HATCH_DISTANCE;

        //Drive
        moveJoyVal = RightDriveJoystick.GetY();
        shiftJoyVal = RightDriveJoystick.GetX();
        rotateJoyVal = LeftDriveJoystick.GetX();

        currentFrontLeft = pdp->GetCurrent(ChannelPDP::PDP_FRONT_LEFT_MOTOR);
        currentBackLeft = pdp->GetCurrent(ChannelPDP::PDP_BACK_LEFT_MOTOR);
        currentFrontRight = pdp->GetCurrent(ChannelPDP::PDP_FRONT_RIGHT_MOTOR);
        currentBackRight = pdp->GetCurrent(ChannelPDP::PDP_BACK_RIGHT_MOTOR);
        currentIntakeLeft = pdp->GetCurrent(ChannelPDP::PDP_INTAKE_LEFT_MOTOR);
        currentIntakeRight = pdp->GetCurrent(ChannelPDP::PDP_INTAKE_RIGHT_MOTOR);

        //Camera
        currentLimelight = pdp->GetCurrent(ChannelPDP::PDP_LIMELIGHT_CAMERA);

        if(LeftButtonHub.GetRawButton(GenericControllerLeft::SWITCH_A))
        {
            driveSystem->moveMultiplier = 0.5;
            driveSystem->shiftMultiplier = 0.5;
            driveSystem->rotateMultiplier = 0.5;
            std::string autoSelected = chooser.GetSelected();

            if(autoSelected == kAutoNameCustom) 
            {
                // Custom Auto goes here
                std::cout << "Running custom Autonomous" << std::endl;

                // Spin at half speed for two seconds
                //robotDrive.ArcadeDrive(0.0, 0.5);
                frc::Wait(2.0);

                // Stop robot
                //robotDrive.ArcadeDrive(0.0, 0.0);
            } 
            else 
            {
                // Default Auto goes here
                std::cout << "Running default Autonomous" << std::endl;

                // Drive forwards at half speed for two seconds
                //robotDrive.ArcadeDrive(-0.5, 0.0);
                frc::Wait(2.0);

                if(XboxController.GetRawButton(ButtonXbox::XBOX_X))
                {
                    compressor->toggleCompressor();
                }
            }

            // Driver Station
            // PDP stuff
            frc::SmartDashboard::PutNumber("InputVoltage", inputVoltage);
            frc::SmartDashboard::PutNumber("TotalCurrent", totalCurrent);
            frc::SmartDashboard::PutNumber("Temperature", temp);
            frc::SmartDashboard::PutNumber("TotalEnergy", totalEnergy);
            frc::SmartDashboard::PutNumber("TotalPower", totalPower);

            // Compressor stuff
            frc::SmartDashboard::PutNumber("CompressorCurrent", compressorCurrent);
            frc::SmartDashboard::PutBoolean("Compressor Enabled", compressorEnabled);

            // Sensor Stuff
            frc::SmartDashboard::PutBoolean("Hatch Ready", hatchReady);

            // Drive stuff
            frc::SmartDashboard::PutBoolean("HalfSpeed", halfSpeed);
            frc::SmartDashboard::PutBoolean("StopDrive", stopDrive);
            frc::SmartDashboard::PutNumber("MoveJoy", moveJoyVal);
            frc::SmartDashboard::PutNumber("ShiftJoy", shiftJoyVal);
            frc::SmartDashboard::PutNumber("RotateJoy", rotateJoyVal);

            frc::SmartDashboard::PutNumber("Front Left Motor Current", currentFrontLeft);
            frc::SmartDashboard::PutNumber("Back Left Motor Current", currentBackLeft);
            frc::SmartDashboard::PutNumber("Front Right Motor Current", currentFrontRight);
            frc::SmartDashboard::PutNumber("Back Right Motor Current", currentBackRight);
            frc::SmartDashboard::PutNumber("Intake Left Motor Current", currentIntakeLeft);
            frc::SmartDashboard::PutNumber("Intake Right Motor Current", currentIntakeRight);

            // Camera Stuff
            frc::SmartDashboard::PutNumber("Limelight Camera Current", currentLimelight);
            frc::Wait(0.005);
        }
    }
}

/**
 * Runs during test mode
 */
void Robot::Test() { }

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
