enum Channel_Controller
{
	//The number correlates to the 'USB Order' number on the driver station
	//XBOX_CONTROLLER = 0,				//When we are using the logitech and xbox controllers
	//LOGITECH_CONTROLLER = 1,			//When we are using the logitech and xbox controllers
	FLIGHT_JOYSTICK = 1,				//When we are using the driver station
	LEFT_DRIVE_JOYSTICK = 2,			//When we are using the driver station
	LEFT_BUTTON_HUB = 3,				//When we are using the driver station
	RIGHT_DRIVE_JOYSTICK = 4,			//When we are using the driver station
	RIGHT_BUTTON_HUB = 5				//When we are using the driver station
};

enum Channel_PWM
{
	//Channels for the PWM motors on the roboRIO
	//For when we are using the logitech and xbox controllers
	//LEFT_MOTOR = 0,
	//RIGHT_MOTOR = 1,
	//placeholder values
	FRONT_LEFT_MOTOR = 0,
	BACK_LEFT_MOTOR = 1,
	FRONT_RIGHT_MOTOR = 2,
	BACK_RIGHT_MOTOR = 3,
	INTAKE_MOTOR = 4,
	PLACEHOLDER_MOTOR = 10
};

enum Channel_Analog
{
	//Channels for the analog sensors on the roboRIO
	//ULTRASONIC_SENSOR_FRONT_LEFT = 0
};

enum Channel_Digital
{
	//Channels for the digital sensors on the roboRIO
	//LIMITSWITCH_ROBOT = 1
};

enum Channel_Solenoid
{
	//Channels for the solenoids on the PCM
	FRONT_LEFT_SOLENOID = 0,
	BACK_LEFT_SOLENOID = 1,
	FRONT_RIGHT_SOLENOID = 2,
	BACK_RIGHT_SOLENOID = 3,
	EXTEND_SOLENOID = 4,
	HATCH_SOLENOID = 5
};

enum Channel_PDP
{
	FRONT_LEFT_MOTOR = 0,
	BACK_LEFT_MOTOR = 1,
	FRONT_RIGHT_MOTOR = 2,
	BACK_RIGHT_MOTOR = 3,
	INTAKE_MOTOR = 4
}
