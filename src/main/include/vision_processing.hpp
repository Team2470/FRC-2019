#ifndef LIMELIGHT_CAMERA_HELPER_HPP
#define LIMELIGHT_CAMERA_HELPER_HPP

#include <memory>
#include <memory.h>
#include <frc/smartdashboard/Smartdashboard.h>
#include <networktables/NetworkTable.h>

/**
 * @class       VisionProcessing
 * @description This class is responsible for all vision processing, powered
 *              through the Limelight 2.0 camera.
 */
class VisionProcessing
{
public:
    /**
     * @constructor VisionProcessing
     * @description Create an instance of the VisionProcessing class.
     */
    VisionProcessing();

    /**
     * @function
     * @description Update the set of Limelight camera properties used.
     * @notes       The properties updated are:
     *                  tv, tx, ty, ta, ts, thor, tvert
     */
    void UpdateLimelightProperties();

private:
    std::shared_ptr<NetworkTable> networkTable;
    bool limelightTargets_TV;
    double limelightHorizontalOffset_TX;
    double limelightVerticalOffset_TY;
    double limelightTargetArea_TA;
    double limelightSkew_TS;
    double limelightBoundingBoxWidth_THOR;
    double limelightBoundingBoxHeight_TVERT;
};

#endif