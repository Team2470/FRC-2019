#include "vision_processing.hpp"

VisionProcessing::VisionProcessing()
{
    this->networkTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    this->updateLimelightProperties();
}

void VisionProcessing::updateLimelightProperties()
{
    this->limelightTargetsTV = this->networkTable->GetNumber("tv", 0);
    this->limelightHorizontalOffsetTX = this->networkTable->GetNumber("tx", 0.0);
    this->limelightVerticalOffsetTY = this->networkTable->GetNumber("ty", 0.0);
    this->limelightTargetAreaTA = this->networkTable->GetNumber("ta", 0.0);
    this->limelightSkewTS = this->networkTable->GetNumber("ts", 0.0);
    this->limelightBoundingBoxWidthTHOR = this->networkTable->GetNumber("thor", 0.0);
    this->limelightBoundingBoxHeightTVERT = this->networkTable->GetNumber("tvert", 0.0);
}

void VisionProcessing::setLedMode(LimelightLedMode mode)
{
    this->networkTable->PutNumber("ledMode", mode);
}

void VisionProcessing::setCameraMode(LimelightCameraMode mode)
{
    this->networkTable->PutNumber("camMode", mode);
}

void VisionProcessing::setPipeline(short pipeline)
{
    this->networkTable->PutNumber("pipeline", pipeline);
}