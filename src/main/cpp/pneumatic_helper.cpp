#include "pneumatic_helper.hpp"

SingleSolenoid::SingleSolenoid(int solenoidChannel)
{
	this->solenoidSingle = new frc::Solenoid(solenoidChannel);
}

void SingleSolenoid::toggleSolenoid()
{
	this->solenoidSingle->Set(!this->currentState);
	this->currentState = !this->currentState;
}

void SingleSolenoid::activate()
{
	this->solenoidSingle->Set(true);
	this->currentState = true;
}

void SingleSolenoid::deactivate()
{
	this->solenoidSingle->Set(false);
	this->currentState = false;
}

bool SingleSolenoid::getVal()
{
	return this->solenoidSingle->Get();
}

DoubleSolenoid::DoubleSolenoid(int solenoidChannelFwd, int solenoidChannelBck)
{
    this->solenoidDouble = new frc::DoubleSolenoid(solenoidChannelFwd, solenoidChannelBck);
}

bool DoubleSolenoid::getVal()
{
	return this->solenoidDouble->Get();
}

void DoubleSolenoid::forwards()
{
	this->solenoidDouble->Set(frc::DoubleSolenoid::Value::kForward);
	this->currentState = frc::DoubleSolenoid::Value::kForward;
}

void DoubleSolenoid::reverse()
{
	this->solenoidDouble->Set(frc::DoubleSolenoid::Value::kReverse);
	this->currentState = frc::DoubleSolenoid::Value::kReverse;
}

void DoubleSolenoid::deactivate()
{
	this->solenoidDouble->Set(frc::DoubleSolenoid::Value::kOff);
	this->currentState = frc::DoubleSolenoid::Value::kOff;
}

Compressor::Compressor(int compressorChannel)
{
	this->compressor = new frc::Compressor(compressorChannel);
}

void Compressor::toggleCompressor()
{
	if(this->currentState)
	{
		this->compressor->Stop();
		this->currentState = !this->currentState;
	}
	else
	{
		this->compressor->Start();
		this->currentState = !this->currentState;
	}
}

void Compressor::activate()
{
	this->compressor->Start();
	this->currentState = true;
}

void Compressor::deactivate()
{
	this->compressor->Stop();
	this->currentState = false;
}

void Compressor::lowPressureActivate(bool state)
{
	this->compressor->SetClosedLoopControl(state);
}

bool Compressor::getPressureActivate()
{
	return this->compressor->GetClosedLoopControl();
}

bool Compressor::getSwitch()
{
	return this->compressor->GetPressureSwitchValue();
}

bool Compressor::getVal()
{
	return this->compressor->Enabled();
}

double Compressor::getCurrent()
{
	return this->compressor->GetCompressorCurrent();
}

void Compressor::testFaults()
{
	this->currentHighFault = this->compressor->GetCompressorCurrentTooHighFault();
	this->currentHighFaultSticky = this->compressor->GetCompressorCurrentTooHighStickyFault();
	this->notConnectedFault = this->compressor->GetCompressorNotConnectedFault();
	this->notConnectedFaultSticky = this->compressor->GetCompressorNotConnectedStickyFault();
	this->shortCircuitFault = this->compressor->GetCompressorShortedFault();
	this->shortCircuitFaultSticky = this->compressor->GetCompressorShortedStickyFault();
}

void Compressor::clearStickyFaults()
{
	this->compressor->ClearAllPCMStickyFaults();
	this->currentHighFault = this->compressor->GetCompressorCurrentTooHighFault();
	this->currentHighFaultSticky = this->compressor->GetCompressorCurrentTooHighStickyFault();
	this->notConnectedFault = this->compressor->GetCompressorNotConnectedFault();
	this->notConnectedFaultSticky = this->compressor->GetCompressorNotConnectedStickyFault();
	this->shortCircuitFault = this->compressor->GetCompressorShortedFault();
	this->shortCircuitFaultSticky = this->compressor->GetCompressorShortedStickyFault();
}
