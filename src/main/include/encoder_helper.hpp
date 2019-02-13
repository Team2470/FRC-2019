#ifndef ENCODER_HELPER_HPP
#define ENCODER_HELPER_HPP

#include <frc/Encoder.h>

/**
 * @class		Encoder
 * @description This class operates an Encoder.
 *				it has the ability to control the mecanum drive.
 */
class Encoder
{
public:
	/**
	 * @constructor Encoder
	 * @description Construct the Encoder.
	 * @param		channelA  -- The A channel for the encoder.
	 * @param		channelB   -- The B channel for the encoder.
	 * @param		reversed -- If the encoder has it's direction reversed.
	 * @param		encoderType  -- The type of encoding that the encoder uses (from a given enum of k1X, k2X, or k4X)
	 */
	Encoder(int channelA, int channelB, bool reversed = false, frc::Encoder::EncodingType encoderType = frc::Encoder::k4X);

	/**
	 * @function	getValue
	 * @description Gets the current number of counts that the encoder has.
	 * @returns		The number of turns.
	 */
	int getValue();

	/**
	 * @function	getDirection
	 * @description Gets the last direction that the encoder moved
	 * @returns		Boolean of the last direction that the encoder moved (true = forwards, false = backwards)?
	 */
	bool getDirection();

	/**
	 * @function	getDistance
	 * @description Gets the current distance since last reset, scaled from SetDistancePerPulse.
	 * @returns		
	 */
	double getDistance();

	/**
	 * @function    reset
	 * @description Resets the encoder's count.
	 */
	void reset();

	/**
	 * @function    reverseDirection
	 * @description Reverses the encoder's direction.
	 */
	void reverseDirection();

private:
	bool currentDirection = false;

	frc::Encoder* encoder;
};

#endif
