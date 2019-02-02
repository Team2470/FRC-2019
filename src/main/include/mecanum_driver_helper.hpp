#ifndef MECANUM_DRIVER_HELPER_HPP
#define MECANUM_DRIVER_HELPER_HPP

#include <frc/drive/MecanumDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>

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
	//int rtTurn = 0;
	//int lftTurn = 0;
	int fwdMove = 0;
	int bckMove = 0;
    int fwdShift = 0;
	int bckShift = 0;
 	int fwdRotate = 0;
	int bckRotate = 0;
	int joystickInt = 0;
	int reverseDrive = -1;
	//bool rotateEnable = true;
	//bool sqrInput = false;
	bool multiMove   = false;
	bool multiShift  = false;
	bool multiRotate = false;
	float moveMultiplier = 1.0;
 	float shiftMultiplier = 1.0;
	float rotateMultiplier = 1.0;
	
	/**
	 * @constructor BjorgMecanumDrive
	 * @description Construct the BjorgMecanumDrive.
	 * @param		m_frontleftMotor  -- The front left motor of the mecanum drive.
	 * @param		m_backleftMotor   -- The back left motor of the mecanum drive.
	 * @param		m_frontrightMotor -- The front right motor of mecanum drive.
	 * @param		m_backrightMotor  -- The back right motor of the mecanum drive.
	 * @param		moveController    -- The joystick controlling forward-backward translational movement.
	 * @param 		shiftController   -- The joystick controlling left-right translational movement.
	 * @param		rotateController  -- The joystick controlling rotational movement.
	 */
	BjorgMecanumDrive(
		frc::Spark* m_frontleftMotor, 
		frc::Spark* m_backleftMotor, 
		frc::Spark* m_frontrightMotor, 
		frc::Spark* m_backrightMotor,
    	frc::Joystick* moveController, 
		frc::Joystick* shiftController, 
		frc::Joystick* rotateController
	);

	/**
	 * @function	mecanumDrive
	 * @description Controls the mecanum drive with the supplied joysticks; it governs all
	 *				movement, translational and rotational.
	 */
	void mecanumDrive();

	/**
	 * @function
	 * @description Controls the mecanum drive with explicitly supplied values; it governs
	 * 				all movement, translational and rotational.
	 * @param		movement -- Forward-backward translation velocity.
	 * @param		shift    -- Left-right translational velocity.
	 * @param		rotate   -- Rotational velocity.
	 */
	void mecanumDrive(double movement, double shift, double rotate);

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
	float movementValue = 0.0;
    float shiftValue = 0.0;
	float rotateValue = 0.0;
	frc::MecanumDrive* m_robotDrive;
	frc::Joystick* driveControllerMove;
	frc::Joystick* driveControllerShift;
    frc::Joystick* driveControllerRotate;
	
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
