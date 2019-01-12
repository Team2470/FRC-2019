//*****************************************************************************
// Filename:            mecanum_driver_helper.hpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2019  Initial design.
//
// Description:
//    This class operates a SpeedController group using Mecanum Drive.
//    The class has the ability to drive using mecanum wheels.
// 
// Dependencies:
//    None
//*****************************************************************************

#ifndef MECANUM_DRIVER_HELPER_HPP
#define MECANUM_DRIVER_HELPER_HPP

/******************************************************************************
 * Include Files
 *****************************************************************************/
// FIRST Includes //
#include <frc/drive/MecanumDrive.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>

/******************************************************************************
 * Constants
 *****************************************************************************/

/******************************************************************************
 * Types
 *****************************************************************************/

/******************************************************************************
 * CLASS      : BjorgMecanumDrive
 *
 * DESCRIPTION: This class creates a MecanumDrive Object
 *
 * RETURNS    : None
 *****************************************************************************/
class BjorgMecanumDrive 
{
public:
	
    /**************************************************************************
     * Variables
     *************************************************************************/
	int moveCtrl 	 = 0;
    int shiftCtrl    = 0;
	int rotateCtrl 	 = 0;
	//int rtTurn		 = 0;
	//int lftTurn		 = 0;
	int fwdMove	     = 0;
	int bckMove	     = 0;
    int fwdShift	 = 0;
	int bckShift	 = 0;
    int fwdRotate    = 0;
	int bckRotate	 = 0;
	int joystickInt  = 0;
	int reverseDrive = -1;

	//bool rotateEnable = true;
	//bool sqrInputs	 = false;
	bool multiMove   = false;
    bool multiShift  = false;
    bool multiRotate = false;
	float motorMultiplier = 1.0;
    float shiftMultiplier = 1.0;
	float rotateMultiplier = 1.0;
	
    /**************************************************************************
     * FUNCTION   : BjorgMecanumDrive
     *
     * DESCRIPTION: Construct class BjorgMecanumDrive, set the motors to be used for 
     *              driving with <m_frontleftMotor>, <m_frontrightMotor>, <m_leftMotor>,
     *              and <m_leftMotor>. It also sets the Joystick used to drive <Joystick>.
     *
     * RETURNS    : A MecanumDrive object
     *************************************************************************/	
	BjorgMecanumDrive(frc::Spark *m_frontleftMotor, frc::Spark *m_backleftMotor, frc::Spark *m_frontrightMotor, frc::Spark *m_backrightMotor,
    frc::Joystick *moveController, frc::Joystick *shiftController, frc::Joystick *rotateController);

    /**************************************************************************
     * FUNCTION   : mecanumDrive
     *
     * DESCRIPTION: Mecanum drive, translational motion with right joystick,
     *              rotation with the left joystick.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void mecanumDrive();

    /**************************************************************************
     * FUNCTION   : mecanumDrive
     *
     * DESCRIPTION: Mecanum drive, translational motion with <movement>,
     *              rotational with <rotate>.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void mecanumDrive(double movement, double shift, double rotate);

    /**************************************************************************
     * FUNCTION   : twoBtnMove
     *
     * DESCRIPTION: Create movement value out of two buttons.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void twoBtnMove();

    /**************************************************************************
     * FUNCTION   : twoBtnShift
     *
     * DESCRIPTION: Create shift value out of two buttons.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void twoBtnShift();

    /**************************************************************************
     * FUNCTION   : twoBtnRotate
     *
     * DESCRIPTION: Create rotate value out of two buttons.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void twoBtnRotate();

private:
	float movementValue = 0.0;
    float shiftValue = 0.0;
	float rotateValue = 0.0;

	frc::MecanumDrive *m_robotDrive;
	frc::Joystick *driveControllerMove;
	frc::Joystick *driveControllerShift;
    frc::Joystick *driveControllerRotate;
    
    /**************************************************************************
     * FUNCTION   : twoBtnRotate
     *
     * DESCRIPTION: Create rotation value out of two buttons and joystick.
     *
     * RETURNS    : Void
     *************************************************************************/	
	//void twoBtnRotate();
    
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

#endif /* MECANUM_DRIVER_HELPER_HPP */
