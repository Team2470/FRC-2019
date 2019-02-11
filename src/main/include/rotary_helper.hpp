#ifndef ROTARY_HELPER_HPP
#define ROTARY_HELPER_HPP

#include <frc/Joystick.h>

/**
 * @enum 	Controller1
 * @description The first controller, controls (0 - 3)
 */ 
enum Controller1
{
	HRLV,
	HRUSB,
	LV,
	XL
};

/**
 * @class 	Rotary
 * @description This class operates a Rotary Switch
 *		This class has the ability to read joystick values to determine the current setting.
 */
class Rotary
{
public:
	/**
	 * @constructor Rotary
	 * @description Constructs a Rotary object.
	 * @param	controller1 -- The first joystick to read for values (0 - 3).
	 * @param	controller2 -- The second joystick to read for values (4 - 7).
	 * @param	controller3 -- The third joystick to read for values (8).
	 */
    Rotary(frc::Joystick* controller1, frc::Joystick* controller2, frc::Joystick* controller3);

	/**
 	 * @function    getActive
 	 * @description Calculates the current setting from joystick inputs.
 	 * @returns     Returns the active dial setting (int from 1 to 10).
 	 */
	int getActive();

	/**
	 * @function    updateValues
	 * @description Updates the values from joystick inputs.
	 */
	void updateValues();

private:
	bool valueList[10];
};

#endif
