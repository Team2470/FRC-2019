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
	chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
	chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
	frc::SmartDashboard::PutData("Auto Modes", &chooser);

    gyro->Calibrate();
}

void Robot::TeleopInit()
{
	return;
}

void Robot::AutonomousInit()
{
	return;
}

void Robot::RobotPeriodic()
{
	return;
}

void Robot::TeleopPeriodic() 
{
	BasicControl(ControlMode::TELEOP);
}

void Robot::AutonomousPeriodic() 
{
	this->BasicControl(ControlMode::AUTO);
}

void Robot::TestPeriodic()
{
	return;
}


void Robot::BasicControl(ControlMode mode)
{
	// Drive system variables
	driveSystem->moveCtrl = AxisGeneric::JOYSTICK_X_AXIS;	//AxisXbox::XBOX_RIGHT_JOYSTICK_X
	driveSystem->shiftCtrl = AxisGeneric::JOYSTICK_Y_AXIS;	//AxisXbox::XBOX_RIGHT_JOYSTICK_Y
	driveSystem->rotateCtrl = AxisGeneric::JOYSTICK_X_AXIS;	//AxisXbox::XBOX_LEFT_JOYSTICK_X
	driveSystem->multiMove = false;
	driveSystem->multiShift = false;
	driveSystem->multiRotate = false;

	//Set motors to invert correctly
	frontLeftMotor->SetInverted(false);
	backLeftMotor->SetInverted(false);
	frontRightMotor->SetInverted(false);
	backRightMotor->SetInverted(false);

	// Intake system variables
	intakeSystem->moveCtrl = AxisFlight::FLIGHT_Y_AXIS; //FlightJoystick.GetYChannel()
	intakeSystem->multiMove = false;
	intakeSystem->multiRotate = false;
	intakeSystem->rotateEnable = false;
	intakeSystem->reverseDrive = 1;

	// encoderFrontLeft->reset();
	// encoderBackLeft->reset();
	// encoderFrontRight->reset();
	// encoderBackRight->reset();

	//plexiglassLED->Set(true);

	frontClimbers->Set(true);
	backClimbers->Set(true);

	bool continueLoop = true;
	while(continueLoop)
	{
		if(mode == ControlMode::AUTO)
		{
			continueLoop = this->IsAutonomous() && this->IsEnabled();
		}
		else if(mode == ControlMode::TELEOP)
		{
			continueLoop = this->IsOperatorControl() && this->IsEnabled();
		}

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
		hatchReady = ultrasonicHatch->sonarRange() <= HATCH_DISTANCE;

		//Drive
		moveJoyVal = RightDriveJoystick.GetY();
		shiftJoyVal = RightDriveJoystick.GetX();
		rotateJoyVal = LeftDriveJoystick.GetX();
		
		//Encoders
		// encoderCountFrontLeft = encoderFrontLeft->getValue();
		// encoderCountBackLeft = encoderBackLeft->getValue();
		// encoderCountFrontRight = encoderFrontRight->getValue();
		// encoderCountBackRight = encoderBackRight->getValue();

		currentFrontLeft = pdp->GetCurrent(ChannelPDP::PDP_FRONT_LEFT_MOTOR);
		currentBackLeft = pdp->GetCurrent(ChannelPDP::PDP_BACK_LEFT_MOTOR);
		currentFrontRight = pdp->GetCurrent(ChannelPDP::PDP_FRONT_RIGHT_MOTOR);
		currentBackRight = pdp->GetCurrent(ChannelPDP::PDP_BACK_RIGHT_MOTOR);
		currentIntakeLeft = pdp->GetCurrent(ChannelPDP::PDP_INTAKE_LEFT_MOTOR);
		currentIntakeRight = pdp->GetCurrent(ChannelPDP::PDP_INTAKE_RIGHT_MOTOR);

		//Camera
		currentLimelight = pdp->GetCurrent(ChannelPDP::PDP_LIMELIGHT_CAMERA);

		//Toggles the limelight between vision processing and regular camera
		if (RightButtonHub.GetRawButton(GenericControllerRight::SWITCH_LOCKING_SAFE3))
		{
			limelight->setPipeline(1);
		}
		else
		{
			limelight->setPipeline(0);
		}

		/*
		//Toggles the plexiglass LEDs
		if (LeftButtonHub.GetRawButton(GenericControllerLeft::SWITCH_ARCADE_LEFT))
		{
			plexiglassLED->Set(true);
		}
		else
		{
			plexiglassLED->Set(false);
		}
		*/

		//Controls the motor multiplier: stopped, halved, or full speed
		if (LeftButtonHub.GetRawButton(GenericControllerLeft::SWITCH_B)) //ButtonXbox::XBOX_LEFT_BUMPER
		{
			driveSystem->moveMultiplier = 0;
			driveSystem->shiftMultiplier = 0;
			driveSystem->rotateMultiplier = 0;
			halfSpeed = false;
			stopDrive = true;
		}
		else if (LeftButtonHub.GetRawButton(GenericControllerLeft::SWITCH_A)) //ButtonXbox::XBOX_RIGHT_BUMPER
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
		if (LeftButtonHub.GetRawButton(GenericControllerLeft::BUTTON_BLUE_TOP_LEFT)) //ButtonXbox::XBOX_X
		{
			//compressor->toggleCompressor();
			compressor->activate();
		}
		else if (LeftButtonHub.GetRawButton(GenericControllerLeft::BUTTON_BLUE_TOP_RIGHT))
		{
			compressor->deactivate();
		}

		/*
		//Toggles if the compressor turns on when pressure is low
		if (LeftButtonHub.GetRawButton(GenericControllerLeft::BUTTON_BLUE_BOTTOM_RIGHT)) //ButtonXbox::XBOX_Y
		{
			//compressor->lowPressureToggle();
			compressor->lowPressureToggle();
		}
		*/

		//Toggles if the robot only moves forwards or backwards
		if (LeftButtonHub.GetRawButton(GenericControllerLeft::BUTTON_BLUE_BOTTOM_RIGHT))
		{
			driveSystem->disableShift = false;
		}
		else
		{
			driveSystem->disableShift = true;
		}

		//Toggles if the robot only moves left or right
		if (LeftButtonHub.GetRawButton(GenericControllerLeft::BUTTON_BLUE_BOTTOM_LEFT))
		{
			driveSystem->disableMove = false;
		}
		else
		{
			driveSystem->disableMove = true;
		}

		// Controlls the Hatch
		if (RightButtonHub.GetRawButton(GenericControllerRight::BUTTON_FIRE)) //ButtonXbox::XBOX_A or GenericControllerRight::BUTTON_FIRE
		{
			hatchExtend->activate();
		}
		else
		{
			hatchExtend->deactivate();
		}

		// Pops off the hatch
		if (RightButtonHub.GetRawButton(GenericControllerRight::BUTTON_RELEASE) || RightButtonHub.GetRawButton(GenericControllerRight::BUTTON_RED_LEFT)) //ButtonXbox::XBOX_B or GenericControllerRight::BUTTON_RELEASE
		{
			hatchPop->activate();
			hatchPopping = true;
		}
		else
		{
			hatchPop->deactivate();
			hatchPopping = false;
		}

		//Climber
		//Extends the climbing pneumatics
		if (LeftButtonHub.GetRawButton(GenericControllerLeft::SWITCH_ARCADE_RIGHT)) //ButtonXbox::XBOX_LEFT_JOYSTICK_PRESS
		{
			climbExtend->forwards();
			climberReady = true;
		}
		//else if (LeftButtonHub.GetRawButton(GenericControllerLeft::SWITCH_ARCADE_LEFT))
		else
		{
			climbExtend->reverse();
			climberReady = false;
		}
		/*else
		{
			climbExtend->deactivate();
			climberReady = false;
		}*/
		//Extends and retracts the front pnuematics
		if (RightButtonHub.GetRawButton(GenericControllerRight::SWITCH_COVERED_SAFE1)) //ButtonXbox::XBOX_START
		{
			//climberFrontLeft->activate();
			//climberFrontRight->activate();
			frontClimbers->Set(false);
		}
		else
		{
			//climberFrontLeft->deactivate();
			//climberFrontRight->deactivate();
			frontClimbers->Set(true);
		}
		//Extends and retracts the back pnuematics
		if (RightButtonHub.GetRawButton(GenericControllerRight::SWITCH_COVERED_SAFE2)) //ButtonXbox::XBOX_BACK
		{
			//climberBackLeft->activate();
			//climberBackRight->activate();
			backClimbers->Set(false);
		}
		else
		{
			//climberBackLeft->deactivate();
			//climberBackRight->deactivate();
			backClimbers->Set(true);
		}

		// Auto-aligment?
		// std::cout << "adsum\n";
		if(RightButtonHub.GetRawButton(GenericControllerRight::SWITCH_X))
		{
			// std::cout << "SWITCH_X\n";

			// Auto-Align robot to closest target
			// Check safety switch
			if(RightButtonHub.GetRawButton(GenericControllerRight::SWITCH_Y))
			{
				// Operator can control robot while safety is on....
				// std::cout << "mecanumDrive SWITCH_Y\n";
				driveSystem->mecanumDrive();
			}
			else
			{
				driveSystem->mecanumDriveAutoAlign();
			}
		} 
		else
		{
			// Operator Control
			// std::cout << "mecanumDrive\n";
			driveSystem->mecanumDrive();
		}

		//Intake Drive
		if (FlightJoystick.GetRawButton(ButtonFlight::FLIGHT_TRIGGER))
		{
			intakeActive = true;
			intakeSystem->arcadeDrive();
		}
		else
		{
			intakeActive = false;
			intakeSystem->stop();
		}
		//intakeSystem->arcadeDrive();

		// Driver Station
		// PDP stuff

        // TODO: i am too lazy to make changes to the smart dashboard; for the time
        //       being (for testing purposes) i am going to place values pertaining
        //       to rotation and the like in the InputVoltage field (perhaps others
        //       as well). 
		frc::SmartDashboard::PutNumber("InputVoltage", inputVoltage); 
        //frc::SmartDashboard::PutNumber("TotalCurrent", totalCurrent);
		frc::SmartDashboard::PutNumber("TotalCurrent", (int)gyro->GetAngle() % 360);   //TODO: remove and uncomment above
        
        frc::SmartDashboard::PutNumber("Temperature", temp);


		frc::SmartDashboard::PutNumber("TotalEnergy", totalEnergy);
		frc::SmartDashboard::PutNumber("TotalPower", totalPower);

		// Compressor stuff
		frc::SmartDashboard::PutNumber("CompressorCurrent", compressorCurrent);
		// frc::SmartDashboard::PutBoolean("Compressor Enabled", compressorEnabled);
		frc::SmartDashboard::PutBoolean("Compressor Enabled", limelight->hasTarget());  //TODO: remove and uncomment above, and add to driver station
		frc::SmartDashboard::PutBoolean("Compressor Low Pressure Activate", compressorLowPressureActivate);

		//Pneumatic Stuff
		frc::SmartDashboard::PutBoolean("Climber Ready", climberReady);

		// Sensor Stuff
		frc::SmartDashboard::PutBoolean("Hatch Ready", hatchReady);
		frc::SmartDashboard::PutBoolean("Hatch Popping", hatchPopping);

		// Drive stuff
		frc::SmartDashboard::PutBoolean("HalfSpeed", halfSpeed);
		frc::SmartDashboard::PutBoolean("StopDrive", stopDrive);
		frc::SmartDashboard::PutBoolean("Intake Active", intakeActive);
		frc::SmartDashboard::PutNumber("MoveJoy", moveJoyVal);
		frc::SmartDashboard::PutNumber("ShiftJoy", shiftJoyVal);
		frc::SmartDashboard::PutNumber("RotateJoy", rotateJoyVal);

		//Encoder Counts
		// frc::SmartDashboard::PutNumber("Front Left Encoder Count", encoderCountFrontLeft);
		// frc::SmartDashboard::PutNumber("Back Left Encoder Count", encoderCountBackLeft);
		// frc::SmartDashboard::PutNumber("Front Right Encoder Count", encoderCountFrontRight);
		// frc::SmartDashboard::PutNumber("Back Right Encoder Count", encoderCountBackRight);

		//Current Values
		frc::SmartDashboard::PutNumber("Front Left Motor Current", currentFrontLeft);
		frc::SmartDashboard::PutNumber("Back Left Motor Current", currentBackLeft);
		frc::SmartDashboard::PutNumber("Front Right Motor Current", currentFrontRight);
		frc::SmartDashboard::PutNumber("Back Right Motor Current", currentBackRight);
		frc::SmartDashboard::PutNumber("Intake Left Motor Current", currentIntakeLeft);
		frc::SmartDashboard::PutNumber("Intake Right Motor Current", currentIntakeRight);

		// Sensor Stuff
		frc::SmartDashboard::PutNumber("Limelight Camera Current", currentLimelight);
		//TODO : add the following to DriverStation...
		// frc::SmartDashboard::PutBoolean("HasTargets", limelight->hasTarget());
		// frc::SmartDashboard::PutBoolean("X Offset", limelight->X_Offset());
		// frc::SmartDashboard::PutBoolean("Y Offset", limelight->Y_Offset());
		
		frc::Wait(0.005);
	}
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
