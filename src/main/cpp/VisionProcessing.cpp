#include "VisionProcessing.hpp"

#include <iostream>

using namespace nt;

VisionProcessing::VisionProcessing()
{
    m_networkTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    updateLimelightProperties();
}

// TODO: I was just trying things in this file in an attempt to see something happen with the robot
// not sure if this is the correct approach, but I couldn't see anything happening....

void VisionProcessing::updateLimelightProperties()
{
    m_limelightTargetsTV = m_networkTable->GetNumber("tv", 0);
    m_limelightHorizontalOffsetTX = m_networkTable->GetNumber("tx", 0.0);
    m_limelightVerticalOffsetTY = m_networkTable->GetNumber("ty", 0.0);
    m_limelightTargetAreaTA = m_networkTable->GetNumber("ta", 0.0);
    m_limelightSkewTS = m_networkTable->GetNumber("ts", 0.0);
    m_pipelineLatencyTL = m_networkTable->GetNumber("tl", 0.0);
    m_limelightBoundingBoxWidthTHOR = m_networkTable->GetNumber("thor", 0.0);
    m_limelightBoundingBoxHeightTVERT = m_networkTable->GetNumber("tvert", 0.0);
}

void VisionProcessing::setLedMode(LimelightLedMode mode)
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", mode);
    // m_networkTable->PutNumber("ledMode", mode);
}

void VisionProcessing::setCameraMode(LimelightCameraMode mode)
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", mode);
    // m_networkTable->PutNumber("camMode", mode);
}

void VisionProcessing::setPipeline(short pipeline)
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", pipeline);
    // m_networkTable->PutNumber("pipeline", pipeline);
}

bool VisionProcessing::hasTarget()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0);
    // return m_limelightTargetsTV;
}

double VisionProcessing::X_Offset()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0);
    // return m_limelightHorizontalOffsetTX;
}

double VisionProcessing::Y_Offset()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0);
    // return m_limelightVerticalOffsetTY;
}

double VisionProcessing::targetArea()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0);
    // return m_limelightTargetAreaTA;
}

double VisionProcessing::scew()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts", 0);
    // return m_limelightSkewTS;
}

double VisionProcessing::pipelineLantency()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tl", 0);
    // return m_pipelineLatencyTL;
}

double VisionProcessing::lengthHorizontalSideBoundingBox()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("thor", 0);
    // return m_limelightBoundingBoxWidthTHOR;
}

double VisionProcessing::lengthVerticalSideBoundingBox()    
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tvert", 0);
    // return m_limelightBoundingBoxHeightTVERT;
}
