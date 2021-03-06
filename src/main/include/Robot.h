#define M_PI 3.14159265358979323846 /* pi */

#ifndef ROBOT_H
#define ROBOT_H

#include <string>

#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/Compressor.h>
#include <frc/Preferences.h>
#include <frc/DigitalOutput.h>
#include <frc/ADXRS450_Gyro.h>
#include <frc/Preferences.h>

#include "AutoAlignment.hpp"
#include "channel_helper.hpp"
#include "controller_helper.hpp"
#include "BjorgMecanumDrive.hpp"
#include "arcade_driver_helper.hpp"
#include "tank_driver_helper.hpp"
#include "motor_helper.hpp"
#include "pneumatic_helper.hpp"
#include "sonar_helper.hpp"
#include "ir_helper.hpp"
#include "encoder_helper.hpp"

enum ControlMode
{
	AUTO,
	TELEOP
};

/**
 * @class	   Robot.
 * @description Controls the robot at the highest level.
 */
class Robot : public frc::TimedRobot
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
	void RobotPeriodic() override;

	/**
	 * @function	Autonomous
	 * @description Control the robot in autonomous mode.
	 * @notes	   Not utilized in 2019.
	 */
	void AutonomousInit() override;
	void AutonomousPeriodic() override;

	/**
	 * @function	OperatorControl
	 * @description Control the robot in operator mode.
	 */
	// void OperatorControl() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;

	/**
	 * @function	TestPeriodic
	 * @description Control the robot in test mode.
	 */
	void TestInit() override;
	void TestPeriodic() override;

	void DisabledInit() override;
	void DisabledPeriodic() override;

	/**
	 * @function    BasicControl
	 * @description Basic robot control. Used in auto and teleop.
	 * @param       mode -- The control mode.
	 */
	void BasicControl(ControlMode mode);

  private:
	static constexpr int KNOWN_PRESSURE = 60;
	static constexpr double EXPERIMENTAL_VOLTAGE_OUTPUT = 1.5;
	static constexpr int HATCH_DISTANCE = 12;
	//256 * 2 = 512 for pulses per rev (Hi-Res CIM encoder)
	//diameter for the mecanum wheels is 6 inches
	//value for encoder mult = (1 / 512) * M_PI * 6 ~= 0.0369
	//could just have it be 1 and rotate once to see what the approx value is
	static constexpr int PULSES_PER_REVOLUTION = 512;
	static constexpr int WHEEL_DIAMETER = 6;
	static constexpr double ENCODER_MULTIPLIER = ((1 / PULSES_PER_REVOLUTION) * WHEEL_DIAMETER * M_PI); //TODO: Find correct value
	
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";

	frc::Preferences *prefs;

	frc::PowerDistributionPanel *pdp = new frc::PowerDistributionPanel();

	frc::SendableChooser<std::string> chooser;

	frc::Joystick XboxController{ChannelController::XBOX_CONTROLLER};
	//frc::Joystick LogitechController { ChannelController::LOGITECH_CONTROLLER };
	frc::Joystick FlightJoystick{ChannelController::FLIGHT_JOYSTICK};
	frc::Joystick LeftDriveJoystick{ChannelController::LEFT_DRIVE_JOYSTICK};
	frc::Joystick RightDriveJoystick{ChannelController::RIGHT_DRIVE_JOYSTICK};
	frc::Joystick LeftButtonHub{ChannelController::LEFT_BUTTON_HUB};
	frc::Joystick RightButtonHub{ChannelController::RIGHT_BUTTON_HUB};

	frc::Spark *frontLeftMotor = new frc::Spark(ChannelPWM::FRONT_LEFT_MOTOR);
	frc::Spark *backLeftMotor = new frc::Spark(ChannelPWM::BACK_LEFT_MOTOR);
	frc::Spark *frontRightMotor = new frc::Spark(ChannelPWM::FRONT_RIGHT_MOTOR);
	frc::Spark *backRightMotor = new frc::Spark(ChannelPWM::BACK_RIGHT_MOTOR);
	frc::VictorSP *intakeLeftMotor = new frc::VictorSP(ChannelPWM::LEFT_INTAKE_MOTOR);
	frc::VictorSP *intakeRightMotor = new frc::VictorSP(ChannelPWM::RIGHT_INTAKE_MOTOR);
	// frc::Spark *placeholderMotor = new frc::Spark(ChannelPWM::PLACEHOLDER_MOTOR);

	frc::ADXRS450_Gyro *gyro = new frc::ADXRS450_Gyro(); // TODO: ENSURE CORRECT CHANNEL
	MaxSonar *ultrasonicHatch = new MaxSonar(ChannelAnalog::ULTRASONIC_SENSOR_HATCH, UltrasonicSensorType::LV);
	VisionProcessing *limelight = new VisionProcessing();
	AutoAlignment *autoAlignment = new AutoAlignment(gyro, ultrasonicHatch, limelight);

	// TODO: Find the correct distance multiplier.
	//hi-res cim encoder has 256 pulses per channel per revolution (either 256 or 512 depending on if we multiply by number of channels)
	//still need the factor in gearing reductions
	Encoder *encoderFrontLeft = new Encoder(ChannelDigital::FRONT_LEFT_ENCODER_CHANNEL_A, ChannelDigital::FRONT_LEFT_ENCODER_CHANNEL_B, ENCODER_MULTIPLIER, false, frc::Encoder::EncodingType::k4X);
	Encoder *encoderBackLeft = new Encoder(ChannelDigital::BACK_LEFT_ENCODER_CHANNEL_A, ChannelDigital::BACK_LEFT_ENCODER_CHANNEL_B, ENCODER_MULTIPLIER, false, frc::Encoder::EncodingType::k4X);
	Encoder *encoderFrontRight = new Encoder(ChannelDigital::FRONT_RIGHT_ENCODER_CHANNEL_A, ChannelDigital::FRONT_RIGHT_ENCODER_CHANNEL_B, ENCODER_MULTIPLIER, false, frc::Encoder::EncodingType::k4X);
	Encoder *encoderBackRight = new Encoder(ChannelDigital::BACK_RIGHT_ENCODER_CHANNEL_A, ChannelDigital::BACK_RIGHT_ENCODER_CHANNEL_B, ENCODER_MULTIPLIER, false, frc::Encoder::EncodingType::k4X);
	//frc::DigitalOutput *plexiglassLED = new frc::DigitalOutput(ChannelDigital::PLEXIGLASS_LIGHT_CONTROL);
	frc::DigitalOutput *frontClimbers = new frc::DigitalOutput(ChannelDigital::FRONT_PNEUMATICS_SPIKE);
	frc::DigitalOutput *backClimbers = new frc::DigitalOutput(ChannelDigital::BACK_PNEUMATICS_SPIKE);

	BjorgArcadeDrive *intakeSystem = new BjorgArcadeDrive(intakeLeftMotor, intakeRightMotor, &FlightJoystick, &FlightJoystick);

	BjorgMecanumDrive *driveSystem = new BjorgMecanumDrive(
		this->frontLeftMotor,
		this->backLeftMotor,
		this->frontRightMotor,
		this->backRightMotor,
		&this->RightDriveJoystick, //XboxController
		&this->RightDriveJoystick, //XboxController
		&this->LeftDriveJoystick,  //XboxController
		this->gyro,
		this->autoAlignment);

	//Need to input a known pressure and measured voltage output to use normalized at construction
	PressureSensor *pressureSensor = new PressureSensor(ChannelAnalog::PRESSURE_SENSOR, KNOWN_PRESSURE, EXPERIMENTAL_VOLTAGE_OUTPUT);
	Compressor *compressor = new Compressor(0);
	SingleSolenoid *climberFrontLeft = new SingleSolenoid(ChannelSolenoid::FRONT_LEFT_SOLENOID);
	SingleSolenoid *climberBackLeft = new SingleSolenoid(ChannelSolenoid::BACK_LEFT_SOLENOID);
	SingleSolenoid *climberFrontRight = new SingleSolenoid(ChannelSolenoid::FRONT_RIGHT_SOLENOID);
	SingleSolenoid *climberBackRight = new SingleSolenoid(ChannelSolenoid::BACK_RIGHT_SOLENOID);
	SingleSolenoid *hatchExtend = new SingleSolenoid(ChannelSolenoid::HATCH_EXTEND_SOLENOID);
	SingleSolenoid *hatchPop = new SingleSolenoid(ChannelSolenoid::HATCH_POP_SOLENOID);
	DoubleSolenoid *climbExtend = new DoubleSolenoid(ChannelSolenoid::CLIMBER_EXTEND_FORWARDS, ChannelSolenoid::CLIMBER_EXTEND_BACKWARDS);

	// bool currentlyResolving = false;
	double climberDelay = 0;		//Value Obtained Via Preferences
	int climberDelayCount = 0;
	double inputVoltage = -1;
	double totalCurrent = -1;
	double temp = -1;
	double totalEnergy = -1;
	double totalPower = -1;
	double compressorCurrent = -1;
	double pressureSensorVoltage = -1;
	double robotPressure = -1;
	bool compressorEnabled = true;
	bool compressorLowPressureActivate = true;
	bool climberReady = false;
	bool hatchReady = false;
	double ultraValue = -1;
	bool hatchPopping = false;
	bool halfSpeed = false;
	bool stopDrive = false;
	bool intakeActive = false;
	double moveJoyVal = 0;
	double shiftJoyVal = 0;
	double rotateJoyVal = 0;
	bool shiftDisabled = false;
	bool moveDisabled = false;
	// int encoderCountFrontLeft = 0;
	// int encoderCountBackLeft = 0;
	// int encoderCountFrontRight = 0;
	// int encoderCountBackRight = 0;
	double currentFrontLeft = -1;
	double currentBackLeft = -1;
	double currentFrontRight = -1;
	double currentBackRight = -1;
	double currentIntakeLeft = -1;
	double currentIntakeRight = -1;
	double currentLimelight = -1;
};

#endif