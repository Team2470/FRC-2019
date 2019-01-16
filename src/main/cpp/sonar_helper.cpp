//*****************************************************************************
// Filename:            sonar_helper.cpp
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

/******************************************************************************
 * Include Files
 *****************************************************************************/
//System Includes
#include <iostream>

// First Includes
#include <frc/AnalogInput.h>
#include <frc/Ultrasonic.h>

//Our Includes
#include "sonar_helper.hpp"

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    MaxSonar
 *---------------------------------------------------------------------------*/
MaxSonar::MaxSonar(int ultrasonicChannel, Ultrasonic_Sensor_Type sonarType)
{
    ultrasonicSensor = new frc::AnalogInput(ultrasonicChannel);
    sensorFamily = sonarType;
    
    switch(sensorFamily)
	{
	case HRLV :
		VOLTAGE_SCALING = (1 / 41.0105);//0.00096063044;
		break;
	case HRUSB : VOLTAGE_SCALING = 1;
		break;
	case LV : VOLTAGE_SCALING = 0.0098;
		break;
	case XL : VOLTAGE_SCALING = 1;
		break;
	default : VOLTAGE_SCALING = 1;
		break;
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    sonarRange
 *---------------------------------------------------------------------------*/
double MaxSonar::sonarRange()
{
	//Gets the ultrasonic sensor voltage and converts it into inches
	double rangeInches = 0.0;
	rangeInches = ultrasonicSensor->GetVoltage() / VOLTAGE_SCALING;
	return rangeInches;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    Voltage
 *---------------------------------------------------------------------------*/
double MaxSonar::Voltage()
{
	double volt = 0;
	volt = ultrasonicSensor->GetVoltage();
	return volt;
}
