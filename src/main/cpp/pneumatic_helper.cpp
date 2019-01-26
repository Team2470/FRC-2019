#include <iostream>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>
#include "pneumatic_helper.hpp"

SingleSolenoid::SingleSolenoid(int solenoidChannel)
{
	m_solenoidSingle = new frc::Solenoid(solenoidChannel);
}

void SingleSolenoid::toggleSolenoid()
{
	//turn solenoid on/off
	m_solenoidSingle->Set(!currentState);
	currentState = !currentState;
}

void SingleSolenoid::activate()
{
	m_solenoidSingle->Set(true);
	currentState = true;
}

void SingleSolenoid::deactivate()
{
	m_solenoidSingle->Set(false);
	currentState = false;
}

bool SingleSolenoid::getVal()
{
	return m_solenoidSingle->Get();
}

DoubleSolenoid::DoubleSolenoid(int solenoidChannelFwd, int solenoidChannelBck)
{
    	m_solenoidDouble = new frc::DoubleSolenoid(solenoidChannelFwd, solenoidChannelBck);
}

bool DoubleSolenoid::getVal()
{
	return m_solenoidDouble->Get();
}

void DoubleSolenoid::forwards()
{
	m_solenoidDouble->Set(frc::DoubleSolenoid::Value::kForward);
	currentState = frc::DoubleSolenoid::Value::kForward;
}

void DoubleSolenoid::reverse()
{
	m_solenoidDouble->Set(frc::DoubleSolenoid::Value::kReverse);
	currentState = frc::DoubleSolenoid::Value::kReverse;
}

void DoubleSolenoid::deactivate()
{
	m_solenoidDouble->Set(frc::DoubleSolenoid::Value::kOff);
	currentState = frc::DoubleSolenoid::Value::kOff;
}

Compressor::Compressor(int compressorChannel)
{
	m_compressor = new frc::Compressor(compressorChannel);
}

void Compressor::toggleCompressor()
{
	if (currentState)
	{
		m_compressor->Stop();
		currentState = !currentState;
	}
	else
	{
		m_compressor->Start();
		currentState = !currentState;
	}
}

void Compressor::activate()
{
	m_compressor->Start();
	currentState = true;
}

void Compressor::deactivate()
{
	m_compressor->Stop();
	currentState = false;
}

void Compressor::lowPressureActivate(bool state)
{
	m_compressor->SetClosedLoopControl(state);
	//loopControl = state;//GetClosedLoopControl
}

bool Compressor::getPressureActivate()
{
	return m_compressor->GetClosedLoopControl();
}

bool Compressor::getSwitch()
{
	return m_compressor->GetPressureSwitchValue();
}

bool Compressor::getVal()
{
	return m_compressor->Enabled();
}

double Compressor::getCurrent()
{
	return m_compressor->GetCompressorCurrent();
}

void Compressor::testFaults()
{
	currentHighFault = m_compressor->GetCompressorCurrentTooHighFault();
	currentHighFaultSticky = m_compressor->GetCompressorCurrentTooHighStickyFault();
	notConnectedFault = m_compressor->GetCompressorNotConnectedFault();
	notConnectedFaultSticky = m_compressor->GetCompressorNotConnectedStickyFault();
	shortCircuitFault = m_compressor->GetCompressorShortedFault();
	shortCircuitFaultSticky = m_compressor->GetCompressorShortedStickyFault();
}

void Compressor::clearStickyFaults()
{
	m_compressor->ClearAllPCMStickyFaults();
	currentHighFault = m_compressor->GetCompressorCurrentTooHighFault();
	currentHighFaultSticky = m_compressor->GetCompressorCurrentTooHighStickyFault();
	notConnectedFault = m_compressor->GetCompressorNotConnectedFault();
	notConnectedFaultSticky = m_compressor->GetCompressorNotConnectedStickyFault();
	shortCircuitFault = m_compressor->GetCompressorShortedFault();
	shortCircuitFaultSticky = m_compressor->GetCompressorShortedStickyFault();
}
