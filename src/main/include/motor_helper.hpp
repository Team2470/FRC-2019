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
 * @enum 	    MotorType
 * @description Contains all the types of motors.
 */
enum MotorType
{
	TALON,
	VICTOR,
	VICTOR_SP,
	SPARK
};

/**
 * @enum	    BehaviorType
 * @description Describes the two behaviors for motors.
 */
enum BehaviorType
{
	Maintain = true,
	Stop = false
};

/**
 * @enum	    VelocityState
 * @description Describes the two states for motors.
 */
enum VelocityState
{
	Constant = 1,
	Accelerate = 2
};

/**
 * @class       Motor
 * @description This class is used to operate a single motor, acceleration, deceleration, velocity
 *		        control, etc. It also contains a number of querying capabilities. It supports motors
 *		        of the types TALON, VICTOR, VICTOR_SP, and SPARK.
 */
class Motor
{
public:
	VelocityState motorState;

	/**
	 * @constructor Motor
	 * @description Constructs a Motor object.
	 * @param	    motorChannel -- The channel of the motor.
	 * @param	    motorType    -- The type of motor.
	 */
	Motor(int motorChannel, MotorType motorType);
    
	/**
	 * @function    gradualRotation
	 * @description Changes the speed of a motor over a specified time interval, changing the
	 *		        motor to a new specified behavior when the new speed is reached.
	 * @param       motorMaxSpeed 	      -- The new speed of the motor.
	 * @param	    speedIncreaseDuration -- The duration of time over which to increase the speed.
	 * @param 	    newBehavior	          -- The new behavior.
	 */
	void gradualRotation(
		double motorMaxSpeed,
		double speedIncreaseDuration,
		BehaviorType newBehavior = Maintain
	);
	
	/**
	 * @function	instantaneousRotation
	 * @description Instantly set the motor to a specified speed.
	 * @param	    motorSpeed -- The new speed of the motor.
	 */
	void instantaneousRotation(double motorSpeed);
    
	/**
	 * @function	instantaneousStop
	 * @description Instantly set the speed of the motor to zero.
	 */
	void instantaneousStop();
    
	/**
	 * @function    getSpeed
	 * @description Obtain the current speed of the motor, in the range [-1.0, 1.0].
	 * @returns     The speed of the motor as a double.
	 */
	double getSpeed();

	/**
	 * @function    maintainSpeed
	 * @description Maintain the current speed of the motor.
	 */
	void maintainSpeed();

	/**
	 * @function    resetAccelerate
	 * @description Reset class after accelerating.
	 * @param       forceReset -- Whether or not to force the reset.
	 */
	void resetAccelerate(bool forceReset = false);

	/**
	 * @function    brake
	 * @description Hold the motor in place -- a brake.
	 */
	void brake();

	/**
	 * @function    slowSpeed
	 * @description Accelerate or decelerate the motor over a specific period.
	 * @param	period 	    -- The period over which to perform the speed change.
	 * @param	changeSpeed -- The change in speed to perform.
	 * @param	multiplier  -- Increases or decreases the period.
	 */
	void slowSpeed(double period, double changeSpeed, double multiplier = 1);

private:
    BehaviorType accelBehavior;
	MotorType motorFamily;
	frc::Talon* motorTalon;
	frc::Victor* motorVictor;
	frc::VictorSP* motorVictorSP;
	frc::Spark* motorSpark;
	frc::PWMSpeedController* pwmMotor;
	frc::Timer clock;

	bool gradualMaxSpeedReached = false;
	bool firstRun;
	int testSpeed = 1;
	double gradualMaxSpeed = 0;
	double gradualCurrentSpeed = 0;
	double gradualRoundedSpeed = 0;
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
	
	/**
	 * @function    accelerateMotor
	 * @description Accelerate the motor at a constant rate.
	 */
	void accelerateMotor();

};

#endif
