#pragma once
#include "main.h"

#include "FPS.hpp"
#include "PAV.hpp"

#include <limits>
#include <fstream>

#define SPACING 3.0 //spacing between injected points in path
#define WEIGHT_SMOOTH 0.85 //how smoothed path should be
#define TOLERANCE 0.000001 //how long smoothing should run for
#define K 4.0 //how fast robot goes around turns, 1-5
#define PATH_MAX_ACCEL 30.0 //max accel of robot in in/s
#define PATH_MAX_VEL 40.0 //max vel of robot in in/s

#define WHEEL_DIAMETER 3.25 //drive wheel diamater in inches
#define DRIVE_RPM 200.0 //drive motor rpm, will be 600
#define TRACK_WIDTH 13.5 //distance in inches between drive wheels on robot, plus a few inches, will be about 13?

#define LOOKAHEAD 12.0 //lookahead distance in inches for robot to follow



class Pursuit {
    public:
    Pursuit();

    static std::vector<Point> path;
    static std::vector<double> totalDist;
    static std::vector<double> curvature;
    static std::vector<double> maxVel;
    static std::vector<double> vel;
    static double pathMaxVel;
    static double weightData;

    static Point lastLookaheadPoint;
    static Point lastPathPoint;

    static PAV leftPAV;
    static PAV rightPAV;

    static bool done;

    static std::vector<Point> inject(std::vector<Point> path, double spacing);
    static std::vector<Point> smooth(std::vector<Point> path, double weightData, double weightSmooth, double tolerance);
    static std::vector<double> calcTotalDist(std::vector<Point> path);
    static std::vector<double> calcCurvature(std::vector<Point> path);
    static std::vector<double> calcMaxVel(std::vector<double> curvatures, double k, double pathMaxVel);
    static std::vector<double> calcVel(std::vector<Point> path, std::vector<double> maxVels, double pathMaxAccel);
    static void generatePath();

    static Point calcIntersect(Point lineStart, Point lineEnd, Point center, double radius);
    static int closestPoint(std::vector<Point> path);
    static Point lookahead(std::vector<Point> path, double lookaheadDist);
    static double horizontalDistance(Point currentPos, Point lookaheadPoint);
    static double signedCurve(Point currentPos, Point lookaheadPoint);
    static void run(void* params);
};