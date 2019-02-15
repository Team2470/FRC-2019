#include "driverstation_helper.hpp"

Rotary::Rotary(frc::Joystick* ctrl1, frc::Joystick* ctrl2, frc::Joystick* ctrl3)
{
	controller1 = ctrl1;
	controller2 = ctrl2;
	controller3 = ctrl3;   
}

int Rotary::getActive()
{
	updateValues();
	
	if (controller1->GetRawAxis(0) == 1)
	{
		return RotarySwitch::RIGHT_HUB_TOP_JOYSTICK_POSITIVE_X;
	}
	else if (controller1->GetRawAxis(0) == -1)
	{
		return RotarySwitch::RIGHT_HUB_TOP_JOYSTICK_NEGATIVE_X;
	}
	else if (controller1->GetRawAxis(1) == 1)
	{
		return RotarySwitch::RIGHT_HUB_TOP_JOYSTICK_POSITIVE_Y;
	}
	else if (controller1->GetRawAxis(1) == -1)
	{
		return RotarySwitch::RIGHT_HUB_TOP_JOYSTICK_NEGATIVE_Y;
	}
	else if (controller2->GetRawAxis(2) == 1)
	{
		return RotarySwitch::RIGHT_HUB_LEFT_JOYSTICK_POSITIVE_X;
	}
	else if (controller2->GetRawAxis(2) == -1)
	{
		return RotarySwitch::RIGHT_HUB_LEFT_JOYSTICK_NEGATIVE_X;
	}
	else if (controller2->GetRawAxis(3) == 1)
	{
		return RotarySwitch::RIGHT_HUB_LEFT_JOYSTICK_POSITIVE_Y;
	}
	else if(controller2->GetRawAxis(3) == -1)
	{
		return RotarySwitch::RIGHT_HUB_LEFT_JOYSTICK_NEGATIVE_Y;
	}
	else if (controller3->GetRawAxis(0) == 1)
	{
		return RotarySwitch::LEFT_HUB_TOP_JOYSTICK_POSITIVE_X;
	}
	else
	{
		return RotarySwitch::EMPTY;
	}
}

bool Rotary::isActive(int rotChannel)
{
	this->updateValues();

	if (rotChannel < 1)
	{
		return valueList[1];
	}
	else if (rotChannel > 10)
	{
		return valueList[10];
	}
	else
	{
		return valueList[rotChannel];
	}
}

void Rotary::updateValues()
{
	valueList = {
		controller1->GetRawAxis(0) == 1,
		controller1->GetRawAxis(0) == -1,
		controller1->GetRawAxis(1) == 1,
		controller1->GetRawAxis(1) == -1,
		controller2->GetRawAxis(2) == 1,
		controller2->GetRawAxis(2) == -1,
		controller2->GetRawAxis(3) == 1,
		controller2->GetRawAxis(3) == -1,
		controller3->GetRawAxis(0) == 1
	};
}
