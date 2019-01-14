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

//OUR INCLUDES//
#include "channel_helper.h"
#include "controller_helper.h"
#include "mecanum_driver_helper.hpp"
#include "arcade_driver_helper.hpp"
#include "motor_helper.hpp"
#include "solenoid_helper.hpp"
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
  //Our joysticks (includes the xbox and logitech controllers, the arcadee joysticks, and the button hubs)
  frc::Joystick LeftDriveJoystick { Channel_Controller::LEFT_DRIVE_JOYSTICK };
  frc::Joystick RightDriveJoystick { Channel_Controller::RIGHT_DRIVE_JOYSTICK };
	frc::Joystick FlightJoystick { Channel_Controller::FLIGHT_JOYSTICK };
	frc::Joystick LeftButtonHub { Channel_Controller::LEFT_BUTTON_HUB };
	frc::Joystick RightButtonHub { Channel_Controller::RIGHT_BUTTON_HUB };

  //Our standalone spark motors
	frc::Spark* m_frontleftMotor = new frc::Spark(Channel_PWM::FRONT_LEFT_MOTOR);
	frc::Spark* m_backleftMotor = new frc::Spark(Channel_PWM::BACK_LEFT_MOTOR);
	frc::Spark* m_frontrightMotor = new frc::Spark(Channel_PWM::FRONT_RIGHT_MOTOR);
  frc::Spark* m_backrightMotor = new frc::Spark(Channel_PWM::BACK_RIGHT_MOTOR);
	frc::Spark* m_cargoMotor = new frc::Spark(Channel_PWM::CARGO_MOTOR);

  //Our BjorgDrive systems for driving the robot, the function takes in four motors and three joysticks from above
  BjorgMecanumDrive* m_driveSystem = new BjorgMecanumDrive(m_frontleftMotor, m_backleftMotor, m_frontrightMotor, m_backrightMotor, &RightDriveJoystick, &RightDriveJoystick, &LeftDriveJoystick);

  //Our generic motors, take the PWM channel and the motor type
	//Motor* m_otherMotor = new Motor(Channel_PWM::LIFT_MOTOR, Motor_Type::SPARK);

  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
};
