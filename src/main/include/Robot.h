#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/SampleRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/Compressor.h>
#include <frc/Preferences.h>
#include "auto_alignment.hpp"
#include "channel_helper.hpp"
#include "controller_helper.hpp"
#include "mecanum_driver_helper.hpp"
#include "arcade_driver_helper.hpp"
#include "tank_driver_helper.hpp"
#include "motor_helper.hpp"
#include "pneumatic_helper.hpp"
#include "sonar_helper.hpp"
#include "ir_helper.hpp"
#include "encoder_helper.hpp"

/**
 * @class	   Robot.
 * @description Controls the robot at the highest level.
 */
class Robot : public frc::SampleRobot 
{
public:
	/**
	 * @constructor Robot
	 * @description Constructs an instance of the Robot class.
	 */
	Robot();

	/**
	 * @function	RobotInit
	 * @description Initialize the robot outside of the constructor.
	 */
	void RobotInit() override;

	/**
	 * @function	Autonomous
	 * @description Control the robot in autonomous mode.
	 * @notes	   Not utilized in 2019.
	 */
	void Autonomous() override;
	
	/**
	 * @function	OperatorControl
	 * @description Control the robot in operator mode.
	 */
	void OperatorControl() override;
	
	/**
	 * @function	Test
	 * @description Control the robot in test mode.
	 */
	void Test() override;

private:
	static constexpr int HATCH_DISTANCE = 24;
	static constexpr double encoderMultiplier = 1;		//TODO: Find correct value
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";

	frc::PowerDistributionPanel* pdp = new frc::PowerDistributionPanel();

	frc::SendableChooser<std::string> chooser;

	frc::Joystick XboxController { ChannelController::XBOX_CONTROLLER };
	frc::Joystick LogitechController { ChannelController::LOGITECH_CONTROLLER };
	frc::Joystick LeftDriveJoystick { ChannelController::LEFT_DRIVE_JOYSTICK };
	frc::Joystick RightDriveJoystick { ChannelController::RIGHT_DRIVE_JOYSTICK };
	frc::Joystick LeftButtonHub { ChannelController::LEFT_BUTTON_HUB };
	frc::Joystick RightButtonHub { ChannelController::RIGHT_BUTTON_HUB };
	
	frc::Spark* frontLeftMotor = new frc::Spark(ChannelPWM::FRONT_LEFT_MOTOR);
	frc::Spark* backLeftMotor = new frc::Spark(ChannelPWM::BACK_LEFT_MOTOR);
	frc::Spark* frontRightMotor = new frc::Spark(ChannelPWM::FRONT_RIGHT_MOTOR);
	frc::Spark* backRightMotor = new frc::Spark(ChannelPWM::BACK_RIGHT_MOTOR);
	frc::Spark* intakeLeftMotor = new frc::Spark(ChannelPWM::LEFT_INTAKE_MOTOR);
	frc::Spark* intakeRightMotor = new frc::Spark(ChannelPWM::RIGHT_INTAKE_MOTOR);
	frc::Spark* placeholderMotor = new frc::Spark(ChannelPWM::PLACEHOLDER_MOTOR);

    Compressor* compressor = new Compressor(0);
    
	MaxSonar* ultrasonicHatch = new MaxSonar(ChannelAnalog::ULTRASONIC_SENSOR_HATCH, UltrasonicSensorType::LV);
	frc::AnalogGyro* gyro = new frc::AnalogGyro(0); // TODO: ENSURE CORRECT CHANNEL
    
	Encoder* encoderFrontLeft = new Encoder(ChannelDigital::FRONT_LEFT_ENCODER_CHANNEL_A, ChannelDigital::FRONT_LEFT_ENCODER_CHANNEL_B, encoderMultiplier, false, frc::Encoder::EncodingType::k4X);
	Encoder* encoderBackLeft = new Encoder(ChannelDigital::BACK_LEFT_ENCODER_CHANNEL_A, ChannelDigital::BACK_LEFT_ENCODER_CHANNEL_B, encoderMultiplier, false, frc::Encoder::EncodingType::k4X);
	Encoder* encoderFrontRight = new Encoder(ChannelDigital::FRONT_RIGHT_ENCODER_CHANNEL_A, ChannelDigital::FRONT_RIGHT_ENCODER_CHANNEL_B, encoderMultiplier, false, frc::Encoder::EncodingType::k4X);
	Encoder* encoderBackRight = new Encoder(ChannelDigital::BACK_RIGHT_ENCODER_CHANNEL_A, ChannelDigital::BACK_RIGHT_ENCODER_CHANNEL_B, encoderMultiplier, false, frc::Encoder::EncodingType::k4X);

    BjorgMecanumDrive* driveSystem = new BjorgMecanumDrive(
        this->frontLeftMotor, 
        this->backLeftMotor, 
        this->frontRightMotor, 
        this->backRightMotor, 
        &this->XboxController, 
        &this->XboxController, 
        &this->XboxController,
        this->gyro,
        this->autoAlignment
    );

	AutoAlignment* autoAlignment = new AutoAlignment(gyro, ultrasonicHatch);

	double inputVoltage = -1;
	double totalCurrent = -1;
	double temp = -1;
	double totalEnergy = -1;
	double totalPower = -1;
	double compressorCurrent = -1;
	bool compressorEnabled = false;
	bool hatchReady = false;
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
	double currentLimelight = -1;
};

#endif