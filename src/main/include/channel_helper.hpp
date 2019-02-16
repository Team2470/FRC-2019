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
	FRONT_LEFT_MOTOR = 0,
	BACK_LEFT_MOTOR = 1,
	FRONT_RIGHT_MOTOR = 2,
	BACK_RIGHT_MOTOR = 3,
	LEFT_INTAKE_MOTOR = 4,
	RIGHT_INTAKE_MOTOR = 5,
	PLACEHOLDER_MOTOR = 10
};

/**
 * @enum	    ChannelAnalog
 * @description Holds the channels for all analog sensors.
 */
enum ChannelAnalog
{
	//gyro slot 0 or 1?
	GYRO_SENSOR = 0,
	ULTRASONIC_SENSOR_HATCH = 1, //placeholder
};

/**
 * @enum	    ChannelDigital
 * @description Holds the channels for all digital sensors.
 */
enum ChannelDigital
{
	PLEXIGLASS_LIGHT_CONTROL = 0,
	FRONT_LEFT_ENCODER_CHANNEL_A = 1,
	FRONT_LEFT_ENCODER_CHANNEL_B = 2,
	BACK_LEFT_ENCODER_CHANNEL_A = 3,
	BACK_LEFT_ENCODER_CHANNEL_B = 4,
	FRONT_RIGHT_ENCODER_CHANNEL_A = 5,
	FRONT_RIGHT_ENCODER_CHANNEL_B = 6,
	BACK_RIGHT_ENCODER_CHANNEL_A = 7,
	BACK_RIGHT_ENCODER_CHANNEL_B = 8
};

/**
 * @enum	    ChannelSolenoid
 * @description Holds the channels for all solenoids.
 */
enum ChannelSolenoid
{
	FRONT_LEFT_SOLENOID = 0,	//Single Solenoid
	BACK_LEFT_SOLENOID = 1,		//Single Solenoid
	FRONT_RIGHT_SOLENOID = 2,	//Single Solenoid
	BACK_RIGHT_SOLENOID = 3,	//Single Solenoid
	HATCH_EXTEND_SOLENOID = 4,	//Single Solenoid
	HATCH_POP_SOLENOID = 5,		//Single Solenoid
	CLIMBER_EXTEND = 6			//Single Solenoid
};

/**
 * @enum	    ChannelPDP
 * @description Holds the PDP channels for motors.
 */
enum ChannelPDP
{
	PDP_FRONT_LEFT_MOTOR = 1,
	PDP_BACK_LEFT_MOTOR = 14,
	PDP_FRONT_RIGHT_MOTOR = 0,
	PDP_BACK_RIGHT_MOTOR = 15,
	PDP_INTAKE_LEFT_MOTOR = 4,
	PDP_INTAKE_RIGHT_MOTOR = 5,
	PDP_LIMELIGHT_CAMERA = 6
};
