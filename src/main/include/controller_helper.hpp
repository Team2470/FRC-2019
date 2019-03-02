/**
 * @enum        AxisXbox
 * @description Channels for all Xbox controller axes.
 */
enum AxisXbox
{
	XBOX_LEFT_JOYSTICK_X = 0,
	XBOX_LEFT_JOYSTICK_Y = 1,
	XBOX_LEFT_TRIGGER = 2,
	XBOX_RIGHT_TRIGGER = 3,
	XBOX_RIGHT_JOYSTICK_X = 4,
	XBOX_RIGHT_JOYSTICK_Y = 5
};

/**
 * @enum	    AxisLogitech
 * @description Channels for all Logitech controller axes.
 */
enum AxisLogitech
{
	LOGITECH_LEFT_JOYSTICK_X = 0,
	LOGITECH_LEFT_JOYSTICK_Y = 1,
	LOGITECH_LEFT_TRIGGER = 2,
	LOGITECH_RIGHT_TRIGGER = 3,
	LOGITECH_RIGHT_JOYSTICK_X = 4,
	LOGITECH_RIGHT_JOYSTICK_Y = 5
};

/**
 * @enum	    ButtonXbox
 * @description Channels for Xbox controller buttons.
 */
enum ButtonXbox
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
 * @enum	    ButtonLogitech
 * @description Channels for Logitech controller buttons.
 */
enum ButtonLogitech
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
 * @enum	    ButtonFlight
 * @description Channels for Flight Joystick buttons.
 */
enum ButtonFlight
{
	FLIGHT_TRIGGER = 1,
	FLIGHT_BALL = 2
};

/**
 * @enum	    DPadXbox
 * @description Values for the Xbox DPAD.
 */
enum DPadXbox
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
 * @enum	    DPadLogitech
 * @description Values for the Logitech DPAD.
 */
enum DPadLogitech
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
 * @enum	    AxisGeneric
 * @description Generic axis.
 */
enum AxisGeneric
{
	JOYSTICK_Y_AXIS = 0,
	JOYSTICK_X_AXIS = 1
};

/**
 * @enum	    AxisFlight
 * @description Flight Joystick axis.
 */
enum AxisFlight
{
	FLIGHT_X_AXIS = 0,
	FLIGHT_Y_AXIS = 1
};

/**
 * @enum	    GenericControllerLeft
 * @description Generic input channels for the left controller.
 */
enum GenericControllerLeft
{
	BUTTON_BLUE_TOP_LEFT = 1,     // Generic Arcade Buttons
	BUTTON_BLUE_TOP_RIGHT = 2,    // Generic Arcade Buttons
	BUTTON_BLUE_BOTTOM_LEFT = 3,  // Generic Arcade Buttons
	BUTTON_BLUE_BOTTOM_RIGHT = 4, // Generic Arcade Buttons
	SWITCH_ARCADE_RIGHT = 5,      // Covered Switch
	SWITCH_ARCADE_LEFT = 6,	      // Covered Switch
	SWITCH_B = 7,		          // Generic Switch
	SWITCH_A = 8,		          // Generic Switch
	//ROTARY_SELECT		          // Probably will be used for autonomous selection, it is the knob with 10 different positions.
};

/**
 * @enum	    GenericControllerRight
 * @description Generic input channels for the right controller.
 */
enum GenericControllerRight
{
	BUTTON_RED_TOP = 1,    // Generic Arcade Buttons
	BUTTON_RED_LEFT = 2,   // Generic Arcade Buttons
	BUTTON_RED_RIGHT = 3,  // Generic Arcade Buttons
	BUTTON_RED_BOTTOM = 4, // Generic Arcade Buttons
	BUTTON_FIRE = 5,       // Elevator Style Buttons
	BUTTON_RELEASE = 6,    // Elevator Style Buttons
	SWITCH_COVERED_SAFE1 = 7,      // Covered Switch
	SWITCH_COVERED_SAFE2 = 8,      // Covered Switch
	SWITCH_X = 9,	       // Generic Switch
	SWITCH_Y = 10,	       // Generic Switch
	SWITCH_LOCKING_SAFE3 = 11      // Locking Switch
};

/**
 * @enum	    RotarySwitch
 * @description The channels for the rotary switch .
 */
enum RotarySwitch
{
	RIGHT_HUB_TOP_JOYSTICK_POSITIVE_X = 1,
	RIGHT_HUB_TOP_JOYSTICK_NEGATIVE_X = 2,
	RIGHT_HUB_TOP_JOYSTICK_POSITIVE_Y = 3,
	RIGHT_HUB_TOP_JOYSTICK_NEGATIVE_Y = 4,
	RIGHT_HUB_LEFT_JOYSTICK_POSITIVE_X = 5,
	RIGHT_HUB_LEFT_JOYSTICK_NEGATIVE_X = 6,
	RIGHT_HUB_LEFT_JOYSTICK_POSITIVE_Y = 7,
	RIGHT_HUB_LEFT_JOYSTICK_NEGATIVE_Y = 8,
	LEFT_HUB_TOP_JOYSTICK_POSITIVE_X = 9,
	EMPTY = 10
};
