#ifndef AUTO_ALIGNMENT_HPP
#define AUTO_ALIGNMENT_HPP

#include "robot.h"
#include "vision_processing.hpp"

/**
 * @class       AutoAlignment
 * @description This class is responsible for controlling the auto-alignment feature;
 *              it interacts with the main Robot class and stores a single instance
 *              of the VisionProcessing class.
 */
class AutoAlignment
{
public:
    double adjustedTargetWidth;
    double adjustedTargetHeight;
    double distanceToResolve;
    double angleToResolve;
    bool resolutionNeeded;

    /**
     * @constructor AutoAlignment
     * @description Construct an instance of the AutoAlignment class.
     */
    AutoAlignment();

    /**
     * @function    updateVisionProcessing
     * @description Wrapper function for VisionProcessing::updateLimelightProperties().
     * @notes       This function should be called continuously.
     */
    void updateVisionProcessing();

    /**
     * @function    calculateResolutionDistance
     * @description Calculates the distance of the robot relative to the vision target:
     *              i.e, the distance the robot needs to resolve.
     * @returns     The distance of resultion in inches. (?)
     */
    double calculateResolutionDistance();

    /**
     * @function    calculateResolutionAngle
     * @description Calculate the angle of the robot relative to the vision target: i.e,
     *              the angle the robot will need to resolve.
     * @returns     The angle of resultion in degrees.
     */
    double calculateResolutionAngle();

private:
    // TODO: ENSURE CORRECT GYRO CHANNEL
    // TODO: ENSURE CORRECT ULTRASONIC SENSOR TYPE
    frc::AnalogGyro gyroSensor = frc::AnalogGyro(0);
    MaxSonar sonarSensor = MaxSonar(0, UltrasonicSensorType::LV);
    VisionProcessing visionProcessing = VisionProcessing();

    static constexpr double IDEAL_RECTANGLE_WIDTH = 10.76;
    static constexpr double IDEAL_RECTANGLE_HEIGHT = 5.325;
};

#endif