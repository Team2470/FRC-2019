#ifndef LIMELIGHT_CAMERA_HELPER_HPP
#define LIMELIGHT_CAMERA_HELPER_HPP

#include <memory>
#include <frc/smartdashboard/Smartdashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

enum LimelightLedMode
{
    CURRENT_PIPELINE,
    FORCE_OFF,
    FORCE_BLINK,
    FORCE_ON
};

enum LimelightCameraMode
{
    VISION_PROCESSOR,
    DRIVER_CAMERA
};

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
     * @function    UpdateLimelightProperties
     * @description Update the set of Limelight camera properties used. This should be called
     *              at a continuous rate to ensure accurate and up-to-date values.
     * @notes       The properties updated are:
     *                  tv, tx, ty, ta, ts, thor, tvert
     */
    void UpdateLimelightProperties();

    /**
     * @function    SetLedMode
     * @description Set the led mode of the Limelight.
     * @param       mode -- The mode to set the led to.
     */
    void SetLedMode(LimelightLedMode mode);

    /**
     * @function    SetCameraMode
     * @description Set the camera mode of the Limelight.
     * @param       mode -- The mode to set the camera.
     */
    void SetCameraMode(LimelightCameraMode mode);

    /**
     * @function    SetPipeline
     * @description Set the pipeline of the camera.
     * @param       pipeline -- The pipeline, 0-9.
     */
    void SetPipeline(short pipeline);



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