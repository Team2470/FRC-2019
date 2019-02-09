#include "auto_alignment.hpp"

AutoAlignment::AutoAlignment()
{
    
}

void AutoAlignment::updateVisionProcessing()
{
    this->visionProcessing.updateLimelightProperties();
}

void AutoAlignment::resolvePositionAndRotation()
{
    if(this->resolutionNeeded)
    {

    }
}

void AutoAlignment::calculateResolution()
{
    if(this->resolutionNeeded)
    {
        this->calculateResolutionAngle();
        this->calculateResolutionDistance();
    }
}

double AutoAlignment::calculateResolutionDistance()
{
    this->distanceToResolve = this->sonarSensor.sonarRange();
    this->distanceToResolveParallel = this->distanceToResolve * cos(this->angleToResolve * PI / 180);
    this->distanceToResolvePerpendicular = this->distanceToResolve * sin(this->angleToResolve * PI / 180);
    return this->distanceToResolve;
}

double AutoAlignment::calculateResolutionAngle()
{
    this->angleToResolve = this->gyroSensor.GetAngle();
    return this->angleToResolve;
}