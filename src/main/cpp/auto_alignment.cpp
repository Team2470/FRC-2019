#include "auto_alignment.hpp"

AutoAlignment::AutoAlignment(frc::AnalogGyro* gyroSensor, MaxSonar* sonarSensor, VisionProcessing* visionProcessing)
{
    this->gyroSensor = gyroSensor;
    this->sonarSensor = sonarSensor;
    this->visionProcessing = visionProcessing;
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
    this->distanceToResolveParallel = this->distanceToResolve * cos(this->angleToResolve * PI / 180);
    this->distanceToResolvePerpendicular = this->distanceToResolve * sin(this->angleToResolve * PI / 180);
    return this->distanceToResolve;
}

double AutoAlignment::calculateResolutionAngle()
{
    this->angleToResolve = this->gyroSensor->GetAngle() + this->visionProcessing->limelightHorizontalOffsetTX;
    this->side = this->visionProcessing->limelightHorizontalOffsetTX <= 0 ? SideRelativeToTarget::LEFT : SideRelativeToTarget::RIGHT;
    return this->angleToResolve;
}