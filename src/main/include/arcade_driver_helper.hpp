//*****************************************************************************
// Filename:            arcade_driver_helper.hpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2018  Initial design.
//   Chris Struck       Jan. 2019  Renamed to arcade, to differentiate easier.
//
// Description:
//    This class operates a SpeedController group using Differential Drive.
//    The class has the ability to drive using tele-operated Arcade Drive, 
//        autonomous arcade drive, and should be updated for other versions of 
//        as needed (tank, H, etc.).
// 
// Dependencies:
//    None
//*****************************************************************************

#ifndef ARCADE_DRIVER_HELPER_HPP
#define ARCADE_DRIVER_HELPER_HPP

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
 * CLASS      : BjorgArcadeDrive
 *
 * DESCRIPTION: This class creates a DifferentialDrive Object
 *
 * RETURNS    : None
 *****************************************************************************/
class BjorgArcadeDrive 
{
public:
	
    /**************************************************************************
     * Variables
     *************************************************************************/
	int moveCtrl 	 = 0;
	int rotateCtrl 	 = 0;
	int rtTurn		 = 0;
	int lftTurn		 = 0;
	int fwdDrive	 = 0;
	int bckDrive	 = 0;
	int joystickInt  = 0;
	int reverseDrive = -1;

	bool rotateEnable = true;
	bool sqrInputs	 = false;
	bool multiRotate = false;
	bool multiMove   = false;
	float motorMultiplier = 1.0;
	float rotateMult = 0.5;
	
    /**************************************************************************
     * FUNCTION   : BjorgArcadeDrive
     *
     * DESCRIPTION: Construct class BjorgArcadeDrive, set the motors to be used for 
     *              driving with <m_leftMotor> and <m_rightMotor> and the 
     *              Joystick used to drive <Joystick>.
     *
     * RETURNS    : A DifferentialDrive object
     *************************************************************************/	
	BjorgArcadeDrive(frc::Spark *m_leftMotor, frc::Spark *m_rightMotor, 
        frc::Joystick *controllerMovement, frc::Joystick *controllerRotate);

    /**************************************************************************
     * FUNCTION   : arcadeDrive
     *
     * DESCRIPTION: Arcade drive, forward motion with left joystick, turn with 
     *              right joystick.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void arcadeDrive();

    /**************************************************************************
     * FUNCTION   : arcadeDrive
     *
     * DESCRIPTION: Arcade drive, forward motion with <movement>, turn with 
     *              <rotate>.
     *
     * RETURNS    : Void
     *************************************************************************/
	void arcadeDrive(double movement, double rotate);

    /**************************************************************************
     * FUNCTION   : stop
     *
     * DESCRIPTION: Stops the robot from driving.
     *
     * RETURNS    : Void
     *************************************************************************/
    void stop();

    /**************************************************************************
     * FUNCTION   : twoBtnDrive
     *
     * DESCRIPTION: Create movement value out of two buttons.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void twoBtnDrive();

private:
	float movementValue = 0.0;
	float rotationValue = 0.0;

	frc::DifferentialDrive *m_robotDrive;
	frc::Joystick *driveControllerMovement;
	frc::Joystick *driveControllerRotate;
    
    /**************************************************************************
     * FUNCTION   : twoBtnRotate
     *
     * DESCRIPTION: Create rotation value out of two buttons and joystick.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void twoBtnRotate();
    
    /**************************************************************************
     * FUNCTION   : setMovement
     *
     * DESCRIPTION: Update <movementValue> to be used for drive.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void setMovement();
    
    /**************************************************************************
     * FUNCTION   : setRotate
     *
     * DESCRIPTION: Update <rotateValue> to be used with drive.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void setRotate(bool rotateEn = true);
};

#endif /* ARCADE_DRIVER_HELPER_HPP */
