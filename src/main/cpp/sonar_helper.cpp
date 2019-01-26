#include <iostream>
#include <frc/AnalogInput.h>
#include <frc/Ultrasonic.h>
#include "sonar_helper.hpp"

MaxSonar::MaxSonar(int ultrasonicChannel, Ultrasonic_Sensor_Type sonarType)
{
<<<<<<< HEAD
    	ultrasonicSensor = new frc::AnalogInput(ultrasonicChannel);
    	sensorFamily = sonarType;
    
    	switch(sensorFamily)
=======
	ultrasonicSensor = new frc::AnalogInput(ultrasonicChannel);
	sensorFamily = sonarType;
    
	switch(sensorFamily)
>>>>>>> master
	{
		case HRLV:
			VOLTAGE_SCALING = (1 / 41.0105);//0.00096063044;
			break;
		case HRUSB: 
			VOLTAGE_SCALING = 1;
			break;
		case LV: 
			VOLTAGE_SCALING = 0.0098;
			break;
		case XL: 
			VOLTAGE_SCALING = 1;
			break;
		default: 
			VOLTAGE_SCALING = 1;
			break;
	}
}

double MaxSonar::sonarRange()
{
	double rangeInches = 0.0;
	rangeInches = ultrasonicSensor->GetVoltage() / VOLTAGE_SCALING;
	return rangeInches;
}

double MaxSonar::Voltage()
{
	double volt = 0;
	volt = ultrasonicSensor->GetVoltage();
	return volt;
}
