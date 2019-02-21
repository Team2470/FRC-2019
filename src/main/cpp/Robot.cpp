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
	driveSystem->moveCtrl = AxisXbox::XBOX_RIGHT_JOYSTICK_X;
	driveSystem->shiftCtrl = AxisXbox::XBOX_RIGHT_JOYSTICK_Y;
	driveSystem->rotateCtrl = AxisXbox::XBOX_LEFT_JOYSTICK_X;
	driveSystem->multiMove = false;
	driveSystem->multiShift = false;
	driveSystem->multiRotate = false;

	//Set motors to invert correctly
	//should be true, false, false, true
	frontLeftMotor->SetInverted(false);
	backLeftMotor->SetInverted(false);
	frontRightMotor->SetInverted(false);
	backRightMotor->SetInverted(false);


	// Intake system variables
	//m_intakeSystem->moveCtrl = FlightJoystick.GetYChannel();
	//m_intakeSystem->multiMove = false;
	//m_intakeSystem->multiRotate = false;
	//m_intakeSystem->rotateEnable = false;
	//m_intakeSystem->reverseDrive = -1;

	encoderFrontLeft->reset();
	encoderBackLeft->reset();
	encoderFrontRight->reset();
	encoderBackRight->reset();

	plexiglassLED->Set(true);

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
		compressorLowPressureActivate = compressor->getPressureActivate();

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

		
		//Main Robot Code

		//Toggles the limelight between vision processing and regular camera
		if (RightButtonHub.GetRawButton(GenericControllerRight::SWITCH_LOCKING_SAFE3))
		{
			limelight->setCameraMode(LimelightCameraMode::DRIVER_CAMERA);
		}
		else
		{
			limelight->setCameraMode(LimelightCameraMode::VISION_PROCESSOR);
		}

		//Toggles the plexiglass LEDs
		if (LeftButtonHub.GetRawButton(GenericControllerLeft::SWITCH_ARCADE_LEFT))
		{
			plexiglassLED->Set(true);
		}
		else
		{
			plexiglassLED->Set(false);
		}

		//Controls the motor multiplier: stopped, halved, or full speeds
		if (XboxController.GetRawButton(ButtonXbox::XBOX_LEFT_BUMPER)) //GenericControllerLeft::SWITCH_B
		{
			driveSystem->moveMultiplier = 0;
			driveSystem->shiftMultiplier = 0;
			driveSystem->rotateMultiplier = 0;
			halfSpeed = false;
			stopDrive = true;
		}
		else if (XboxController.GetRawButton(ButtonXbox::XBOX_RIGHT_BUMPER)) //GenericControllerLeft::SWITCH_A
		{
			driveSystem->moveMultiplier = 0.5;
			driveSystem->shiftMultiplier = 0.5;
			driveSystem->rotateMultiplier = 0.5;
			halfSpeed = true;
			stopDrive = false;
		}
		else
		{
			driveSystem->moveMultiplier = 1;
			driveSystem->shiftMultiplier = 1;
			driveSystem->rotateMultiplier = 1;
			halfSpeed = false;
			stopDrive = false;
		}

		//Toggles the compressor on and off
		if (XboxController.GetRawButton(ButtonXbox::XBOX_X)) //GenericControllerLeft::BUTTON_BLUE_TOP_LEFT
		{
			compressor->toggleCompressor();
		}

		//Toggles if the compressor turns on when pressure is low
		if (XboxController.GetRawButton(ButtonXbox::XBOX_Y)) //GenericControllerLeft::BUTTON_BLUE_TOP_RIGHT
		{
			compressor->lowPressureToggle();
		}

		// Controlls the Hatch
		if (XboxController.GetRawButton(ButtonXbox::XBOX_A)) //(GenericControllerRight::SWITCH_X
		{
			hatchExtend->activate();
		}
		else
		{
			hatchExtend->deactivate();
		}

		// Pops off the hatch
		if (XboxController.GetRawButton(ButtonXbox::XBOX_B)) //GenericControllerRight::SWITCH_Y
		{
			hatchPop->activate();
		}
		else
		{
			hatchPop->deactivate();
		}

		//Climber
		//Extends the climbing pneumatics
		if (XboxController.GetRawButton(ButtonXbox::XBOX_LEFT_JOYSTICK_PRESS)) //GenericControllerLeft::SWITCH_ARCADE_RIGHT
		{
			climbExtend->forwards();
			climberReady = true;
		}
		else if (XboxController.GetRawButton(ButtonXbox::XBOX_RIGHT_JOYSTICK_PRESS))
		{
			climbExtend->reverse();
			climberReady = false;
		}
		else
		{
			climbExtend->deactivate();
			climberReady = false;
		}
		//Extends and retracts the front pnuematics
		if (XboxController.GetRawButton(ButtonXbox::XBOX_START)) //GenericControllerRight::SWITCH_COVERED_SAFE1
		{
			climberFrontLeft->activate();
			climberFrontRight->activate();
			climberBackLeft->activate();
			climberBackRight->activate();
		}
		else
		{
			climberFrontLeft->deactivate();
			climberFrontRight->deactivate();
			climberBackLeft->deactivate();
			climberBackRight->deactivate();
		}
		//Extends and retracts the back pnuematics
		/*if (XboxController.GetRawButton(ButtonXbox::XBOX_BACK)) //GenericControllerRight::SWITCH_COVERED_SAFE2
		{
			climberBackLeft->activate();
			climberBackRight->activate();
		}
		else
		{
			climberBackLeft->deactivate();
			climberBackRight->deactivate();
		}*/

        // Activate the auto-alignment function.
        if(this->RightButtonHub.GetRawButton(GenericControllerRight::SWITCH_X))
        {
            this->currentlyResolving = true;
            this->driveSystem->resolutionNeeded = true;
        }

        // Check for potential emergency abort BEFORE the function
        // responsible for resolution is called.
        if(this->RightButtonHub.GetRawButton(GenericControllerRight::SWITCH_Y))
        {
            this->currentlyResolving = false;
        }

        // Assuming that resolution is indeed still required, call
        // the resolution function.
        if(this->currentlyResolving)
        {
            this->driveSystem->mecanumDriveAutoAlign();
            this->currentlyResolving = this->driveSystem->resolutionNeeded;
        }

        if(!this->currentlyResolving)
        {
            driveSystem->mecanumDrive();
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
		frc::SmartDashboard::PutBoolean("Compressor Low Pressure Activate", compressorLowPressureActivate);

		//Pneumatic Stuff
		frc::SmartDashboard::PutBoolean("Climber Ready", climberReady);

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

/**
 * Runs during test mode
 */
void Robot::Test() { }

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
