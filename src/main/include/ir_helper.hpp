#ifndef IR_HELPER_HPP
#define IR_HELPER_HPP

#include <frc/AnalogInput.h>

/**
 * @enum	Infrared_Sensor_Type
 * @description Holds the different types of infrared sensor.
 */
enum Infrared_Sensor_Type
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
	Infrared(int irChannel, Infrared_Sensor_Type irType);

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
	double VOLTAGE_SCALING = 1.0;
	double VOLTAGE_INTERCEPT = 1.0;
	Infrared_Sensor_Type sensorFamily;
	frc::AnalogInput* irSensor;

	static constexpr double colorError = 0.1;
	static constexpr double whiteValue = 0.0;
	static constexpr double blackValue = 1.0;
	static constexpr double grayValue = 2.0;
};

#endif
