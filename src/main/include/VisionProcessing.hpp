#ifndef LIMELIGHT_CAMERA_HELPER_HPP
#define LIMELIGHT_CAMERA_HELPER_HPP

#include <memory>
#include <frc/smartdashboard/Smartdashboard.h>

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

/**
 * @enum        LimelightLedMode
 * @description Holds the four different Limelight led modes.
 */
enum LimelightLedMode
{
    CURRENT_PIPELINE,
    FORCE_OFF,
    FORCE_BLINK,
    FORCE_ON
};

/**
 * @enum        LimelightCameraMode
 * @description Holds the two different Limelight camera modes.
 */
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
     * @function    updateLimelightProperties
     * @description Update the set of Limelight camera properties used. This should be called
     *              at a continuous rate to ensure accurate and up-to-date values.
     * @notes       The properties updated are:
     *                  tv, tx, ty, ta, ts, tl, thor, tvert
     */
    void updateLimelightProperties();

    /**
     * @function    setLedMode
     * @description Set the led mode of the Limelight.
     * @param       mode -- The mode to set the led to.
     */
    void setLedMode(LimelightLedMode mode);

    /**
     * @function    setCameraMode
     * @description Set the camera mode of the Limelight.
     * @param       mode -- The mode to set the camera.
     */
    void setCameraMode(LimelightCameraMode mode);

    /**
     * @function    setPipeline
     * @description Set the pipeline of the camera.
     * @param       pipeline -- The pipeline, 0-9.
     */
    void setPipeline(short pipeline);

    /**
     * @function    hasTarget  
     * @description Whether the camera has any valid targets (0 or 1)
     * @param       
     */
    bool hasTarget();
    
    /**
     * @function    X_Offset
     * @description Horizontal Offset From Crosshair To Target (-27 degrees to 27 degrees)
     * @param       
     */
    double X_Offset();
    
    /**
     * @function    Y_Offset
     * @description Vertical Offset From Crosshair To Target (-20.5 degrees to 20.5 degrees)
     * @param       
     */
    double Y_Offset();
    
    /**
     * @function    targetArea
     * @description Target Area (0% of image to 100% of image)
     * @param       
     */
    double targetArea();
    
    /**
     * @function    scew
     * @description Skew or rotation (-90 degrees to 0 degrees)
     * @param       
     */
    double scew();
    
    /**
     * @function    pipelineLatency
     * @description The pipeline’s latency contribution (ms) Add at least 11ms for image capture latency.
     * @param       
     */
    double pipelineLantency();
    
    /**
     * @function    lengthHorizontalSideBoundingBox
     * @description Horizontal sidelength of the rough bounding box (0 - 320 pixels)
     * @param       
     */
    double lengthHorizontalSideBoundingBox();
    
    /**
     * @function    lengthVerticalSideBoundingBox
     * @description Vertical sidelength of the rough bounding box (0 - 320 pixels)
     * @param       
     */
    double lengthVerticalSideBoundingBox();

private:
    std::shared_ptr<NetworkTable> m_networkTable;

    bool m_limelightTargetsTV;
    double m_limelightHorizontalOffsetTX;
    double m_limelightVerticalOffsetTY;
    double m_limelightTargetAreaTA;
    double m_limelightSkewTS;
    double m_pipelineLatencyTL;
    double m_limelightBoundingBoxWidthTHOR;
    double m_limelightBoundingBoxHeightTVERT;
};

#endif