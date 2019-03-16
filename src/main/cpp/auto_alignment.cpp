#include "auto_alignment.hpp"

AutoAlignment::AutoAlignment(frc::ADXRS450_Gyro* gyroSensor, MaxSonar* sonarSensor, VisionProcessing* visionProcessing)
{
    this->gyroSensor = gyroSensor;
    this->sonarSensor = sonarSensor;
    this->visionProcessing = visionProcessing;
}

void AutoAlignment::updateVisionProcessing()
{
    this->visionProcessing->updateLimelightProperties();
}

RobotFace AutoAlignment::getDirectionCorrection()
{
    double absoluteAngle = (int)gyroSensor->GetAngle() % 360;
    
    if(inRange(absoluteAngle, 0, 45) || inRange(absoluteAngle, 315, 360))
    {
        return RobotFace::NORTH;
    }

    if(inRange(absoluteAngle, 45, 135))
    {
        return RobotFace::EAST;
    }

    if(inRange(absoluteAngle, 135, 225))
    {
        return RobotFace::SOUTH;
    }

    if(inRange(absoluteAngle, 225, 315))
    {
        return RobotFace::WEST;
    }
}

bool AutoAlignment::inRange(double value, double low, double high)
{
    return value >= low && value < high;
}