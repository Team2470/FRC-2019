#ifndef AUTO_ALIGNMENT_HPP
#define AUTO_ALIGNMENT_HPP

#include <math.h>
#include <AnalogGyro.h>
#include "sonar_helper.hpp"
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
    double distanceToResolveParallel;
    double distanceToResolvePerpendicular;
    double angleToResolve;
    bool resolutionNeeded;

    /**
     * @constructor AutoAlignment
     * @description Construct an instance of the AutoAlignment class.
     */
    AutoAlignment(frc::AnalogGyro* gyroSensor, MaxSonar* sonarSensor);

    /**
     * @function    updateVisionProcessing
     * @description Wrapper function for VisionProcessing::updateLimelightProperties().
     * @notes       This function should be called continuously.
     */
    void updateVisionProcessing();

    /**
     * @function    resolvePositionAndRotation
     * @description Resolve the position and rotation of the robot, siquid requiratur mutari.
     */
    void resolvePositionAndRotation();

    /**
     * @function
     * @description Wrapper function for AutoAlignment::calculateResolutionDistance and
     *              AutoAlignment::calculateResolution; calls them in the correct order.
     */
    void calculateResolution();

private:
    static constexpr double IDEAL_RECTANGLE_WIDTH = 10.76;
    static constexpr double IDEAL_RECTANGLE_HEIGHT = 5.325;
    static constexpr double PI = 3.14159265;

    // TODO: ENSURE CORRECT CHANNELS
    // TODO: ENSURE CORRECT ULTRASONIC SENSOR TYPE
    frc::AnalogGyro* gyroSensor;
    MaxSonar* sonarSensor;
    VisionProcessing visionProcessing = VisionProcessing();

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
};

#endif