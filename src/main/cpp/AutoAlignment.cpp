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
    double kp = -0.1;  // if we are moving the wrong way we need to make this positive
    double strafeCorrection = 0.0;

    m_visionProcessing->updateLimelightProperties();

    if (m_visionProcessing->hasTarget())
    {
        double headingError = m_visionProcessing->X_Offset();
    
        // the error is between -27 and 27 degrees - we need to translate to -1 to 1 (speed controller speak)
        headingError /= 27.0;

        strafeCorrection = kp * headingError; 

        // TODO: we may have to adjust this because of friction in the robot - see http://docs.limelightvision.io/en/latest/cs_aiming.html
    }

    return strafeCorrection;
}

double AutoAlignment::getMoveCorrection()
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

    return distanceCorrection;
}

double AutoAlignment::getRotateCorrection()
{
    // return [-1,1]

    double rotationCorrection = 0.0;
    double angleError = 0.0;
    double kp = -0.2;
    
    // Determine the [-45,45] degree correction from closest compass point
    double gyroAngle = m_gyroSensor->GetAngle();
    std::cout << "in(" << gyroAngle << ")\t";

    angleError = relativeAngleCorrection(gyroAngle);

    // Deadband code...
    if ( abs(angleError) > 5 )
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
    std::cout << "out(" << rotationCorrection << ")\t";

    return rotationCorrection;
}

RobotFace AutoAlignment::closestCompassPoint(double angle)
{
    RobotFace closestCompassPoint = RobotFace::UNKNOWN;

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
    
    return closestCompassPoint;
}

double AutoAlignment::relativeAngleCorrection(double angle)
{
    // Determine the angle relative to the closest compass direction
    // angle [0,359); returns [-45,45]

    double relativeAngle = 0.0;
    int northCorrection = 0;
    RobotFace face = RobotFace::UNKNOWN;

    relativeAngle = constrainToCircle(angle);
    face = closestCompassPoint(relativeAngle);

    switch(face)
    {
        case RobotFace::NORTH:
            std::cout << "N\t";
            relativeAngle -= RobotFace::NORTH;
            break;

        case RobotFace::SOUTH:
            std::cout << "S\t";
            relativeAngle -= RobotFace::SOUTH;
            break;

        case RobotFace::EAST:
            std::cout << "E\t";
            relativeAngle -= RobotFace::EAST;
            break;

        case RobotFace::WEST:
            std::cout << "W\t";
            relativeAngle -= RobotFace::WEST;
            break;
        case RobotFace::NORTH2:
            std::cout << "N\t";
            relativeAngle -= RobotFace::NORTH2;
            break;
    default:
            std::cout << "UNKNOWN\t";
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

    // transpose large numbers into the range [-360 and +360] inclusive
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

    return angle;
}