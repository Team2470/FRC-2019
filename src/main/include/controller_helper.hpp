/**
 * @enum        Axis_XBOX
 * @description Channels for all Xbox controller axes.
 */
enum Axis_XBOX
{
	XBOX_LEFT_JOYSTICK_X = 0,
	XBOX_LEFT_JOYSTICK_Y = 1,
	XBOX_LEFT_TRIGGER = 2,
	XBOX_RIGHT_TRIGGER = 3,
	XBOX_RIGHT_JOYSTICK_X = 4,
	XBOX_RIGHT_JOYSTICK_Y = 5
};

/**
 * @enum	Axis_LOGITECH
 * @description Channels for all Logitech controller axes.
 */
enum Axis_LOGITECH
{
	LOGITECH_LEFT_JOYSTICK_X = 0,
	LOGITECH_LEFT_JOYSTICK_Y = 1,
	LOGITECH_LEFT_TRIGGER = 2,
	LOGITECH_RIGHT_TRIGGER = 3,
	LOGITECH_RIGHT_JOYSTICK_X = 4,
	LOGITECH_RIGHT_JOYSTICK_Y = 5
};

/**
 * @enum	Button_XBOX
 * @description Channels for Xbox controller buttons.
 */
enum Button_XBOX
{
	XBOX_A = 1,
	XBOX_B = 2,
	XBOX_X = 3,
	XBOX_Y = 4,
	XBOX_LEFT_BUMPER = 5,
	XBOX_RIGHT_BUMPER = 6,
	XBOX_BACK = 7,
	XBOX_START = 8,
	XBOX_LEFT_JOYSTICK_PRESS = 9,
	XBOX_RIGHT_JOYSTICK_PRESS = 10
};

/**
 * @enum	Button_LOGITECH
 * @description Channels for Logitech controller buttons.
 */
enum Button_LOGITECH
{
	LOGITECH_A = 1,
	LOGITECH_B = 2,
	LOGITECH_X = 3,
	LOGITECH_Y = 4,
	LOGITECH_LEFT_BUMPER = 5,
	LOGITECH_RIGHT_BUMPER = 6,
	//LOGITECH_LEFT_TRIGGER = 7,
	//LOGITECH_RIGHT_TRIGGER = 8,
	LOGITECH_BACK = 7,
	LOGITECH_START = 8,
	LOGITECH_LEFT_JOYSTICK_PRESS = 9,
	LOGITECH_RIGHT_JOYSTICK_PRESS = 10
};

/**
 * @enum	DPad_XBOX
 * @description Values for the Xbox DPAD.
 */
enum DPad_XBOX
{
	XBOX_RELEASED = -1,
	XBOX_TOP = 0,
	XBOX_TOP_RIGHT = 45,
	XBOX_RIGHT = 90,
	XBOX_BOTTOM_RIGHT = 135,
	XBOX_BOTTOM = 180,
	XBOX_BOTTOM_LEFT = 225,
	XBOX_LEFT = 270,
	XBOX_TOP_LEFT = 315,
	XBOX_TRANSITION = 1,
	XBOX_STOP_BRAKE = 2
};

/**
 * @enum	DPad_XBOX
 * @description Values for the Logitech DPAD.
 */
enum DPad_LOGITECH
{
	LOGITECH_RELEASED = -1,
	LOGITECH_TOP = 0,
	LOGITECH_TOP_RIGHT = 45,
	LOGITECH_RIGHT = 90,
	LOGITECH_BOTTOM_RIGHT = 135,
	LOGITECH_BOTTOM = 180,
	LOGITECH_BOTTOM_LEFT = 225,
	LOGITECH_LEFT = 270,
	LOGITECH_TOP_LEFT = 315,
	LOGITECH_TRANSITION = 1,
	LOGITECH_STOP_BRAKE = 2
};

/**
 * @enum	Axis_Generic.
 * @description Generic axes.
 */
enum Axis_Generic
{
	JOYSTICK_Y_AXIS = 0,
	JOYSTICK_X_AXIS = 1,
};

/**
 * @enum	Generic_Controller_Left
 * @description Generic input channels for the left controller.
 */
enum Generic_Controller_Left
{
	BUTTON_BLUE_TOP_LEFT = 1,     //Generic Arcade Buttons
	BUTTON_BLUE_TOP_RIGHT = 2,    //Generic Arcade Buttons
	BUTTON_BLUE_BOTTOM_LEFT = 3,  //Generic Arcade Buttons
	BUTTON_BLUE_BOTTOM_RIGHT = 4, //Generic Arcade Buttons
	SWITCH_ARCADE_RIGHT = 5,      //Covered Switch
	SWITCH_ARCADE_LEFT = 6,	      //Covered Switch
	SWITCH_B = 7,		      //Generic Switch
	SWITCH_A = 8,		      //Generic Switch
	//ROTARY_SELECT		      //Probably will be used for autonomous selection, it is the knob with 10 different positions.
};

/**
 * @enum	Generic_Controller_Right
 * @description Generic input channels for the right controller.
 */
enum Generic_Controller_Right
{
	BUTTON_RED_TOP = 1,    //Generic Arcade Buttons
	BUTTON_RED_LEFT = 2,   //Generic Arcade Buttons
	BUTTON_RED_RIGHT = 3,  //Generic Arcade Buttons
	BUTTON_RED_BOTTOM = 4, //Generic Arcade Buttons
	BUTTON_FIRE = 5,       //Elevator Style Buttons
	BUTTON_RELEASE = 6,    //Elevator Style Buttons
	SWITCH_SAFE1 = 7,      //Covered Switch
	SWITCH_SAFE2 = 8,      //Covered Switch
	SWITCH_X = 9,	       //Generic Switch
	SWITCH_Y = 10,	       //Generic Switch
	SWITCH_SAFE3 = 11      //Locking Switch
};
