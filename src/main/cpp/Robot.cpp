/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//CPP INCLUDES//
#include <iostream>

//FIRST INCLUDES//
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

//OUR INCLUDES//
#include "Robot.h"

Robot::Robot()
{
  // Note SmartDashboard is not initialized here, wait until RobotInit() to make
  // SmartDashboard calls
  //m_robotDrive.SetExpiration(0.1);
}

void Robot::RobotInit()
{
  //prefs = Preferences::GetInstance();

  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  //m_chooser.AddOption();
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::Autonomous() 
{
  std::string autoSelected = m_chooser.GetSelected();
  // std::string autoSelected = frc::SmartDashboard::GetString(
  // "Auto Selector", kAutoNameDefault);
  std::cout << "Auto selected: " << autoSelected << std::endl;

  // MotorSafety improves safety when motors are updated in loops but is
  // disabled here because motor updates are not looped in this autonomous mode.
  //m_robotDrive.SetSafetyEnabled(false);

  if (autoSelected == kAutoNameCustom) 
  {
    // Custom Auto goes here
    std::cout << "Running custom Autonomous" << std::endl;

    // Spin at half speed for two seconds
    //m_robotDrive.ArcadeDrive(0.0, 0.5);
    frc::Wait(2.0);

    // Stop robot
    //m_robotDrive.ArcadeDrive(0.0, 0.0);
  } 
  else 
  {
    // Default Auto goes here
    std::cout << "Running default Autonomous" << std::endl;

    // Drive forwards at half speed for two seconds
    //m_robotDrive.ArcadeDrive(-0.5, 0.0);
    frc::Wait(2.0);

    // Stop robot
    //m_robotDrive.ArcadeDrive(0.0, 0.0);
  }
}

/**
 * Runs the motors with arcade steering.
 */
void Robot::OperatorControl() 
{
  //Drive system variables
  m_driveSystem->moveCtrl = Axis_XBOX::XBOX_RIGHT_JOYSTICK_Y;
  m_driveSystem->shiftCtrl = Axis_XBOX::XBOX_RIGHT_JOYSTICK_X;
  m_driveSystem->rotateCtrl = Axis_XBOX::XBOX_LEFT_JOYSTICK_X;
  m_driveSystem->multiMove = false;
  m_driveSystem->multiShift = false;
  m_driveSystem->multiRotate = false;

  //Intake system variables
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
    compressorCurrent = m_compressor->getCurrent();
    compressorEnabled = m_compressor->getVal();

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

    if (LeftButtonHub.GetRawButton(Generic_Controller_Left::SWITCH_A))
    {
      m_driveSystem->moveMultiplier = 0.5;
      m_driveSystem->shiftMultiplier = 0.5;
      m_driveSystem->rotateMultiplier = 0.5;

      halfSpeed = true;
    }
    else
    {
      m_driveSystem->moveMultiplier = 1.0;
      m_driveSystem->shiftMultiplier = 1.0;
      m_driveSystem->rotateMultiplier = 1.0;

      halfSpeed = false;
    }

    /*if (RightButtonHub.GetRawButton(Generic_Controller_Right::SWITCH_X))
    {
      m_intakeSystem->arcadeDrive();
    }
    else
    {
      m_intakeSystem->stop();
    }*/

    m_driveSystem->mecanumDrive();


    //Driver Station//
    //PDP stuff
    frc::SmartDashboard::PutNumber("InputVoltage", inputVoltage);
    frc::SmartDashboard::PutNumber("TotalCurrent", totalCurrent);
    frc::SmartDashboard::PutNumber("Temperature", temp);
    frc::SmartDashboard::PutNumber("TotalEnergy", totalEnergy);
    frc::SmartDashboard::PutNumber("TotalPower", totalPower);

    //Compressor stuff
    frc::SmartDashboard::PutNumber("CompressorCurrent", compressorCurrent);
    frc::SmartDashboard::PutBoolean("Compressor Enabled", compressorEnabled);

    //Drive stuff
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


    //Camera Stuff
    frc::SmartDashboard::PutNumber("Limelight Camera Current", currentLimelight);
    frc::Wait(0.005);
  }
}

/**
 * Runs during test mode
 */
void Robot::Test() { }

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
