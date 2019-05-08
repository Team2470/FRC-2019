#include <iostream>
#include "AutoAlignment.hpp"

AutoAlignment::AutoAlignment(frc::ADXRS450_Gyro* gyroSensor, MaxSonar* sonarSensor, VisionProcessing* visionProcessing)
{
	m_gyroSensor = gyroSensor;
	m_sonarSensor = sonarSensor;
	m_visionProcessing = visionProcessing;
}

double AutoAlignment::getShiftCorrection()
{

	double strafeCorrection = 0.0;
	double kp = 0.8;  // if we are moving the wrong way we need to make this positive

	// TODO: Something is up with the camera/network tables.  I'm not sure why we aren't
	// seeing the robot being able to control the camera....  
	// the code below is just trying to get the limelight to do somehing...

	m_visionProcessing->setLedMode(LimelightLedMode::CURRENT_PIPELINE);
	m_visionProcessing->setCameraMode(LimelightCameraMode::VISION_PROCESSOR);
	// m_visionProcessing->updateLimelightProperties();


	// TODO: This is where the code should be pretty close
	// you'll have to muck with kp and maybe even put in deadband
	// and some code to make sure a "minimum" value is sent to the motors
	// look at the rotate code for an example
	if (m_visionProcessing->hasTarget())
	{
		std::cout << "** has targates **" << std::endl;
		double headingError = m_visionProcessing->X_Offset();
	
		// the error is between -27 and 27 degrees - we need to translate to -1 to 1 (speed controller speak)
		headingError /= 27;

		strafeCorrection = kp * headingError; 

		// TODO: we may have to adjust this because of friction in the robot - see http://docs.limelightvision.io/en/latest/cs_aiming.html
	}
	else
	{
		std::cout << "--  NO targates --" << std::endl;
	}

	// validate output
	if ( strafeCorrection < -1.0 || strafeCorrection > 1.0 )
	{
		std::cout << "AutoAlignment::getShiftCorrection() : ERROR on output : strafeCorrection = " << strafeCorrection << std::endl;
		strafeCorrection = 0.0;
	}


	return strafeCorrection;
}

double AutoAlignment::getMoveCorrection()
{
	double distanceCorrection = 0.0;

	// TODO: switch over to the ping one if you guys are using the ultrasonic..
	
	//probably going to use ultra so switching this for now
	// distanceCorrection = moveCorrectionViaVision();
	distanceCorrection = moveCorrectionViaPing();

	/*
	//commented out because we already validate in the functions
	// validate output
	if ( distanceCorrection < -1.0 || distanceCorrection > 1.0 )
	{
		std::cout << "AutoAlignment::getMoveCorrection() : ERROR on output : distanceCorrection = " << distanceCorrection << std::endl;
		distanceCorrection = 0.0;
	}
	*/

	return distanceCorrection;
}

double AutoAlignment::getRotateCorrection()
{
	// return [-1,1]

	double rotationCorrection = 0.0;
	double angleError = 0.0;
	double kp = -1.0;
	
	// Determine the [-45,45] degree correction from closest compass point
	double gyroAngle = m_gyroSensor->GetAngle();
	// std::cout << "in(" << gyroAngle << ")\t";

	angleError = relativeAngleCorrection(gyroAngle);

	// Deadband code...
	if ( abs(angleError) > 1 )
	{
		// take the [-45,45] degree value and tranform it into [-1,1]
		rotationCorrection = angleError / 45.0;
	}
	else
	{
		// if within our deadband return 0.0
		rotationCorrection = 0.0;
	}

	// only using a proportional constant - switch to a PID later??
	rotationCorrection = kp * rotationCorrection;
	// std::cout << "out(" << rotationCorrection << ")\t";

	// have a minimum amount of speed...
	if (rotationCorrection > 0.05 && rotationCorrection < 0.3 )
	{
		rotationCorrection = 0.3;
	}

	if (rotationCorrection < -0.05 && rotationCorrection > -0.3)
	{
		rotationCorrection = -0.3;
	}

	// validate output
	if ( rotationCorrection > 1.0 || rotationCorrection < -1.0 )
	{
		std::cout << "AutoAlignment::getRotateCorrection() : ERROR on output : rotationCorrection = " << rotationCorrection << std::endl;
		rotationCorrection = 0.0;
	}

	return rotationCorrection;
}

RobotFace AutoAlignment::closestCompassPoint(double angle)
{
	RobotFace closestCompassPoint = RobotFace::UNKNOWN;

	// validate input
	if ( angle >=0 && angle < 360 )
	{
		if (inRange(angle, 0, 45))
		{
			closestCompassPoint = RobotFace::NORTH;
		}
		else if (inRange(angle, 45, 135))
		{
			closestCompassPoint = RobotFace::EAST;
		}
		else if (inRange(angle, 135, 225))
		{
			closestCompassPoint = RobotFace::SOUTH;
		}
		else if (inRange(angle, 225, 315))
		{
			closestCompassPoint = RobotFace::WEST;
		}
		else if (inRange(angle, 316,360))
		{
			closestCompassPoint = RobotFace::NORTH2;
		}
	}
	else
	{
		std::cout << "AutoAlignment::closestCompassPoint() : ERROR on input : angle = " << angle << std::endl;
	}

	// validate output
	if ( closestCompassPoint == RobotFace::UNKNOWN )
	{
		std::cout << "AutoAlignment::closestCompassPoint() : ERROR on output : closestCompassPoint == UNKNOWN" << std::endl;
	}
	
	return closestCompassPoint;
}

double AutoAlignment::relativeAngleCorrection(double angle)
{
	// Determine the angle relative to the closest compass direction
	// angle (-inf,inf); returns [-45,45]

	double relativeAngle = 0.0;
	int northCorrection = 0;
	RobotFace face = RobotFace::UNKNOWN;

	// validate input
	relativeAngle = constrainToCircle(angle);
	face = closestCompassPoint(relativeAngle);

	switch(face)
	{
		case RobotFace::NORTH:
			// std::cout << "N\t";
			relativeAngle -= RobotFace::NORTH;
			break;

		case RobotFace::SOUTH:
			// std::cout << "S\t";
			relativeAngle -= RobotFace::SOUTH;
			break;

		case RobotFace::EAST:
			// std::cout << "E\t";
			relativeAngle -= RobotFace::EAST;
			break;

		case RobotFace::WEST:
			// std::cout << "W\t";
			relativeAngle -= RobotFace::WEST;
			break;
		case RobotFace::NORTH2:
			// std::cout << "N\t";
			relativeAngle -= RobotFace::NORTH2;
			break;
	default:
			// std::cout << "UNKNOWN\t";
			relativeAngle = 0.0;
	}

	// validate output
	if ( relativeAngle < -45.0 || relativeAngle > 45.0 )
	{
		std::cout << "AutoAlignment::relativeAngleCorrection() : ERROR on output: relativeAngle = " << relativeAngle << std::endl;
		relativeAngle = 0.0;
	}

	return relativeAngle;
}


bool AutoAlignment::inRange(double value, double low, double high)
{
	return value >= low && value < high;
}

double AutoAlignment::constrainToCircle(double angle)
{
	// angle: (-inf,inf); returns [0,360)

	// this algorithm will only be using the whole part of
	// the provided angle, so we'll pull the decimal portion
	// off and add it back in at the end

	double angleDecimalPart = abs(angle) - abs(static_cast<int>(angle));
	int angleWholePart = static_cast<int>(angle - angleDecimalPart);

	// transpose large numbers into the range [-360,360]
	if ( abs(angleWholePart) >= 360 )
	{
		// grab the sign (modulus will always turn it into a positive)
		int sign = 1;
		if ( angleWholePart < 0 )
		{
			sign *= -1;
			angleWholePart = abs(angleWholePart);
		}

		angleWholePart = angleWholePart % 360;
		
		angleWholePart *= sign;
	}

	// if the angle is less then zero we want to
	// rotate the compass so that the value is positive
	if ( angleWholePart < 0  )
	{
		// we know it's <= 360, see above...
		angleWholePart = 360 + angleWholePart;
	}
	
	// angleWholePart should only be a postive value at this point...
	// we want [0,360), so if it's 360 treat it as zero
	if (angleWholePart == 360 )  
	{
		angleWholePart = 0;
	}
   
	// add the deimcal portion of the original angle
	angle = angleWholePart + angleDecimalPart;

	// validate the output
	if ( angle >=360 || angle < 0 )  
	{
		std::cout << "AutoAlignment::constrainToCircle() : ERROR on output : angle = " << angle << std::endl;
		angle = 0.0;
	}

	return angle;
}

double AutoAlignment::moveCorrectionViaVision()
{
	double distanceCorrection = 0.0;
	double kp = 0.1;

	m_visionProcessing->updateLimelightProperties();

	if (m_visionProcessing->hasTarget())
	{
		double verticalError = m_visionProcessing->Y_Offset();
	
		// the error is between -20.5 and 20.5 degrees - need -1 to 1
		verticalError /= 27.0;

		distanceCorrection = kp * verticalError; 
	}

	// validate output
	if ( distanceCorrection < -1 || distanceCorrection > 1 )
	{
		std::cout << "AutoAlignment::moveCorrectionViaVision() : ERROR on output : distanceCorrection = " << distanceCorrection << std::endl;
		distanceCorrection = 0.0;
	}

	return distanceCorrection;
}

double AutoAlignment::moveCorrectionViaPing()
{
	double distanceCorrection = 0;
	double kpforwards = 0.4;
	double kpbackwards = 0.6;
	double yLength = m_sonarSensor->sonarRange();

	std::cout << "Ultrasonic Sensor: " << yLength << std::endl;
	//int sign = yLength > IDEAL_SONAR_RANGE ? 1 : -1;

	//Checks to see if the sonar range is in the deadzone 12 inches +- 2 inches
	if (yLength >= IDEAL_SONAR_RANGE - SONAR_DEADZONE && yLength <= IDEAL_SONAR_RANGE + SONAR_DEADZONE)
	{
		yLength = IDEAL_SONAR_RANGE;
	}

	//Checks to see if the sonar range is greater than the max value
	if (yLength >= MAX_SONAR_RANGE)
	{
		yLength = MAX_SONAR_RANGE;
	}

	if ((yLength - IDEAL_SONAR_RANGE) < 0)
	{
		distanceCorrection = kpbackwards * ((yLength - IDEAL_SONAR_RANGE) / MAX_SONAR_RANGE);
	}
	else
	{
		distanceCorrection = kpforwards * ((yLength - IDEAL_SONAR_RANGE) / MAX_SONAR_RANGE);
	}

	// validate output
	if ( distanceCorrection < -1 || distanceCorrection > 1 )
	{
		std::cout << "AutoAlignment::moveCorrectionViaPing() : ERROR on output : distanceCorrection = " << distanceCorrection << std::endl;
		distanceCorrection = 0.0;
	}

	std::cout << "Distance Correction: " << distanceCorrection << std::endl;

	return distanceCorrection;
}