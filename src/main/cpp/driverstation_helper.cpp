#include "driverstation_helper.hpp"

Rotary::Rotary(frc::Joystick* controller1, frc::Joystick* controller2, frc::Joystick* controller3)
{
    this->ultrasonicSensor = new frc::AnalogInput(ultrasonicChannel);
    this->sensorFamily = sonarType;
    
}

int Rotary::getActive()
{
	//updateValues();
	if (controller1->GetRawAxis(0) == 1)
	{
		//Right Controller, Top Joystick Slot, Positive X-Axis
		return 1;
	}
	else if (controller1->GetRawAxis(0) == -1)
	{
		//Right Controller, Top Joystick Slot, Negative X-Axis
		return 2;
	}
	else if (controller1->GetRawAxis(1) == 1)
	{
		//Right Controller, Top Joystick Slot, Positive Y-Axis
	}
	else if (controller1->GetRawAxis(1) == -1)
	{
		//Right Controller, Top Joystick Slot, Positive Y-Axis
	}
	else if (controller2->GetRawAxis(2) == 1)
	{
		//Right Controller, Left Joystick Slot, Positive X-Axis
	}
	else if (controller2->GetRawAxis(2) == -1)
	{
		//Right Controller, Left Joystick Slot, Negative X-Axis
	}
	else if (controller2->GetRawAxis(3) == 1)
	{
		//Right Controller, Left Joystick Slot, Positive Y-Axis
	}
	else if(controller2->GetRawAxis(3) == -1)
	{
		//Right Controller, Left Joystick Slot, Negative Y-Axis
	}
	else if (controller3->GetRawAxis(0) == 1)
	{
		//Left Controller, Top Joystick Slot, Positive X-Axis
	}
	else
	{

	}
}

/*void Rotary::updateValues()
{
	valueList = [
		controller1->GetRawAxis(0) == 1 ? true : false,
		controller1->GetRawAxis(0) == -1 ? true : false,
		controller1->GetRawAxis(1) == 1 ? true : false,
		controller1->GetRawAxis(1) == -1 ? true : false,
		controller2->GetRawAxis(2) == 1 ? true : false,
		controller2->GetRawAxis(2) == -1 ? true : false,
		controller2->GetRawAxis(3) == 1 ? true : false,
		controller2->GetRawAxis(3) == -1 ? true : false,
		controller3->GetRawAxis(0) == 1 ? true : false
	];
}*/
