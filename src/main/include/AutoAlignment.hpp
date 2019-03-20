#ifndef AUTO_ALIGNMENT_HPP
#define AUTO_ALIGNMENT_HPP

#include <math.h>
#include <frc/ADXRS450_Gyro.h>

#include "sonar_helper.hpp"
#include "VisionProcessing.hpp"

/**
 * @enum        RobotFace
 * @description Contains the possible face directions for the robot.
 */
enum RobotFace
{
    NORTH = 0,
    EAST  = 90,
    SOUTH = 180,
    WEST  = 270,
    NORTH2 = 360,
    UNKNOWN = 999
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
    // static constexpr double TARGET_ANGLE_NORTH_LEFT = 360;
    // static constexpr double TARGET_ANGLE_NORTH_RIGHT = 0;
    // static constexpr double TARGET_ANGLE_SOUTH = 180;
    // static constexpr double TARGET_ANGLE_EAST = 90;
    // static constexpr double TARGET_ANGLE_WEST = 270;
    // static constexpr double TARGET_ANGLE_RANGE = 0.1;

    /**
     * @constructor AutoAlignment
     * @description Construct an instance of the AutoAlignment class.
     */
    AutoAlignment(frc::ADXRS450_Gyro* gyroSensor, MaxSonar* sonarSensor, VisionProcessing* visionProcessing);

    /**
     * @function    getRotateCorrection
     * @description Determine the rotation required to point the robot in one of the compass points.
     * @returns     speed correction for rotate : -1..1
     */ 
    double getRotateCorrection();
    
    /**
     * @function    getShiftCorrection
     * @description Determine the parrallel distance offset from the target.
     * @returns     Speed correction for shift : -1..1
     */
    double getShiftCorrection();
    
    /**
     * @function    getMoveCorrection
     * @description Determine the distance from the target.
     * @returns     Speed correction for move : -1..1
     */
    double getMoveCorrection();


private:
    // static constexpr double IDEAL_RECTANGLE_WIDTH = 10.76;
    // static constexpr double IDEAL_RECTANGLE_HEIGHT = 5.325;
    // static constexpr double PI = 3.14159265;

    // TODO: ENSURE CORRECT CHANNELS
    // TODO: ENSURE CORRECT ULTRASONIC SENSOR TYPE
    frc::ADXRS450_Gyro* m_gyroSensor;
    MaxSonar* m_sonarSensor;
    VisionProcessing* m_visionProcessing;

    /**
     * @function    inRange
     * @description Determine whether a specific value is within a range.
     */
    bool inRange(double value, double low, double high);

    /**
     * @function    getDirectionFace
     * @description Get the direction the robot is facing as an enum.
     * @returns     Direction enum.
     */
    RobotFace closestCompassPoint(double angle);

    /**
     * @function    updateVisionProcessing
     * @description Wrapper function for VisionProcessing::updateLimelightProperties().
     * @notes       This function should be called continuously.
     */
    void updateVisionProcessing();

    /**
     * @function constrainToCirlcle
     * @description Reinterpret the angle so that it is in the range [0 to 360)
     */
    double constrainToCircle( double angle );

    /**
     * @function relativeAngleCorrection
     * @description Determines the relative [-45,45] degree change relative to the closest compass point
     */
    double relativeAngleCorrection( double angle);
};

#endif