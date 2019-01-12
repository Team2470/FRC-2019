//*****************************************************************************
// Filename:            sonar_helper.hpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2018  Initial design.
//
// Description:
//    This class operates a MaxSonar, Ultrasonic Senor such as the following:
//        LV, HRLV, HRUSB, XL
//    The class has the ability to return the current distance.
// 
// Dependencies:
//    None
//*****************************************************************************

#ifndef SONAR_HELPER_HPP
#define SONAR_HELPER_HPP

/******************************************************************************
 * Include Files
 *****************************************************************************/
 // First Includes
#include <frc/Ultrasonic.h>
#include <frc/AnalogInput.h>

/******************************************************************************
 * Constants
 *****************************************************************************/

/******************************************************************************
 * Types
 *****************************************************************************/
enum Ultrasonic_Sensor_Type
{
	HRLV,
	HRUSB,
	LV,
	XL
};
    
/******************************************************************************
 * Variables
 *****************************************************************************/

/******************************************************************************
 * CLASS      : MaxSonar
 *
 * DESCRIPTION: This class is to operate a PWM Motor.
 *
 * RETURNS    : None
 *****************************************************************************/
class MaxSonar
{
public:
    /**************************************************************************
     * FUNCTION   : MaxSonar
     *
     * DESCRIPTION: Constructs the MaxSonar object with the specified 
     *              <ultrasonicChannel> and <sonarType>.
     *
     * RETURNS    : A MaxSonar object
     *************************************************************************/
	MaxSonar(int ultrasonicChannel, Ultrasonic_Sensor_Type sonarType);

    /**************************************************************************
     * FUNCTION   : sonarRange
     *
     * DESCRIPTION: Returns the current distance as read by the sensor.
     *
     * RETURNS    : Distance as a double (inches)
     *************************************************************************/
	double sonarRange();

	/**************************************************************************
	 * FUNCTION   : Voltage
	 *
	 * DESCRIPTION: Returns the current voltage as read by the sensor.
	 *
	 * RETURNS    : Voltage as a double
	 *************************************************************************/
	double Voltage();

private:
	double VOLTAGE_SCALING = 0.0098;		//Roughly 9.8mV per inch

	Ultrasonic_Sensor_Type sensorFamily;

	frc::AnalogInput *ultrasonicSensor;
};

#endif /* SONAR_HELPER_HPP */
