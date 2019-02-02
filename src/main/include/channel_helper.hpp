/**
 * @enum 	ChannelController
 * @description Holds the controller input channels.
 * @notes       The number correlates to the 'USB Order' number on the driver station.
 *       		XBOX_CONTROLLER and LOGITECH_CONTROLLER should only be used when the 
 *		        Logitech or Xbox controllers are being used; if the 
 */
enum ChannelController
{
	XBOX_CONTROLLER = 0,				//When we are using the logitech and xbox controllers
	LOGITECH_CONTROLLER = 1,			//When we are using the logitech and xbox controllers
	//FLIGHT_JOYSTICK = 1,				//When we are using the driver station
	LEFT_DRIVE_JOYSTICK = 2,			//When we are using the driver station
	LEFT_BUTTON_HUB = 3,				//When we are using the driver station
	RIGHT_DRIVE_JOYSTICK = 4,			//When we are using the driver station
	RIGHT_BUTTON_HUB = 5				//When we are using the driver station
};

/**
 * @enum	    ChannelPWM
 * @description Holds the motor input channels.
 * @note	    Used when the Logitech and Xbox controllers are being utilized.
 */
enum ChannelPWM
{
	//LEFT_MOTOR = 0,
	//RIGHT_MOTOR = 1,
	FRONT_LEFT_MOTOR = 0,
	BACK_LEFT_MOTOR = 1,
	FRONT_RIGHT_MOTOR = 2,
	BACK_RIGHT_MOTOR = 3,
	INTAKE_MOTOR = 4,
	PLACEHOLDER_MOTOR = 10
};

/**
 * @enum	    ChannelAnalog
 * @description Holds the channels for all analog sensors.
 */
enum ChannelAnalog
{
	ULTRASONIC_SENSOR_FRONT_LEFT = 0 // TODO: ENSURE CORRECT CHANNEL FOR ULTRASONIC SENSOR
};

/**
 * @enum	    ChannelDigital
 * @description Holds the channels for all digital sensors.
 */
enum ChannelDigital
{
	//LIMITSWITCH_ROBOT = 1
};

/**
 * @enum	    ChannelSolenoid
 * @description Holds the channels for all solenoids.
 */
enum ChannelSolenoid
{
	FRONT_LEFT_SOLENOID = 0,
	BACK_LEFT_SOLENOID = 1,
	FRONT_RIGHT_SOLENOID = 2,
	BACK_RIGHT_SOLENOID = 3,
	EXTEND_SOLENOID = 4,
	HATCH_SOLENOID = 5
};

/**
 * @enum	    ChannelPDP
 * @description Holds the PDP channels for motors.
 */
enum ChannelPDP
{
	PDP_FRONT_LEFT_MOTOR = 0,
	PDP_BACK_LEFT_MOTOR = 1,
	PDP_FRONT_RIGHT_MOTOR = 2,
	PDP_BACK_RIGHT_MOTOR = 3,
	PDP_INTAKE_LEFT_MOTOR = 4,
	PDP_INTAKE_RIGHT_MOTOR = 5,
	PDP_LIMELIGHT_CAMERA = 6
};
