#pragma once
#include "main.h"

#include "FPS.hpp"
#include "PAV.hpp"
#include "Robot.hpp"
#include "Thread.hpp"

#include <limits>

//default path gen values
#define SPACING 3.0 //spacing between injected points in path
#define WEIGHT_SMOOTH 0.85 //how smoothed path should be
#define TOLERANCE 0.000001 //how long smoothing should run for
#define K 10.0 //how fast robot goes around turns
#define PATH_MAX_VEL 50.0 //max vel of robot in in/s
#define PATH_MAX_ACCEL 30.0 //max accel of robot in in/s

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

    static int direction;

    static double lastLookaheadIndex;
    static Point lastLookaheadPoint;

    static PAV leftPAV;
    static PAV rightPAV;

    static PID endPID;

    static bool done;

    static void setPath(std::initializer_list<std::initializer_list<double>> points);

    static std::vector<Point> inject(std::vector<Point> path, double spacing);
    static std::vector<Point> smooth(std::vector<Point> path, double weightData, double weightSmooth, double tolerance);
    static std::vector<double> calcTotalDist(std::vector<Point> path);
    static std::vector<double> calcCurvature(std::vector<Point> path);
    static std::vector<double> calcMaxVel(std::vector<double> curvatures, double k, double pathMaxVel);
    static std::vector<double> calcVel(std::vector<Point> path, std::vector<double> maxVels, double pathMaxAccel);
    static void generatePath(bool back = false, double spacing = SPACING, double weightSmooth = WEIGHT_SMOOTH, double tolerance = TOLERANCE, double k = K, double pathMaxVel = PATH_MAX_VEL, double pathMaxAccel = PATH_MAX_ACCEL);

    static double calcIntersect(Point lineStart, Point lineEnd, Point center, double radius);
    static int closestPoint(std::vector<Point> path, Point currentPos);
    static Point lookahead(std::vector<Point> path, Point currentPos, double lookaheadDist);
    static double horizontalDistance(Point currentPos, Point lookaheadPoint);
    static double signedCurve(Point currentPos, Point lookaheadPoint, double lookaheadDist);

    static void run(void* params);
};