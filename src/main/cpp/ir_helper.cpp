#include <iostream>
#include <frc/AnalogInput.h>
#include "ir_helper.hpp"

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

Color Infrared::checkColor()
{
	double irValue = voltage();
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

double Infrared::irRange()
{
	double rangeInches = 0.0;
	rangeInches = 1 / ( ( irSensor->GetVoltage() - VOLTAGE_INTERCEPT ) / ( VOLTAGE_SCALING * 0.393701) );
	return rangeInches;
}

double Infrared::voltage()
{
	double volt = 0;
	volt = irSensor->GetVoltage();
	return volt;
}

int Infrared::averageRaw()
{
	double volt = 0;
	volt = irSensor->GetAverageValue();
	return volt;
}
