#include <iostream>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>
#include "pneumatic_helper.hpp"

SingleSolenoid::SingleSolenoid(int solenoidChannel)
{
	solenoidSingle = new frc::Solenoid(solenoidChannel);
}

void SingleSolenoid::toggleSolenoid()
{
	solenoidSingle->Set(!currentState);
	currentState = !currentState;
}

void SingleSolenoid::activate()
{
	solenoidSingle->Set(true);
	currentState = true;
}

void SingleSolenoid::deactivate()
{
	solenoidSingle->Set(false);
	currentState = false;
}

bool SingleSolenoid::getVal()
{
	return solenoidSingle->Get();
}

DoubleSolenoid::DoubleSolenoid(int solenoidChannelFwd, int solenoidChannelBck)
{
    solenoidDouble = new frc::DoubleSolenoid(solenoidChannelFwd, solenoidChannelBck);
}

bool DoubleSolenoid::getVal()
{
	return solenoidDouble->Get();
}

void DoubleSolenoid::forwards()
{
	solenoidDouble->Set(frc::DoubleSolenoid::Value::kForward);
	currentState = frc::DoubleSolenoid::Value::kForward;
}

void DoubleSolenoid::reverse()
{
	solenoidDouble->Set(frc::DoubleSolenoid::Value::kReverse);
	currentState = frc::DoubleSolenoid::Value::kReverse;
}

void DoubleSolenoid::deactivate()
{
	solenoidDouble->Set(frc::DoubleSolenoid::Value::kOff);
	currentState = frc::DoubleSolenoid::Value::kOff;
}

Compressor::Compressor(int compressorChannel)
{
	compressor = new frc::Compressor(compressorChannel);
}

void Compressor::toggleCompressor()
{
	if(currentState)
	{
		compressor->Stop();
		currentState = !currentState;
	}
	else
	{
		compressor->Start();
		currentState = !currentState;
	}
}

void Compressor::activate()
{
	compressor->Start();
	currentState = true;
}

void Compressor::deactivate()
{
	compressor->Stop();
	currentState = false;
}

void Compressor::lowPressureActivate(bool state)
{
	compressor->SetClosedLoopControl(state);
	//loopControl = state;//GetClosedLoopControl
}

bool Compressor::getPressureActivate()
{
	return compressor->GetClosedLoopControl();
}

bool Compressor::getSwitch()
{
	return compressor->GetPressureSwitchValue();
}

bool Compressor::getVal()
{
	return compressor->Enabled();
}

double Compressor::getCurrent()
{
	return compressor->GetCompressorCurrent();
}

void Compressor::testFaults()
{
	currentHighFault = compressor->GetCompressorCurrentTooHighFault();
	currentHighFaultSticky = compressor->GetCompressorCurrentTooHighStickyFault();
	notConnectedFault = compressor->GetCompressorNotConnectedFault();
	notConnectedFaultSticky = compressor->GetCompressorNotConnectedStickyFault();
	shortCircuitFault = compressor->GetCompressorShortedFault();
	shortCircuitFaultSticky = compressor->GetCompressorShortedStickyFault();
}

void Compressor::clearStickyFaults()
{
	compressor->ClearAllPCMStickyFaults();
	currentHighFault = compressor->GetCompressorCurrentTooHighFault();
	currentHighFaultSticky = compressor->GetCompressorCurrentTooHighStickyFault();
	notConnectedFault = compressor->GetCompressorNotConnectedFault();
	notConnectedFaultSticky = compressor->GetCompressorNotConnectedStickyFault();
	shortCircuitFault = compressor->GetCompressorShortedFault();
	shortCircuitFaultSticky = compressor->GetCompressorShortedStickyFault();
}
