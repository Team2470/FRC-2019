//*****************************************************************************
// Filename:            ir_helper.hpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Feb. 2018  Initial design.
//
// Description:
//    This class operates a variety of infrared sensors, at varying distances.
// 
// Dependencies:
//    None
//*****************************************************************************

#ifndef IR_HELPER_HPP
#define IR_HELPER_HPP

/******************************************************************************
 * Include Files
 *****************************************************************************/
// First Includes //
#include <frc/AnalogInput.h>

/******************************************************************************
 * Constants
 *****************************************************************************/

/******************************************************************************
 * Types
 *****************************************************************************/
enum Infrared_Sensor_Type
	{
		GP2Y0A710K0F,	//3 - 18 feet
		GP2Y0A02YK0F,	//7 - 59 inches
		OPB732WZ		//up to 3 inches
	};

enum Color
	{
		BLACK,
		WHITE,
		GRAY
	};
    
/******************************************************************************
 * Variables
 *****************************************************************************/

/******************************************************************************
 * CLASS      : Infrared
 *
 * DESCRIPTION: This class is to operate a Infrared sensor.
 *
 * RETURNS    : None
 *****************************************************************************/
class Infrared
{
public:
    /**************************************************************************
     * FUNCTION   : Infrared
     *
     * DESCRIPTION: Constructs the Infrared object with the specified 
     *              <irChannel> and <irType>.
     *
     * RETURNS    : A Infrared object
     *************************************************************************/
	Infrared(int irChannel, Infrared_Sensor_Type irType);

	/**************************************************************************
	 * FUNCTION   : checkColor
	 *
	 * DESCRIPTION: Returns the current range in inches.
	 *
	 * RETURNS    : Range as a double
	 *************************************************************************/
	Color checkColor();

	/**************************************************************************
	 * FUNCTION   : irRange
	 *
	 * DESCRIPTION: Returns the current range in inches.
	 *
	 * RETURNS    : Range as a double
	 *************************************************************************/
	double irRange();

	/**************************************************************************
	 * FUNCTION   : Voltage
	 *
	 * DESCRIPTION: Returns the current voltage as read by the sensor.
	 *
	 * RETURNS    : Voltage as a double
	 *************************************************************************/
	double Voltage();

	/**************************************************************************
	 * FUNCTION   : AverageRaw
	 *
	 * DESCRIPTION: Returns the average raw value as read by the sensor.
	 *
	 * RETURNS    : value as an int
	 *************************************************************************/
	int AverageRaw();

private:
	double VOLTAGE_SCALING = 1.0;		//placeholder value
	double VOLTAGE_INTERCEPT = 1.0;		//placeholder value

	Infrared_Sensor_Type sensorFamily;

	frc::AnalogInput *irSensor;

	static constexpr double colorError = 0.1;
	static constexpr double whiteValue = 0.0;
	static constexpr double blackValue = 1.0;
	static constexpr double grayValue = 2.0;
};

#endif /* IR_HELPER_HPP */
