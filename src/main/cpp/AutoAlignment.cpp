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
    double rotationCorrection = 0.0;
    double angleError = 0.0;
    double kp = 0.1;

    // determine the -45..45 degree correction from closest compass point    
    angleError = relativeAngleCorrection(m_gyroSensor->GetAngle());

    // take the -45..45 degree value and tranform it into -1..1 
    rotationCorrection = angleError / 45.0;

    // only using a proportional constant - switch to a PID later??
    rotationCorrection = kp * rotationCorrection;

    return rotationCorrection;
}

RobotFace AutoAlignment::closestCompassPoint(double angle)
{
    // make sure the value is constrained to [0,360)
    if ( angle <= -360.0 || angle >= 360.0 )
    {
        angle = constrainToCircle(angle);
    }

    // direction closest to where the robot is currently facing
    RobotFace closestCompassPoint = RobotFace::UNKNOWN;

    // walk around the cirlce...
    if(inRange(angle, 0, 45))
    {
        closestCompassPoint = RobotFace::NORTH;
    }
    else if (inRange(angle, 45, 135))
    {
        closestCompassPoint = RobotFace::EAST;
    }
    else if(inRange(angle, 135, 225))
    {
        closestCompassPoint = RobotFace::SOUTH;
    }
    else if(inRange(angle, 225, 315))
    {
        closestCompassPoint = RobotFace::WEST;
    }
    else if(inRange(angle, 316,360))
    {
        closestCompassPoint = RobotFace::NORTH;
    }
    
    return closestCompassPoint;
}

double AutoAlignment::relativeAngleCorrection(double angle)
{
    // based on the closest face determine the relative angle    

    double relativeCorrection = 0.0;
    RobotFace face = RobotFace::UNKNOWN;

    angle = constrainToCircle(angle);
    face = closestCompassPoint(angle);

    // rotate the compass 45 degrees to make the math easier
    relativeCorrection = angle + 45.0;  
    switch(face)
    {
        case RobotFace::NORTH:
            relativeCorrection -= RobotFace::NORTH;

        case RobotFace::SOUTH:
            relativeCorrection -= RobotFace::SOUTH;

        case RobotFace::EAST:
            relativeCorrection -= RobotFace::EAST;

        case RobotFace::WEST:
            relativeCorrection -= RobotFace::WEST;

        default:
            return 0.0;
    }

    // rotate our compass back - the value should now be [-45,45] relative to compass point
    relativeCorrection -= 45.0;  

    return relativeCorrection;
}


bool AutoAlignment::inRange(double value, double low, double high)
{
    return value >= low && value < high;
}

double AutoAlignment::constrainToCircle(double angle)
{
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