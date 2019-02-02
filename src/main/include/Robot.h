/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//CPP INCLUDES//
#include <string>

//FIRST INCLUDES//
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/SampleRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/Compressor.h>
#include <frc/Preferences.h>

//OUR INCLUDES//
#include "channel_helper.hpp"
#include "controller_helper.hpp"
#include "mecanum_driver_helper.hpp"
#include "arcade_driver_helper.hpp"
#include "tank_driver_helper.hpp"
#include "motor_helper.hpp"
#include "pneumatic_helper.hpp"
#include "sonar_helper.hpp"
#include "ir_helper.hpp"

/**
 * This is a demo program showing the use of the DifferentialDrive class. The
 * SampleRobot class is the base of a robot application that will automatically
 * call your Autonomous and OperatorControl methods at the right time as
 * controlled by the switches on the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're
 * inexperienced, don't. Unless you know what you are doing, complex code will
 * be much more difficult under this system. Use TimedRobot or Command-Based
 * instead if you're new.
 */
class Robot : public frc::SampleRobot {
 public:
  Robot();

  void RobotInit() override;
  void Autonomous() override;
  void OperatorControl() override;
  void Test() override;

 private:
  //The PDP can be used to check current draw, input voltage, and other useful readings.
  frc::PowerDistributionPanel* pdp = new frc::PowerDistributionPanel();

  //Our joysticks (includes the xbox and logitech controllers, the arcadee joysticks, and the button hubs)
  frc::Joystick XboxController { ChannelController::XBOX_CONTROLLER };
	frc::Joystick LogitechController { ChannelController::LOGITECH_CONTROLLER };
  frc::Joystick LeftDriveJoystick { ChannelController::LEFT_DRIVE_JOYSTICK };
  frc::Joystick RightDriveJoystick { ChannelController::RIGHT_DRIVE_JOYSTICK };
	//frc::Joystick FlightJoystick { ChannelController::FLIGHT_JOYSTICK };
	frc::Joystick LeftButtonHub { ChannelController::LEFT_BUTTON_HUB };
	frc::Joystick RightButtonHub { ChannelController::RIGHT_BUTTON_HUB };

  //Our standalone spark motors
	frc::Spark* m_frontleftMotor = new frc::Spark(ChannelPWM::FRONT_LEFT_MOTOR);
	frc::Spark* m_backleftMotor = new frc::Spark(ChannelPWM::BACK_LEFT_MOTOR);
	frc::Spark* m_frontrightMotor = new frc::Spark(ChannelPWM::FRONT_RIGHT_MOTOR);
  frc::Spark* m_backrightMotor = new frc::Spark(ChannelPWM::BACK_RIGHT_MOTOR);
	frc::Spark* m_intakeMotor = new frc::Spark(ChannelPWM::INTAKE_MOTOR);
  //frc::Spark* m_leftMotor = new frc::Spark(ChannelPWM::LEFT_MOTOR);
  //frc::Spark* m_rightMotor = new frc::Spark(ChannelPWM::RIGHT_MOTOR);
  frc::Spark* m_placeholderNotor = new frc::Spark(ChannelPWM::PLACEHOLDER_MOTOR);

  //Our BjorgDrive systems for driving the robot, the function takes in four motors and three joysticks from above
  BjorgMecanumDrive* m_driveSystem = new BjorgMecanumDrive(m_frontleftMotor, m_backleftMotor, m_frontrightMotor, m_backrightMotor, &XboxController, &XboxController, &XboxController);
  //BjorgArcadeDrive* m_intakeSystem = new BjorgArcadeDrive(m_intakeMotor, m_placeholderNotor, &FlightJoystick, &FlightJoystick);
  //BjorgArcadeDrive* m_arcdriveSystem = new BjorgArcadeDrive(m_leftMotor, m_rightMotor, &XboxController, &XboxController);

  //Our generic motors, take the PWM channel and the motor type
	//Motor* m_otherMotor = new Motor(ChannelPWM::LIFT_MOTOR, MotorType::SPARK);

  Compressor* m_compressor = new Compressor(0);

  //Preferences *prefs;

  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";

  //PDP
  double inputVoltage = -1;
  double totalCurrent = -1;
  double temp = -1;
  double totalEnergy = -1;
  double totalPower = -1;

  //Compressor
  double compressorCurrent = -1;
  bool compressorEnabled = false;

  //Driving
  bool halfSpeed = false;
  bool stopDrive = false;
  double moveJoyVal = 0;
  double shiftJoyVal = 0;
  double rotateJoyVal = 0;
  double currentFrontLeft = -1;
  double currentBackLeft = -1;
  double currentFrontRight = -1;
  double currentBackRight = -1;
  double currentIntakeLeft = -1;
  double currentIntakeRight = -1;

  //Camera
  double currentLimelight = -1;
};
