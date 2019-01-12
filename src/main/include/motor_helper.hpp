//*****************************************************************************
// Filename:            motor_helper.hpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2018  Initial design.
//
// Description:
//    This class operates a PWM Motor such as the following drivers:
//        Spark, Talon, Victor, VictorSP
//    The class has the ability to drive the motor cw and ccw as well as
//        accelerating/decelerating and reading the current speed.
// 
// Dependencies:
//    None
//*****************************************************************************

#ifndef MOTOR_HELPER_HPP
#define MOTOR_HELPER_HPP

/******************************************************************************
 * Include Files
 *****************************************************************************/
// System Includes
#include <Timer.h>

// FIRST Includes
#include <frc/PWMSpeedController.h>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Spark.h>
#include <frc/Victor.h>
#include <frc/VictorSP.h>
#include <frc/Talon.h>

/******************************************************************************
 * Constants
 *****************************************************************************/

/******************************************************************************
 * Types
 *****************************************************************************/
enum Motor_Type
{
	TALON,
	VICTOR,
	VICTOR_SP,
	SPARK
};

enum Behavior_Type
{
	Maintain = true,
	Stop = false
};

enum Velocity_State
{
	Constant = 1,
	Accelerate = 2
};

/******************************************************************************
 * CLASS      : Motor
 *
 * DESCRIPTION: This class is to operate a PWM Motor.
 *
 * RETURNS    : None
 *****************************************************************************/
class Motor
{
public:

	/******************************************************************************
	 * Variables
	 *****************************************************************************/
	Velocity_State motorState;

    /**************************************************************************
     * FUNCTION   : Motor
     *
     * DESCRIPTION: Constructs the PWM Motor object with the specified 
     *              <motorChannel> and <motorType>.
     *
     * RETURNS    : A PWM SpeedController object
     *************************************************************************/
	Motor(int motorChannel, Motor_Type motorType);
    
    /**************************************************************************
     * FUNCTION   : GradualRotation
     *
     * DESCRIPTION: Changes the speed from the current speed to <motorMaxSpeed>
     *              at a constant rate over <speedIncreaseDuration> seconds.
     *              Once reaching the <motorMaxSpeed> the motor will continue
     *              at <newBehavior>.
     *              ResetAcceleration should be run prior to GradualRotation.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void GradualRotation(double motorMaxSpeed,
					     double speedIncreaseDuration,
						 Behavior_Type newBehavior = Maintain);
    
    /**************************************************************************
     * FUNCTION   : InstantaneousRotation
     *
     * DESCRIPTION: Sets the speed to <motorSpeed>.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void InstantaneousRotation(double motorSpeed);
    
    /**************************************************************************
     * FUNCTION   : InstantaneousStop
     *
     * DESCRIPTION: Sets the speed to 0.0 (stop).
     *
     * RETURNS    : Void
     *************************************************************************/	
	void InstantaneousStop();
    
    /**************************************************************************
     * FUNCTION   : GetSpeed
     *
     * DESCRIPTION: Returns the current speed of the motor.
     *
     * RETURNS    : Speed as double (-1.0 to 1.0)
     *************************************************************************/	
	double GetSpeed();

    /**************************************************************************
     * FUNCTION   : MaintainSpeed
     *
     * DESCRIPTION: Maintains the current speed of the motor.
     *
     * RETURNS    : Speed as double (-1.0 to 1.0)
     *************************************************************************/
	void MaintainSpeed();

	/**************************************************************************
	 * FUNCTION   : ResetAccelerate
	 *
	 * DESCRIPTION: Reset class after accelerating.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void ResetAccelerate(bool forceReset = false);

	/**************************************************************************
	 * FUNCTION   : Brake
	 *
	 * DESCRIPTION: Holds the motor in place
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void Brake();

	/**************************************************************************
	 * FUNCTION   : SlowSpeed
	 *
	 * DESCRIPTION: Moves motor with an offset
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void SlowSpeed(double period, double changeSpeed, double multiplier = 1);

private:
	Motor_Type motorFamily;
	frc::Talon* motorTalon;
	frc::Victor* motorVictor;
	frc::VictorSP* motorVictorSP;
	frc::Spark* motorSpark;
	frc::PWMSpeedController* pwmMotor;
	frc::Timer clock;

	bool gradual_MaxSpeedReached = false;
	bool firstRun;
	int testSpeed = 1;
	double gradual_MaxSpeed = 0;
	double gradual_CurrentSpeed = 0;
	double gradual_RoundedSpeed = 0;
	double speedIncreaseRate = 0;
	double brakeMotorSpeed = 0.15;

	double lastTime = 0;
	double currentTime = 0;
	double brakeTimeLast = 0;
	double brakeTimeCurrent = 0;
	double slowTimeLast = 0;
	double slowTimeCurrent = 0;

	double timeOn = 0;
	double timeOff = 0;
	bool slowStatus = false;

	Behavior_Type accelBehavior;


    /**************************************************************************
     * FUNCTION   : AccelerateMotor
     *
     * DESCRIPTION: Accelerates the motor at a constant rate based on
     *              speedIncreaseRate.
     *
     * RETURNS    : Void
     *************************************************************************/	
	void AccelerateMotor();

};

#endif /* MOTOR_HELPER_HPP */
