//*****************************************************************************
// Filename:            tank_driver_helper.hpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2019  Initial design.
//
// Description:
//    This class operates a SpeedController group using Differential Drive.
//    The class has the ability to drive using tele-operated Tank Drive, 
//        autonomous tank drive, and should be updated for other versions of 
//        as needed (tank, H, etc.).
// 
// Dependencies:
//    None
//*****************************************************************************

#ifndef TANK_DRIVER_HELPER_HPP
#define TANK_DRIVER_HELPER_HPP

/******************************************************************************
 * Include Files
 *****************************************************************************/
// FIRST Includes //
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>

/******************************************************************************
 * Constants
 *****************************************************************************/

/******************************************************************************
 * Types
 *****************************************************************************/

/******************************************************************************
 * CLASS      : BjorgTankDrive
 *
 * DESCRIPTION: This class creates a DifferentialDrive Object
 *
 * RETURNS    : None
 *****************************************************************************/
class BjorgTankDrive
{
public:
	
    /**************************************************************************
     * Variables
     *************************************************************************/
	int leftCtrl 	 = 0;
	int rightCtrl 	 = 0;
    //int rtTurn		 = 0;
    //int lftTurn		 = 0;
    int leftFwd 	 = 0;
    int leftBck	     = 0;
    int rightFwd	 = 0;
    int rightBck	 = 0;
	int joystickInt  = 0;
	int leftReverse = -1;
    int rightReverse = -1;
    

	bool rotateEnable = true;
	bool sqrInputs	 = false;
	bool multiLeft   = false;
    bool multiRight   = false;
	float leftMultiplier = 1.0;
    float rightMultiplier = 1.0;
	
    /**************************************************************************
     * FUNCTION   : BjorgTankDrive
     *
     * DESCRIPTION: Construct class BjorgTankDrive, set the motors to be used for 
     *              driving with <m_leftMotor> and <m_rightMotor> and the 
     *              Joystick used to drive <Joystick>.
     *
     * RETURNS    : A DifferentialDrive object
     *************************************************************************/	
	BjorgTankDrive(frc::Spark *m_leftMotor, frc::Spark *m_rightMotor, 
        frc::Joystick *controllerLeft, frc::Joystick *controllerRight);

    /**************************************************************************
     * FUNCTION   : tankDrive
     *
     * DESCRIPTION: Tank drive, left motor motion with the left joystick,
     *              right motor motion with the right joystick.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void tankDrive();

    /**************************************************************************
     * FUNCTION   : tankDrive
     *
     * DESCRIPTION: Tank drive, left motion with <leftMovement> and right with 
     *              <rightMotion>.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void tankDrive(double leftMovement, double rightMovement);

    /**************************************************************************
     * FUNCTION   : twoBtnLeft
     *
     * DESCRIPTION: Create movement value out of two buttons.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void twoBtnLeft();

    /**************************************************************************
     * FUNCTION   : twoBtnRight
     *
     * DESCRIPTION: Create movement value out of two buttons.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void twoBtnRight();
private:
	float leftValue = 0.0;
	float rightValue = 0.0;

	frc::DifferentialDrive *m_robotDrive;
	frc::Joystick *driveControllerLeft;
	frc::Joystick *driveControllerRight;
    
    /**************************************************************************
     * FUNCTION   : setMovement
     *
     * DESCRIPTION: Update <movementValue> to be used for drive.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void setMovement();
};

#endif /* TANK_DRIVER_HELPER_HPP */
