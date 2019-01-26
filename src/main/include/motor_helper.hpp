#ifndef MOTOR_HELPER_HPP
#define MOTOR_HELPER_HPP

#include <frc/Timer.h>
#include <frc/PWMSpeedController.h>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Spark.h>
#include <frc/Victor.h>
#include <frc/VictorSP.h>
#include <frc/Talon.h>

/**
 * @enum 	Motor_Type
 * @description Contains all the types of motors.
 */
enum Motor_Type
{
	TALON,
	VICTOR,
	VICTOR_SP,
	SPARK
};

/**
 * @enum	Behavior_Type
 * @description Describes the two behaviors for motors.
 */
enum Behavior_Type
{
	Maintain = true,
	Stop = false
};

/**
 * @enum	Velocity_State
 * @description Describes the two states for motors.
 */
enum Velocity_State
{
	Constant = 1,
	Accelerate = 2
};

/**
 * @class
 * @description This class is used to operate a single motor, acceleration, deceleration, velocity
 *		control, etc. It also contains a number of querying capabilities. It supports motors
 *		of the types TALON, VICTOR, VICTOR_SP, and SPARK.
 */
class Motor
{
public:
	Velocity_State motorState;

	/**
	 * @constructor Motor
	 * @description Constructs a Motor object.
	 * @param	motorChannel -- The channel of the motor.
	 * @param	motorType    -- The type of motor.
	 */
	Motor(int motorChannel, Motor_Type motorType);
    
	/**
	 * @function    GradualRotation
	 * @description Changes the speed of a motor over a specified time interval, changing the
	 		motor to a new specified behavior when the new speed is reached.
	 * @param       motorMaxSpeed 	      -- The new speed of the motor.
	 * @param	speedIncreaseDuration -- The duration of time over which to increase the speed.
	 * @param 	newBehavior	      -- The new behavior.
	 */
	void GradualRotation(
		double motorMaxSpeed,
		double speedIncreaseDuration,
		Behavior_Type newBehavior = Maintain
	);
	
	/**
	 * @function	InstantaneousRotation
	 * @description Instantly set the motor to a specified speed.
	 * @param	motorSpeed -- The new speed of the motor.
	 */
	void InstantaneousRotation(double motorSpeed);
    
	/**
	 * @function	InstantaneousStop
	 * @description Instantly set the speed of the motor to zero.
	 */
	void InstantaneousStop();
    
	/**
	 * @function    GetSpeed
	 * @description Obtain the current speed of the motor, in the range [-1.0, 1.0].
	 * @returns     The speed of the motor as a double.
	 */
	double GetSpeed();

	/**
	 * @function    MaintainSpeed
	 * @description Maintain the current speed of the motor.
	 */
	void MaintainSpeed();

	/**
	 * @function    ResetAccelerate
	 * @description Reset class after accelerating.
	 * @param       forceReset -- Whether or not to force the reset.
	 */
	void ResetAccelerate(bool forceReset = false);

	/**
	 * @function    Brake
	 * @description Hold the motor in place -- a brake.
	 */
	void Brake();

	/**
	 * @function    SlowSpeed
	 * @description Accelerate or decelerate the motor over a specific period.
	 * @param	period 	    -- The period over which to perform the speed change.
	 * @param	changeSpeed -- The change in speed to perform.
	 * @param	multiplier  -- Increases or decreases the period.
	 */
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
	
	/**
	 * @function    AccelerateMotor
	 * @description Accelerate the motor at a constant rate.
	 */
	void AccelerateMotor();

};

#endif
