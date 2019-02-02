#include "vision_processing.hpp"

VisionProcessing::VisionProcessing()
{
    this->networkTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    this->updateLimelightProperties();
}

void VisionProcessing::updateLimelightProperties()
{
    this->limelightTargets_TV = this->networkTable->GetNumber("tv", 0);
    this->limelightHorizontalOffset_TX = this->networkTable->GetNumber("tx", 0.0);
    this->limelightVerticalOffset_TY = this->networkTable->GetNumber("ty", 0.0);
    this->limelightTargetArea_TA = this->networkTable->GetNumber("ta", 0.0);
    this->limelightSkew_TS = this->networkTable->GetNumber("ts", 0.0);
    this->limelightBoundingBoxWidth_THOR = this->networkTable->GetNumber("thor", 0.0);
    this->limelightBoundingBoxHeight_TVERT = this->networkTable->GetNumber("tvert", 0.0);
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