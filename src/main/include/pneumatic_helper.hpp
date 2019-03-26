#ifndef PNEUMATIC_HELPER_HPP
#define PNEUMATIC_HELPER_HPP

#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>
#include <frc/AnalogInput.h>

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

/**
 * @class	    PressureSensor
 * @description Operates a pressure sensor.
 */
class PressureSensor
{
public:
	/**
	 * @constructor PressureSensor
	 * @description Construct the PressureSensor object.
	 * @param 	    analogChannel -- The channel of pressure switch.
	 * @param       knownPressureValue -- known pressure value to be used to set the normalized voltage
	 * @param       knownPressureValue -- known voltage output value to be used to set the normalized voltage
	 */
	PressureSensor(int analogChannel, int knownPressureValue = -1, double outputVoltageValue = -1);
	
	/**
	 * @function    setNormalizedVoltage
	 * @description Sets the normalized voltage supply for the pressure sensor.
	 */
	void setNormalizedVoltage(int knownPressure, double outputVoltage);
	
	/**
	 * @function	 getVoltage
	 * @description Gets the raw voltage output from the pressure sensor.
	 * @returns     Voltage value from 0.5V to 4.5V (maybe 0V to 5V idk)
	 */
	double getVoltage();
	
	/**
	 * @function	getVoltageOutput
	 * @description Gets the voltage output from the pressure sensor, using the "ideal" supply voltage or given voltage and given pressure.
	 * @returns     Voltage value from 0.5V to 4.5V
	 */
	double getVoltageOutput(double pressureValue, bool isNormalized);
	
	/**
	 * @function	getPressure
	 * @description Finds the pressure value from the default input voltage or normalized input voltage, then the current sensor output or the optional output voltage value.
	 * @returns     The pressure value up to 200 psi
	 */
	double getPressure(double optionalVoltage, bool isNormalized);

private:
	frc::AnalogInput* pressureSensor;
	
	double normalizedVoltageInput = -1;
	
	static constexpr double defaultVoltageInput = 5;
};

#endif
