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

RobotFace AutoAlignment::getDirectionFace(double angle)
{
    int adjustedAngle = (int)angle % 360;
    
    if(
        inRange(adjustedAngle, 0, 45) || inRange(adjustedAngle, 315, 360) ||
        inRange(adjustedAngle, -45, 0) || inRange(adjustedAngle, -360, -315) 
    )
    {
        return RobotFace::NORTH;
    }

    if(inRange(adjustedAngle, 45, 135) || inRange(adjustedAngle, -315, -225))
    {
        return RobotFace::EAST;
    }

    if(inRange(adjustedAngle, 135, 225) || inRange(adjustedAngle, -225, -135))
    {
        return RobotFace::SOUTH;
    }

    if(inRange(adjustedAngle, 225, 315) || inRange(adjustedAngle, -135, -45))
    {
        return RobotFace::WEST;
    }
}

double AutoAlignment::getDirectionCorrection()
{
    double angle = gyroSensor->GetAngle();
    double angleAdjusted = (int)angle % 360;
    RobotFace face = getDirectionFace(angle);

    switch(face)
    {
        case RobotFace::NORTH:
            return angleAdjusted > 315
                ? TARGET_ANGLE_NORTH_RIGHT - angleAdjusted
                : TARGET_ANGLE_NORTH_LEFT - angleAdjusted;

        case RobotFace::SOUTH:
            return TARGET_ANGLE_SOUTH - angleAdjusted;

        case RobotFace::EAST:
            return TARGET_ANGLE_EAST - angleAdjusted;

        case RobotFace::WEST:
            return TARGET_ANGLE_WEST - angleAdjusted;

        default:
            return 0;
    }
}

double AutoAlignment::getStrafeCorrection()
{

}

double AutoAlignment::getDistanceCorrection()
{

}

bool AutoAlignment::inRange(double value, double low, double high)
{
    return value >= low && value < high;
}