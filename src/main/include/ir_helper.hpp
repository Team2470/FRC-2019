#ifndef IR_HELPER_HPP
#define IR_HELPER_HPP

#include <frc/AnalogInput.h>

/**
 * @enum	InfraredSensorType
 * @description Holds the different types of infrared sensor.
 */
enum InfraredSensorType
{
	GP2Y0A710K0F, // 3 - 18 feet
	GP2Y0A02YK0F, // 7 - 59 inches
	OPB732WZ      // up to 3 inches
};

/**
 * @enum	Color
 * @description Holds three different colors.
 */
enum Color
{
	BLACK,
	WHITE,
	GRAY
};

/**
 * @class 	Infrared
 * @description This class operates an infrared sensor.
 */
class Infrared
{
public:
	/**
	 * @constructor Infrared
	 * @description Constructs the Infrared object.
	 * @param	irChannel -- the input channel of the sensor.
	 * @param	irType    -- the type of sensor.
	 */
	Infrared(int irChannel, InfraredSensorType irType);

	/**
	 * @function    checkColor
	 * @description Attempt to read the current color value from the IR sensor.
	 * @returns     The registered color value in enumeration form.
	 */
	Color checkColor();

	/**
	 * @function    irRange
	 * @description Reads a distance value from the infrared sensor.
	 * @returns     The read distance value.
	 */
	double irRange();

	/**
	 * @function    voltage
	 * @description Reads the current voltage of the IR sensor.
	 * @returns     The read voltage.
	 */
	double voltage();
	
	/**
	 * @function    averageRaw
	 * @description Calculates the average value read by the sensor.
	 * @returns     The calculated average value.
	 */
	int averageRaw();

private:
	static constexpr double COLOR_ERROR = 0.1;
	static constexpr double WHITE_VALUE = 0.0;
	static constexpr double BLACK_VALUE = 1.0;
	static constexpr double GRAY_VALUE = 2.0;
    
	double voltageScaling = 1.0;
	double voltageIntercept = 1.0;

    InfraredSensorType sensorFamily;
	frc::AnalogInput* irSensor;
};

#endif
