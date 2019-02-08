#include <iostream>
#include <frc/AnalogInput.h>
#include "ir_helper.hpp"

Infrared::Infrared(int irChannel, InfraredSensorType irType)
{
    this->irSensor = new frc::AnalogInput(irChannel);
    this->sensorFamily = irType;
    
    switch(sensorFamily)
	{
		case InfraredSensorType::GP2Y0A710K0F:			//3-18 feet
			this->voltageScaling = 137.5;
			this->voltageIntercept = 1.125;
			break;

		case InfraredSensorType::GP2Y0A02YK0F:			//7-59 inches
			this->voltageScaling = 46.5909091;
			this->voltageIntercept = 0.33522727272;
			break;

		case InfraredSensorType::OPB732WZ:				// up to 3 inches
			this->voltageScaling = 1.0;
			this->voltageIntercept = 1.0;
			break;

		default:
			this->voltageScaling = 1.0;
			this->voltageIntercept = 1.0;
			break;
	}
}

Color Infrared::checkColor()
{
	double irValue = voltage();
	Color rtnColor;

	if(irValue <= (WHITE_VALUE + COLOR_ERROR) || irValue >= (WHITE_VALUE - COLOR_ERROR))
	{
		rtnColor = WHITE;
	}
	else if(irValue <= (BLACK_VALUE + COLOR_ERROR) || irValue >= (BLACK_VALUE - COLOR_ERROR))
	{
		rtnColor = BLACK;
	}
	else if(irValue <= (GRAY_VALUE + COLOR_ERROR) || irValue >= (GRAY_VALUE - COLOR_ERROR))
	{
		rtnColor = GRAY;
	}

	return rtnColor;
}

double Infrared::irRange()
{
	double rangeInches = 0.0;
	rangeInches = 1 / ((this->irSensor->GetVoltage() - voltageIntercept) / (voltageScaling * 0.393701));
	return rangeInches;
}

double Infrared::voltage()
{
	double volt = 0;
	volt = this->irSensor->GetVoltage();
	return volt;
}

int Infrared::averageRaw()
{
	double volt = 0;
	volt = this->irSensor->GetAverageValue();
	return volt;
}
