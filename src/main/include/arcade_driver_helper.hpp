#ifndef ARCADE_DRIVER_HELPER_HPP
#define ARCADE_DRIVER_HELPER_HPP

#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>

/**
 * @class 	BjorgArcadeDRive
 * @description This class operates a SpeedController group using a differential drive;
 *      	    it has the ability to drive using a teleoperated arcade drive or autonomous
 *		        arcade drive.
 * @notes       This should be updated for other versions as needed.
 */
class BjorgArcadeDrive 
{
public:
    int moveCtrl = 0;
	int rotateCtrl = 0;
	int rtTurn = 0;
	int lftTurn = 0;
	int fwdDrive = 0;
	int bckDrive = 0;
	int joystickInt = 0;
	int reverseDrive = -1;
	bool rotateEnable = true;
	bool sqrInputs = false;
	bool multiRotate = false;
	bool multiMove = false;
	float motorMultiplier = 1.0;
	float rotateMult = 0.5;
	
	/**
	 * @constructor BjorgArcadeDrive
	 * @description Construct the arcade drive.
	 * @param       leftMotor  	   -- A pointer to the Spark object controlling the left motor.
	 * @param	    rightMotor       -- A pointer to the Spark object controlling the right motor.
	 * @param	    controllerMovement -- A pointer to the Joystick object governing movement.
	 * @param	    controllerRotate   -- A pointer to the Joystick object governing rotation.
	 */
	BjorgArcadeDrive(
        frc::SpeedController* leftMotor, 
        frc::SpeedController* rightMotor, 
        frc::Joystick* controllerMovement, 
        frc::Joystick* controllerRotate
    );
	
	/**
	 * @function    arcadeDrive
	 * @description Control the arcade drive with joystick input, governs both translational
	 *		        and rotational movement.
	 */
	void arcadeDrive();

	/**
	 * @function    arcadeDrive
	 * @description Control the arcade drive with explicit input, governs both translation
	 *		        and rotational movement.
	 */
	void arcadeDrive(double movement, double rotate);

	/**
	 * @function	stop
	 * @description Full-stop the arcade drive, i.e, all translational and rotational
	 * 		        velocity is set to zero.
	 */
	void stop();

	/**
	 * @function	twoBtnDrive
	 * @description Generate a singular movement value from two buttons.
	 */
	void twoBtnDrive();

private:
	float movementValue = 0.0;
	float rotationValue = 0.0;
    
	frc::DifferentialDrive* robotDrive;
	frc::Joystick* driveControllerMovement;
	frc::Joystick* driveControllerRotate;
    
	/**
	 * @function	twoBtnRotate
	 * @description Create a singular rotation value from two buttons and a joystick.
	 */
	void twoBtnRotate();
    
	/**
	 * @function
	 * @description Update movementValue to an appropriate value, utilized by the drive.
	 */
	void setMovement();
    
	/**
	 * @function    setRotate
	 * @description Update rotateValue to be utilized by the drive.
	 */
	void setRotate(bool rotateEn = true);
};

#endif
