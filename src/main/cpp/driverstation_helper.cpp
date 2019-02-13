#include "driverstation_helper.hpp"

Rotary::Rotary(frc::Joystick* ctrl1, frc::Joystick* ctrl2, frc::Joystick* ctrl3)
{
	controller1 = ctrl1;
	controller2 = ctrl2;
	controller3 = ctrl3;   
}

int Rotary::getActive()
{
	//updateValues();
	if (controller1->GetRawAxis(0) == 1)
	{
		//Right Controller, Top Joystick Slot, Positive X-Axis
		return RotarySwitch::RIGHT_HUB_TOP_JOYSTICK_POSITIVE_X;
	}
	else if (controller1->GetRawAxis(0) == -1)
	{
		//Right Controller, Top Joystick Slot, Negative X-Axis
		return RotarySwitch::RIGHT_HUB_TOP_JOYSTICK_NEGATIVE_X;
	}
	else if (controller1->GetRawAxis(1) == 1)
	{
		//Right Controller, Top Joystick Slot, Positive Y-Axis
		return RotarySwitch::RIGHT_HUB_TOP_JOYSTICK_POSITIVE_Y;
	}
	else if (controller1->GetRawAxis(1) == -1)
	{
		//Right Controller, Top Joystick Slot, Positive Y-Axis
		return RotarySwitch::RIGHT_HUB_TOP_JOYSTICK_NEGATIVE_Y;
	}
	else if (controller2->GetRawAxis(2) == 1)
	{
		//Right Controller, Left Joystick Slot, Positive X-Axis
		return RotarySwitch::RIGHT_HUB_LEFT_JOYSTICK_POSITIVE_X;
	}
	else if (controller2->GetRawAxis(2) == -1)
	{
		//Right Controller, Left Joystick Slot, Negative X-Axis
		return RotarySwitch::RIGHT_HUB_LEFT_JOYSTICK_NEGATIVE_X;
	}
	else if (controller2->GetRawAxis(3) == 1)
	{
		//Right Controller, Left Joystick Slot, Positive Y-Axis
		return RotarySwitch::RIGHT_HUB_LEFT_JOYSTICK_POSITIVE_Y;
	}
	else if(controller2->GetRawAxis(3) == -1)
	{
		//Right Controller, Left Joystick Slot, Negative Y-Axis
		return RotarySwitch::RIGHT_HUB_LEFT_JOYSTICK_NEGATIVE_Y;
	}
	else if (controller3->GetRawAxis(0) == 1)
	{
		//Left Controller, Top Joystick Slot, Positive X-Axis
		return RotarySwitch::LEFT_HUB_TOP_JOYSTICK_POSITIVE_X;
	}
	else
	{
		return RotarySwitch::EMPTY;
	}
}

/*void Rotary::updateValues()
{
	valueList = [
		controller1->GetRawAxis(0) == 1,
		controller1->GetRawAxis(0) == -1,
		controller1->GetRawAxis(1) == 1,
		controller1->GetRawAxis(1) == -1,
		controller2->GetRawAxis(2) == 1,
		controller2->GetRawAxis(2) == -1,
		controller2->GetRawAxis(3) == 1,
		controller2->GetRawAxis(3) == -1,
		controller3->GetRawAxis(0) == 1
	];
}*/
