#ifndef MECANUM_DRIVER_HELPER_HPP
#define MECANUM_DRIVER_HELPER_HPP

#include <frc/drive/MecanumDrive.h>
#include <frc/AnalogGyro.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include "sonar_helper.hpp"
#include "vision_processing.hpp"
#include "auto_alignment.hpp"
#include "encoder_helper.hpp"

/**
 * @class		BjorgMecanumDrive
 * @description This class operates a SpeedController group using the mecanum drive;
 *				it has the ability to control the mecanum drive.
 */
class BjorgMecanumDrive
{
public:
	int moveCtrl = 0;
    int shiftCtrl = 0;
	int rotateCtrl = 0;
	int fwdMove = 0;
	int bckMove = 0;
    int fwdShift = 0;
	int bckShift = 0;
 	int fwdRotate = 0;
	int bckRotate = 0;
	int joystickInt = 0;
	int reverseDrive = -1;
	bool multiMove = false;
	bool multiShift = false;
	bool multiRotate = false;
	float moveMultiplier = 1.0;
 	float shiftMultiplier = 1.0;
	float rotateMultiplier = 1.0;
    bool resolutionNeeded = false;

	/**
	 * @constructor BjorgMecanumDrive
	 * @description Construct the BjorgMecanumDrive.
	 * @param		frontLeftMotor   -- The front left motor of the mecanum drive.
	 * @param		backLeftMotor    -- The back left motor of the mecanum drive.
	 * @param		frontRightMotor  -- The front right motor of mecanum drive.
	 * @param		backRightMotor   -- The back right motor of the mecanum drive.
	 * @param		moveController   -- The joystick controlling forward-backward translational movement.
	 * @param 		shiftController  -- The joystick controlling left-right translational movement.
	 * @param		rotateController -- The joystick controlling rotational movement.
     * @param       gyroSensor       -- The installed gyro.
	 */
	BjorgMecanumDrive(
		frc::Spark* frontLeftMotor, 
		frc::Spark* backLeftMotor, 
		frc::Spark* frontRightMotor, 
		frc::Spark* backRightMotor,
    	frc::Joystick* moveController, 
		frc::Joystick* shiftController, 
		frc::Joystick* rotateController,
        frc::AnalogGyro* gyroSensor,
        AutoAlignment* autoAlignment
	);

	/**
	 * @function	mecanumDrive
	 * @description Controls the mecanum drive with the supplied joysticks; it governs all
	 *				movement, translational and rotational.
	 */
	void mecanumDrive();

	/**
	 * @function    mecanumDrive
	 * @description Controls the mecanum drive with explicitly supplied values; it governs
	 * 				all movement, translational and rotational.
	 * @param		movement -- Forward-backward translation velocity.
	 * @param		shift    -- Left-right translational velocity.
	 * @param		rotate   -- Rotational velocity.
	 */
	void mecanumDrive(double movement, double shift, double rotate);

    /**
     * @function
     * @description Responsible for performing the auto-alignment of the robot.
     * @notes       Utilizes the VisionProcessing class.
     */
    void mecanumDriveAutoAlign();

	/**
	 * @function	twoBtnMove
	 * @description Create a singular movement value from two buttons.
	 */
	void twoBtnMove();

	/**
	 * @function    twoBtnShift
	 * @description Create a singular shift value from two buttons.
	 */
	void twoBtnShift();

	/**
	 * @function	twoBtnRotate
	 * @description Create a singular rotation value out of two buttons.
	 */
	void twoBtnRotate();

private:
    static constexpr bool UTILIZE_GYRO = false;
	float movementValue = 0.0;
    float shiftValue = 0.0;
	float rotateValue = 0.0;
    bool rotationResolved = false;
    bool distanceResolved = false;

    frc::MecanumDrive* robotDrive;
	frc::Joystick* driveControllerMove;
	frc::Joystick* driveControllerShift;
    frc::Joystick* driveControllerRotate;
    frc::AnalogGyro* gyroSensor;
    AutoAlignment* autoAlignment;
    Encoder* encoderFrontLeft;
    Encoder* encoderFrontRight;
    Encoder* encoderBackLeft;
    Encoder* encoderBackRight;

	/**
	 * @function	setMovement
	 * @description Update the movement value, to be used by the drive.
	 */
	void setMovement();
    
	/**
	 * @function    setRotate
	 * @description Update the rotation value, to be used by the drive.
	 */
	void setRotate(bool rotateEn = true);
};

#endif
