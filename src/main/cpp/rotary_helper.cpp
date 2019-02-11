#include "rotary_helper.hpp"

Rotary::Rotary(frc::Joystick* controller1, frc::Joystick* controller2, frc::Joystick* controller3)
{
    this->ultrasonicSensor = new frc::AnalogInput(ultrasonicChannel);
    this->sensorFamily = sonarType;
    
    
}

int Rotary::getActive()
{
	updateValues();
}

void Rotary::updateValues()
{
	valueList = [
		controller1,>GetRawAxis(1) = 1 ? true : false,
		controller1,>GetRawAxis(1) = -1 ? true : false,
		controller1,>GetRawAxis(2) = 1 ? true : false,
		controller1,>GetRawAxis(4) = 1 ? true : false,
		controller1,>GetRawAxis(1) = 1 ? true : false,
		controller1,>GetRawAxis(1) = 1 ? true : false,
	];
}
