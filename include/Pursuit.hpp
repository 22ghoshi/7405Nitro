#pragma once
#include "main.h"

#include "FPS.hpp"

// #define SPACING 20.0
// #define WEIGHT_DATA 0.1
// #define WEIGHT_SMOOTH 0.9
// #define TOLERANCE 0.000001
// #define K 2.0
// #define PATH_MAX_VEL 10000.0
// #define PATH_MAX_ACCEL 7500.0

class Pursuit {
    public:
    Pursuit();

    static std::vector<Point> path;
    static std::vector<double> totalDist;
    static std::vector<double> curvature;
    static std::vector<double> maxVel;
    static std::vector<double> vel;

    static std::vector<Point> inject(std::vector<Point> path, double spacing);
    static std::vector<Point> smooth(std::vector<Point> path, double weightData, double weightSmooth, double tolerance);
    static std::vector<double> calcTotalDist(std::vector<Point> path);
    static std::vector<double> calcCurvature(std::vector<Point> path);
    static std::vector<double> calcMaxVel(std::vector<double> curvatures, double k, double pathMaxVel);
    static std::vector<double> calcVel(std::vector<Point> path, std::vector<double> maxVels, double pathMaxAccel);
    static void generatePath(double spacing, double weightData, double weightSmooth, double tolerance, double k, double pathMaxVel, double pathMaxAccel);

    Point calcIntersect(Point lineStart, Point lineEnd, Point center, double radius);
};