//*****************************************************************************
// Filename:            pneumatic_helper.hpp
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

#ifndef PNEUMATIC_HELPER_HPP
#define PNEUMATIC_HELPER_HPP

/******************************************************************************
 * Include Files
 *****************************************************************************/
// First Includes //
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>

/******************************************************************************
 * Constants
 *****************************************************************************/

/******************************************************************************
 * Types
 *****************************************************************************/
    
/******************************************************************************
 * Variables
 *****************************************************************************/
bool loopControl = false;

/******************************************************************************
 * CLASS      : SingleSolenoid
 *
 * DESCRIPTION: This class is to operate a Single Solenoid.
 *
 * RETURNS    : None
 *****************************************************************************/
class SingleSolenoid
{
public:
    /**************************************************************************
     * FUNCTION   : SingleSolenoid
     *
     * DESCRIPTION: Constructs the Solenoid object with the specified 
     *              <solenoidChannel>.
     *
     * RETURNS    : A Solenoid object
     *************************************************************************/
	SingleSolenoid(int solenoidChannel);

    /**************************************************************************
     * FUNCTION   : toggleSolenoid
     *
     * DESCRIPTION: Toggles the current state of the solenoid.
     *
     * RETURNS    : Void
     *************************************************************************/
	void toggleSolenoid();

	/**************************************************************************
	 * FUNCTION   : activate
	 *
	 * DESCRIPTION: Activates the solenoid.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void activate();

	/**************************************************************************
	 * FUNCTION   : deactivate
	 *
	 * DESCRIPTION: Deactivates the solenoid.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void deactivate();

     /**************************************************************************
	 * FUNCTION   : getVal
	 *
	 * DESCRIPTION: Gets the value of the solenoid.
	 *
	 * RETURNS    : Boolean, if the solenoid is on or off.
	 *************************************************************************/
	bool getVal();
private:
     bool currentState = false;

	frc::Solenoid *m_solenoidSingle;
};

/////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * CLASS      : DoubleSolenoid
 *
 * DESCRIPTION: This class is to operate a Double Solenoid.
 *
 * RETURNS    : None
 *****************************************************************************/
class DoubleSolenoid
{
public:
	/**************************************************************************
     * FUNCTION   : DoubleSolenoid
     *
     * DESCRIPTION: Constructs the Solenoid object with the specified 
     *              <solenoidChannelFwd> and <solenoidChannelBck>.
     *
     * RETURNS    : A Solenoid object
     *************************************************************************/
	DoubleSolenoid(int solenoidChannelFwd, int solenoidChannelBck);

    /**************************************************************************
     * FUNCTION   : toggleSolenoid
     *
     * DESCRIPTION: Toggles the current state of the solenoid.
     *
     * RETURNS    : Void
     *************************************************************************/
	void toggleSolenoid();

	/**************************************************************************
	 * FUNCTION   : activateFwd
	 *
	 * DESCRIPTION: Activates the solenoid forwards.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void forwards();

     /**************************************************************************
	 * FUNCTION   : activateRev
	 *
	 * DESCRIPTION: Activates the solenoid reverse.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void reverse();

	/**************************************************************************
	 * FUNCTION   : deactivate
	 *
	 * DESCRIPTION: Deactivates the solenoid.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void deactivate();

     /**************************************************************************
	 * FUNCTION   : getVal
	 *
	 * DESCRIPTION: Gets the value of the solenoid.
	 *
	 * RETURNS    : Boolean, if the solenoid is on or off.
	 *************************************************************************/
	bool getVal();
private:
    frc::DoubleSolenoid::Value currentState = frc::DoubleSolenoid::Value::kOff;

	frc::DoubleSolenoid *m_solenoidDouble;
};

/////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * CLASS      : Compressor
 *
 * DESCRIPTION: This class is to operate a Compressor.
 *
 * RETURNS    : None
 *****************************************************************************/
class Compressor
{
public:
	/**************************************************************************
     * FUNCTION   : Compressor
     *
     * DESCRIPTION: Constructs the Compressor object with the specified 
     *              <compressorChannel>.
     *
     * RETURNS    : A Compressor object
     *************************************************************************/
	Compressor(int compressorChannel = 0);

    /**************************************************************************
     * FUNCTION   : toggleCompressor
     *
     * DESCRIPTION: Toggles the current state of the compressor.
     *
     * RETURNS    : Void
     *************************************************************************/
	bool toggleCompressor();

	/**************************************************************************
	 * FUNCTION   : activate
	 *
	 * DESCRIPTION: Activates the compressor.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void activate();

	/**************************************************************************
	 * FUNCTION   : deactivate
	 *
	 * DESCRIPTION: Deactivates the compressor.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void deactivate();

	/**************************************************************************
	 * FUNCTION   : lowPressureActivate
	 *
	 * DESCRIPTION: Sets the compressor to activate when the pressure is low.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void lowPressureActivate(bool state);

	/**************************************************************************
	 * FUNCTION   : getPressureActivate
	 *
	 * DESCRIPTION: If the compressor will activate when the pressure is low.
	 *
	 * RETURNS    : Bool
	 *************************************************************************/
	bool getPressureActivate();

	/**************************************************************************
	 * FUNCTION   : getSwitch
	 *
	 * DESCRIPTION: If the pressure switch is activated.
	 *
	 * RETURNS    : Bool
	 *************************************************************************/
	bool getSwitch();

     /**************************************************************************
	 * FUNCTION   : getVal
	 *
	 * DESCRIPTION: Gets the value of the compressor.
	 *
	 * RETURNS    : Boolean, if the compressor is on or off.
	 *************************************************************************/
	bool getVal();

	/**************************************************************************
	 * FUNCTION   : getCurrent
	 *
	 * DESCRIPTION: Gets the current draw of the compressor.
	 *
	 * RETURNS    : Double, the current in amps.
	 *************************************************************************/
	double getCurrent();

	/**************************************************************************
	 * FUNCTION   : testFaults
	 *
	 * DESCRIPTION: Queries the compressor about various things.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void testFaults();

	/**************************************************************************
	 * FUNCTION   : clearStickyFaults
	 *
	 * DESCRIPTION: Clears the sticky faults.
	 *
	 * RETURNS    : Void
	 *************************************************************************/
	void clearStickyFaults();
private:
	bool currentState = false;
	bool currentHighFault = false;//GetCompressorCurrentTooHighFault
	bool currentHighFaultSticky = false;//GetCompressorCurrentTooHighStickyFault
	bool notConnectedFault = false;//GetCompressorNotConnectedFault
	bool notConnectedFaultSticky = false;//GetCompressorNotConnectedStickyFault
	bool shortCircuitFault = false;//GetCompressorShortedFault
	bool shortCircuitFaultSticky = false;//GetCompressorShortedStickyFault

	frc::Compressor *m_compressor;
};

#endif /* PNEUMATIC_HELPER_HPP */
