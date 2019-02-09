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
class Robot : public frc::SampleRobot 
{
public:
    Robot();

    void RobotInit() override;
    void Autonomous() override;
    void OperatorControl() override;
    void Test() override;

private:
    frc::PowerDistributionPanel* pdp = new frc::PowerDistributionPanel();
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
	frc::Spark* intakeMotor = new frc::Spark(ChannelPWM::INTAKE_MOTOR);
    frc::Spark* placeholderMotor = new frc::Spark(ChannelPWM::PLACEHOLDER_MOTOR);
    BjorgMecanumDrive* driveSystem = new BjorgMecanumDrive(frontLeftMotor, backLeftMotor, frontRightMotor, backRightMotor, &XboxController, &XboxController, &XboxController);
    Compressor* compressor = new Compressor(0);
    MaxSonar* ultrasonicHatch = new MaxSonar(ChannelAnalog::ULTRASONIC_SENSOR_HATCH, UltrasonicSensorType::LV);

    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    
    static constexpr int HATCH_DISTANCE = 24;

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