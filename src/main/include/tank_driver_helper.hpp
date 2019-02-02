#ifndef TANK_DRIVER_HELPER_HPP
#define TANK_DRIVER_HELPER_HPP

#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>

/**
 * @class	    BjorgTankDrive
 * @description This class operates a SpeedController group to control a tank drive.
 * @notes	    This class should be updated for other versions as needed.
 */
class BjorgTankDrive
{
public:
	int leftCtrl = 0;
	int rightCtrl = 0;
	//int rtTurn = 0;
	//int lftTurn = 0;
	int leftFwd = 0;
	int leftBck = 0;
	int rightFwd = 0;
	int rightBck = 0;
	int joystickInt = 0;
	int leftReverse = -1;
    int rightReverse = -1;
	bool rotateEnable = true;
	bool sqrInputs = false;
	bool multiLeft = false;
    bool multiRight = false;
	float leftMultiplier = 1.0;
    float rightMultiplier = 1.0;
	
	/**
	 * @constructor BjorgTankDrive
	 * @description Construct the BjorgTankDrive class.
	 * @param 	    leftMotor     -- The tank drive left motor.
	 * @param	    rightMotor    -- The tank drive right motor.
	 * @param	    controllerLeft  -- The joystick controlling the left motor.
	 * @param 	    controllerRight -- The joystick controlling the right motor.
	 */
	BjorgTankDrive(
		frc::Spark* leftMotor, 
		frc::Spark* rightMotor, 
        frc::Joystick* controllerLeft, 
		frc::Joystick* controllerRight
	);

	/**
	 * @function    tankDrive
	 * @description Controls the tank drive. The left joystick controls the velocity of the
	 *		        right motor; the right joystick controls the velocity of the right motor.
	 */ 
	void tankDrive();

	/**
	 * @function    tankDrive
	 * @description Controls the tank drive with explicit values for left and right movement.
	 * @param       leftMovement  -- The velocity of the left motor.
	 * @param	    rightMovement -- The velocity of the right motor.
	 */
	void tankDrive(double leftMovement, double rightMovement);

	/**
	 * @function	twoBtnLeft
	 * @description Generate a single left movement value from two buttons.
	 */
	void twoBtnLeft();

	/**
	 * @function    twoBtnRight
	 * @description Generate a single right movement value from two buttons.
	 */
	void twoBtnRight();
	
private:
	float leftValue = 0.0;
	float rightValue = 0.0;
	frc::DifferentialDrive* robotDrive;
	frc::Joystick* driveControllerLeft;
	frc::Joystick* driveControllerRight;
    
	/**
	 * @function    setMovement
	 * @description Update the movement value to be used by the
	 */
	void setMovement();
};

#endif
