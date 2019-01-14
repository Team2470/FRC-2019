//*****************************************************************************
// Filename:            solenoid_helper.hpp
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

#ifndef SOLENOID_HELPER_HPP
#define SOLENOID_HELPER_HPP

/******************************************************************************
 * Include Files
 *****************************************************************************/
// First Includes //
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>

/******************************************************************************
 * Constants
 *****************************************************************************/

/******************************************************************************
 * Types
 *****************************************************************************/
    
/******************************************************************************
 * Variables
 *****************************************************************************/

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

#endif /* SOLENOID_HELPER_HPP */
