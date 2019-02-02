#ifndef SONAR_HELPER_HPP
#define SONAR_HELPER_HPP

#include <frc/Ultrasonic.h>
#include <frc/AnalogInput.h>

/**
 * @enum 	UltrasonicSensorType
 * @description Holds the four different supported ultrasonic sensor types.
 */ 
enum UltrasonicSensorType
{
	HRLV,
	HRUSB,
	LV,
	XL
};

/**
 * @class 	MaxSonar
 * @description This class operates a MaxSonar, Ultrasonic Senor such as the following:
 * 		   LV, HRLV, HRUSB, XL
 *		This class has the ability to return the current distance.
 */
class MaxSonar
{
public:
	/**
	 * @constructor MaxSonar
	 * @description Constructs a MaxSonar object.
	 * @param	ultrasonicChannel -- the analog channel for the ultrasonic sensor.
	 * @param	sonarType	  -- the category of ultrasonic sensor.
	 */
    MaxSonar(int ultrasonicChannel, UltrasonicSensorType sonarType);

    	/**
 	* @function    sonarRange
 	* @description Calculates the current distance (inches) read by the sensor.
 	* @returns     Returns the calculated distance.
 	*/
	double sonarRange();

	/**
	 * @function    voltage
	 * @description Calculates the current voltage (volts) read by the sensor.
	 * @returns     The calculated voltage.
	 */
	double voltage();

private:
	double VOLTAGE_SCALING = 0.0098; // Roughly 9.8mV per inch
	UltrasonicSensorType sensorFamily;
	frc::AnalogInput* ultrasonicSensor;
};

#endif
