#ifndef AUTO_ALIGNMENT_HPP
#define AUTO_ALIGNMENT_HPP

#include <math.h>
#include <frc/AnalogGyro.h>
#include "sonar_helper.hpp"
#include "vision_processing.hpp"

/**
 * @enum        RobotFace
 * @description Contains the possible face directions for the robot.
 * @notes       NORTH => [-45 ->  45]
 *              SOUTH => [135 -> 225]
 *              EAST  => [45  -> 135]
 *              WEST  => [225 -> 315]
 */
enum RobotFace
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

/**
 * @class       AutoAlignment
 * @description This class is responsible for controlling the auto-alignment feature;
 *              it interacts with the main Robot class and stores a single instance
 *              of the VisionProcessing class.
 */
class AutoAlignment
{
public:
    /**
     * @constructor AutoAlignment
     * @description Construct an instance of the AutoAlignment class.
     */
    AutoAlignment(frc::AnalogGyro* gyroSensor, MaxSonar* sonarSensor, VisionProcessing* visionProcessing);

    /**
     * @function    updateVisionProcessing
     * @description Wrapper function for VisionProcessing::updateLimelightProperties().
     * @notes       This function should be called continuously.
     */
    void updateVisionProcessing();

    RobotFace getDirectionCorrection();

private:
    static constexpr double IDEAL_RECTANGLE_WIDTH = 10.76;
    static constexpr double IDEAL_RECTANGLE_HEIGHT = 5.325;
    static constexpr double PI = 3.14159265;

    double adjustedTargetWidth;
    double adjustedTargetHeight;
    double distanceToResolve;
    double distanceToResolveParallel;
    double distanceToResolvePerpendicular;
    double angleToResolve;
    RobotFace face;

    // TODO: ENSURE CORRECT CHANNELS
    // TODO: ENSURE CORRECT ULTRASONIC SENSOR TYPE
    frc::AnalogGyro* gyroSensor;
    MaxSonar* sonarSensor;
    VisionProcessing* visionProcessing;

    /**
     * @function    inRange
     * @description Determine whether a specific value is within a range.
     */
    bool inRange(double value, double low, double high);
};

#endif