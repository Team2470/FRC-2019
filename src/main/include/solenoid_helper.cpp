//*****************************************************************************
// Filename:            solenoid_helper.cpp
//
// Revision Record:
//   Author             Date       Description
//   ------------------ ---------- --------------------------------------------
//   Chris Struck       Jan. 2019  Initial design.
//
// Description:
//    Operates a single or double solenoid.
// 
// Dependencies:
//    None
//*****************************************************************************

/******************************************************************************
 * Include Files
 *****************************************************************************/
//System Includes
#include <iostream>

// First Includes
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>

//Our Includes
#include "solenoid_helper.hpp"

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    SingleSolenoid
 *---------------------------------------------------------------------------*/
SingleSolenoid::SingleSolenoid(int solenoidChannel)
{
    m_solenoidSingle = new frc::Solenoid(solenoidChannel);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    toggleSolenoid
 *---------------------------------------------------------------------------*/
void SingleSolenoid::toggleSolenoid()
{
	//turn solenoid on/off
	m_solenoidSingle->Set(!currentState);
	currentState = !currentState;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    activate
 *---------------------------------------------------------------------------*/
void SingleSolenoid::activate()
{
	m_solenoidSingle->Set(true);
	currentState = true;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    deactivate
 *---------------------------------------------------------------------------*/
void SingleSolenoid::deactivate()
{
	m_solenoidSingle->Set(false);
	currentState = false;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    getVal
 *---------------------------------------------------------------------------*/
bool SingleSolenoid::getVal()
{
	return m_solenoidSingle->Get();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    DoubleSolenoid
 *---------------------------------------------------------------------------*/
DoubleSolenoid::DoubleSolenoid(int solenoidChannelFwd, int solenoidChannelBck)
{
    m_solenoidDouble = new frc::DoubleSolenoid(solenoidChannelFwd, solenoidChannelBck);
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    getVal
 *---------------------------------------------------------------------------*/
bool DoubleSolenoid::getVal()
{
	return m_solenoidDouble->Get();
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    forwards
 *---------------------------------------------------------------------------*/
void DoubleSolenoid::forwards()
{
	m_solenoidDouble->Set(frc::DoubleSolenoid::Value::kForward);
	currentState = frc::DoubleSolenoid::Value::kForward;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    reverse
 *---------------------------------------------------------------------------*/
void DoubleSolenoid::reverse()
{
	m_solenoidDouble->Set(frc::DoubleSolenoid::Value::kReverse);
	currentState = frc::DoubleSolenoid::Value::kReverse;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME:    deactivate
 *---------------------------------------------------------------------------*/
void DoubleSolenoid::deactivate()
{
	m_solenoidDouble->Set(frc::DoubleSolenoid::Value::kOff);
	currentState = frc::DoubleSolenoid::Value::kOff;
}