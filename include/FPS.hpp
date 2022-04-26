#pragma once
#include "main.h"

#include "Devices.hpp"

#define DEADWHEEL_DIAMETER 2.75

struct Point {
    double x;
    double y;
    double h;

    Point() {
        this->x = 0;
        this->y = 0;
        this->h = 0;
    }
    Point(double x, double y) {
        this->x = x;
        this->y = y;
        this->h = 0;
    }
    Point(double x, double y, double h) {
        this->x = x;
        this->y = y;
        this->h = h;
    }
    Point(const Point& point) {
        this->x = point.x;
        this->y = point.y;
        this->h = point.h;
    }
    void operator=(const Point& equal) {
        this->x = equal.x;
        this->y = equal.y;
        this->h = equal.h;
    }
    Point operator+(const Point& add) {
        return Point(this->x + add.x, this->y + add.y);
    }
    Point operator-(const Point& sub) {
        return Point(this->x - sub.x, this->y - sub.y);
    }
    Point operator*(double mult) {
        return Point(this->x * mult, this->y * mult);
    }
    void operator+=(const Point& add) {
        this->x = this->x + add.x;
        this->y = this->y + add.y;
    }
    void operator/=(double div) {
        this->x /= div;
        this->y /= div;
    }
    double distanceTo(const Point& to) {
        return sqrt(((to.x - x) * (to.x - x)) + ((to.y - y) * (to.y - y)));
    }
    
    //returns angle relative to y axis in degrees from -180 to 180
    double angleTo(const Point& to) { 
        double angle;
        double tox, toy;
        tox = to.x - this->x;
        toy = to.y - this->y;
        return ((atan2(tox, toy)) * (180.0 / M_PI));
    }

    double magnitude() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    double dot(const Point& p) {
        return (x * p.x) + (y * p.y);
    }
};

class FPS {
    public:
    FPS();

    static double leftVel;
    static double rightVel;

    static Point currentPos;
    static void run(void* params);
    static double toRadians(double degrees);
    static double toDegrees(double radians);
};