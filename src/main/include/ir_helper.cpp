//*****************************************************************************
// Filename:            ir_helper.cpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Feb. 2018  Initial design.
//
// Description:
//
//		f
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

//Our Includes
#include "ir_helper.hpp"

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    MaxSonar
 *---------------------------------------------------------------------------*/
Infrared::Infrared(int irChannel, Infrared_Sensor_Type irType)
{
    irSensor = new frc::AnalogInput(irChannel);
    sensorFamily = irType;
    
    switch(sensorFamily)
	{
	case GP2Y0A710K0F:			//3-18 feet
		VOLTAGE_SCALING = 137.5;
		VOLTAGE_INTERCEPT = 1.125;
		break;

	case GP2Y0A02YK0F:			//7-59 inches
		VOLTAGE_SCALING = 46.5909091;
		VOLTAGE_INTERCEPT = 0.33522727272;
		break;

	case OPB732WZ:				// up to 3 inches
		VOLTAGE_SCALING = 1.0;
		VOLTAGE_INTERCEPT = 1.0;
		break;

	default:
		VOLTAGE_SCALING = 1.0;
		VOLTAGE_INTERCEPT = 1.0;
		break;
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    checkColor
 *---------------------------------------------------------------------------*/
Color Infrared::checkColor()
{
	double irValue = Voltage();
	Color rtnColor;

	if (irValue <= (whiteValue + colorError) || irValue >= (whiteValue - colorError))
	{
		rtnColor = WHITE;
	}
	else if (irValue <= (blackValue + colorError) || irValue >= (blackValue - colorError))
	{
		rtnColor = BLACK;
	}
	else if (irValue <= (grayValue + colorError) || irValue >= (grayValue - colorError))
	{
		rtnColor = GRAY;
	}

	return rtnColor;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    irRange
 *---------------------------------------------------------------------------*/
double Infrared::irRange()
{
	//Gets the ir sensor voltage and converts it into inches
	double rangeInches = 0.0;
	rangeInches = 1 / ( ( irSensor->GetVoltage() - VOLTAGE_INTERCEPT ) / ( VOLTAGE_SCALING * 0.393701) );
	return rangeInches;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    Voltage
 *---------------------------------------------------------------------------*/
double Infrared::Voltage()
{
	double volt = 0;
	volt = irSensor->GetVoltage();
	return volt;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    AverageRaw
 *---------------------------------------------------------------------------*/
int Infrared::AverageRaw()
{
	double volt = 0;
	volt = irSensor->GetAverageValue();
	return volt;
}
