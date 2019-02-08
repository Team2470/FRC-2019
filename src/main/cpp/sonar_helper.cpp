#include <iostream>
#include <frc/AnalogInput.h>
#include <frc/Ultrasonic.h>
#include "sonar_helper.hpp"

MaxSonar::MaxSonar(int ultrasonicChannel, UltrasonicSensorType sonarType)
{
    this->ultrasonicSensor = new frc::AnalogInput(ultrasonicChannel);
    this->sensorFamily = sonarType;
    
    switch(sensorFamily)
	{
		case UltrasonicSensorType::HRLV:
			this->voltageScaling = 1 / 41.0105;
			break;
		case UltrasonicSensorType::HRUSB: 
			this->voltageScaling = 1;
			break;
		case UltrasonicSensorType::LV: 
			this->voltageScaling = 0.0098;
			break;
		case UltrasonicSensorType::XL: 
			this->voltageScaling = 1;
			break;
		default: 
			this->voltageScaling = 1;
			break;
	}
}

double MaxSonar::sonarRange()
{
	double rangeInches = 0.0;
	rangeInches = this->ultrasonicSensor->GetVoltage() / this->voltageScaling;
	return rangeInches;
}

double MaxSonar::voltage()
{
	double volt = 0;
	volt = this->ultrasonicSensor->GetVoltage();
	return volt;
}
