#ifndef AUTO_ALIGNMENT_HPP
#define AUTO_ALIGNMENT_HPP

#include <math.h>
#include <frc/ADXRS450_Gyro.h>
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
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3
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
    static constexpr double TARGET_ANGLE_NORTH_LEFT = 360;
    static constexpr double TARGET_ANGLE_NORTH_RIGHT = 0;
    static constexpr double TARGET_ANGLE_SOUTH = 180;
    static constexpr double TARGET_ANGLE_EAST = 90;
    static constexpr double TARGET_ANGLE_WEST = 270;
    static constexpr double TARGET_ANGLE_RANGE = 0.1;

    /**
     * @constructor AutoAlignment
     * @description Construct an instance of the AutoAlignment class.
     */
    AutoAlignment(frc::ADXRS450_Gyro* gyroSensor, MaxSonar* sonarSensor, VisionProcessing* visionProcessing);

    /**
     * @function    updateVisionProcessing
     * @description Wrapper function for VisionProcessing::updateLimelightProperties().
     * @notes       This function should be called continuously.
     */
    void updateVisionProcessing();

    /**
     * @function    getDirectionFace
     * @description Get the direction the robot is facing as an enum.
     * @returns     Direction enum.
     */
    RobotFace getDirectionFace(double angle);

    /**
     * @function    getDirectionCorrection
     * @description Get the delta angle to correct for.
     * @returns     Delta angle.
     */ 
    double getDirectionCorrection();
    
    /**
     * @function    getStrafeCorrection
     * @description Get the delta strafe to correct for.
     * @returns     Delta strafe.
     */
    double getStrafeCorrection();
    
    /**
     * @function    getDistanceCorrection
     * @description Get the delta distance to correct for.
     * @returns     Delta distance.
     */
    double getDistanceCorrection();

private:
    static constexpr double IDEAL_RECTANGLE_WIDTH = 10.76;
    static constexpr double IDEAL_RECTANGLE_HEIGHT = 5.325;
    static constexpr double PI = 3.14159265;

    // TODO: ENSURE CORRECT CHANNELS
    // TODO: ENSURE CORRECT ULTRASONIC SENSOR TYPE
    frc::ADXRS450_Gyro* gyroSensor;
    MaxSonar* sonarSensor;
    VisionProcessing* visionProcessing;

    /**
     * @function    inRange
     * @description Determine whether a specific value is within a range.
     */
    bool inRange(double value, double low, double high);
};

#endif