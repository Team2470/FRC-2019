#include "auto_alignment.hpp"

AutoAlignment::AutoAlignment(frc::AnalogGyro* gyroSensor, MaxSonar* sonarSensor)
{
    this->gyroSensor = gyroSensor;
    this->sonarSensor = sonarSensor;
    this->visionProcessing = new VisionProcessing();
}

void AutoAlignment::updateVisionProcessing()
{
    this->visionProcessing->updateLimelightProperties();
}

void AutoAlignment::calculateResolution()
{
    this->calculateResolutionAngle();
    this->calculateResolutionDistance();
}

double AutoAlignment::calculateResolutionDistance()
{
    this->distanceToResolve = this->sonarSensor->sonarRange();
    this->distanceToResolveParallel = fabs(this->distanceToResolve * cos(this->angleToResolve * PI / 180));
    this->distanceToResolvePerpendicular = fabs(this->distanceToResolve * sin(this->angleToResolve * PI / 180));
    return this->distanceToResolve;
}

double AutoAlignment::calculateResolutionAngle()
{
    this->angleToResolve = this->gyroSensor->GetAngle() + this->visionProcessing->limelightHorizontalOffsetTX;
    this->side = this->visionProcessing->limelightHorizontalOffsetTX <= 0 ? SideRelativeToTarget::LEFT : SideRelativeToTarget::RIGHT;
    return this->angleToResolve;
}