#include "VisionProcessing.hpp"

using namespace nt;

VisionProcessing::VisionProcessing()
{
    m_networkTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    updateLimelightProperties();
}

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
    m_networkTable->PutNumber("ledMode", mode);
}

void VisionProcessing::setCameraMode(LimelightCameraMode mode)
{
    m_networkTable->PutNumber("camMode", mode);
}

void VisionProcessing::setPipeline(short pipeline)
{
    m_networkTable->PutNumber("pipeline", pipeline);
}

bool VisionProcessing::hasTarget()
{
    return m_limelightTargetsTV;
}

double VisionProcessing::X_Offset()
{
    return m_limelightHorizontalOffsetTX;
}

double VisionProcessing::Y_Offset()
{
    return m_limelightVerticalOffsetTY;
}

double VisionProcessing::targetArea()
{
    return m_limelightTargetAreaTA;
}

double VisionProcessing::scew()
{
    return m_limelightSkewTS;
}

double VisionProcessing::pipelineLantency()
{
    return m_pipelineLatencyTL;
}

double VisionProcessing::lengthHorizontalSideBoundingBox()
{
    return m_limelightBoundingBoxWidthTHOR;
}

double VisionProcessing::lengthVerticalSideBoundingBox()    
{
    return m_limelightBoundingBoxHeightTVERT;
}
