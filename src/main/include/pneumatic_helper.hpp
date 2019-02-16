#ifndef PNEUMATIC_HELPER_HPP
#define PNEUMATIC_HELPER_HPP

#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>

/**
 * @class	SingleSolenoid
 * @description Operates a single solenoid.
 */
class SingleSolenoid
{
public:
	/**
	 * @constructor SingleSolenoid
	 * @description Construct the Solenoid object.
	 * @param 	solenoidChannel -- The channel of the solenoid.
	 */
	SingleSolenoid(int solenoidChannel);

	/**
	 * @function    toggleSolenoid
	 * @description Toggles the current state of the solenoid.
	 */
	void toggleSolenoid();

	/**
	 * @function	activate
	 * @description Activates the solenoid.
	 */
	void activate();

	/**
	 * @function    deactivate
	 * @description Deactivates the solenoid.
	 */
	void deactivate();

	/**
	 * @function	getVal
	 * @description Gets the value of the solenoid.
	 * @returns     The current state of the solenoid.
	 */
	bool getVal();

private:
    frc::Solenoid* solenoidSingle;
	bool currentState = false;
};


/**
 * @class       DoubleSolenoid
 * @description This class operates a double solenoid.
 */
class DoubleSolenoid
{
public:
	/**
	 * @constructor DoubleSolenoid
	 * @description Constructs the Solenoid object.
	 * @param	solenoidChannelFwd -- The forward channel of the solenoid.
	 * @param	solenoidChannelBck -- The backward channel of the solenoid.
	 */
	DoubleSolenoid(int solenoidChannelFwd, int solenoidChannelBck);

	/**
	 * @function	toggleSolenoid
	 * @description Toggles the current state of the solenoid.
	 */
	void toggleSolenoid();

	/**
	 * @function	forwards
	 * @description Activates the solenoid forward.
	 */
	void forwards();

	/**
	 * @function	reverse
	 * @description Activates the solenoid reverse.
	 */
	void reverse();

	/**
	 * @function	deactivate
	 * @description Deactivates the solenoid.
	 */ 
	void deactivate();

	/**
	 * @function    getVal
	 * @description Gets the current value of the solenoid.
	 * @returns     The current state of the solenoid.
	 */
	bool getVal();

private:
    frc::DoubleSolenoid::Value currentState = frc::DoubleSolenoid::Value::kOff;
	frc::DoubleSolenoid* solenoidDouble;
};


/**
 * @class	Compressor
 * @description This class operates a compressor.
 */
class Compressor
{
public:
	/**
	 * @constructor Compressor
	 * @description Constructs the compressor object.
	 * @param	compressorChannel -- The channel of the compressor. Defaults to zero.
	 */
	Compressor(int compressorChannel = 0);

	/**
	 * @function	toggleCompressor
	 * @description Toggles the current state of the compressor.
	 */
	void toggleCompressor();

	/**
	 * @function	activate
	 * @description Activates the compressor.
	 */
	void activate();

	/**
	 * @function	deactivate
	 * @description Deactivates the compressor.
	 */
	void deactivate();

	/**
	 * @function	lowPressureToggle
	 * @description Toggles if the compressor will activate when the pressure is low.
	 */
	void lowPressureToggle();

	/**
	 * @function	lowPressureActivate
	 * @description Sets the compressor to activate when the pressure is low.
	 */
	void lowPressureActivate(bool state);

	/**
	 * @function	getPressureActivate
	 * @description Determines whether the compressor will activate when the pressure is low.
	 * @returns 	Whether the compressor should activate.
	 */
	bool getPressureActivate();

	/**
	 * @function    getSwitch
	 * @description Determines if the pressure switch is activated.
	 * @returns	Whether the switch is activated.
	 */
	bool getSwitch();

	/**
	 * @function	getVal
	 * @description Determine the current state of the compressor, on or off.
	 * @returns     The current state.
	 */
	bool getVal();

	/**
	 * @function	getCurrent
	 * @description Determine the present current draw of the compressor.
	 * @returns     The current, in amps.
	 */
	double getCurrent();

	/**
	 * @function    testFaults
	 * @description Test for compressor faults.
	 */
	void testFaults();

	/**
	 * @function    clearStickyFaults
	 * @description Clear any current sticky faults.
	 */
	void clearStickyFaults();

private:
	bool loopControl = false;
	bool currentState = false;
	bool currentHighFault = false;        // GetCompressorCurrentTooHighFault
	bool currentHighFaultSticky = false;  // GetCompressorCurrentTooHighStickyFault
	bool notConnectedFault = false;       // GetCompressorNotConnectedFault
	bool notConnectedFaultSticky = false; // GetCompressorNotConnectedStickyFault
	bool shortCircuitFault = false;	      // GetCompressorShortedFault
	bool shortCircuitFaultSticky = false; // GetCompressorShortedStickyFault
    frc::Compressor* compressor;
};

#endif
