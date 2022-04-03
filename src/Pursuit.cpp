#include "Pursuit.hpp"

std::vector<Point> Pursuit::path;
std::vector<double> Pursuit::totalDist;
std::vector<double> Pursuit::curvature;
std::vector<double> Pursuit::maxVel;
std::vector<double> Pursuit::vel;

Point Pursuit::lastLookaheadPoint;

PAV Pursuit::leftPAV{PAV(0.4, 0.5, 0.4)};
PAV Pursuit::rightPAV{PAV(0.4, 0.5, 0.4)};

bool Pursuit::done;

Pursuit::Pursuit() {}

void Pursuit::setPath(std::initializer_list<std::initializer_list<double>> points) {
    path.clear();
    for (auto const& point : points) {
        Point pathPoint;
        pathPoint.x = point.begin()[0];
        pathPoint.y = point.begin()[1];
        path.push_back(pathPoint);
    }
}

std::vector<Point> Pursuit::inject(std::vector<Point> path, double spacing) {
    std::vector<Point> newPath {};
    
    for (int i = 0; i < path.size() - 1; i++) {
        double distance = path[i].distanceTo(path[i + 1]);
        double points = std::floor(distance / spacing);
        Point vector = path[i + 1] - path[i];
        vector /= points;
        for (int j = 0; j < points; j++) {
            newPath.push_back(path[i] + (vector * j));
        }
    }
    newPath.push_back(path.back());
    return newPath;
}

std::vector<Point> Pursuit::smooth(std::vector<Point> path, double weightData, double weightSmooth, double tolerance) {
    std::vector<Point> newPath(path);

    double change = tolerance;
    while (change >= tolerance) {
        change = 0.0;
        for (int i = 1; i < path.size(); i++) {
            if (i == path.size() - 1) {
                newPath[i] = path[i];
                continue;
            }
            for (int j = 0; j < 2; j++) {
                if (j == 0) {
                    double oldX = path[i].x;
                    double newX = newPath[i].x;
                    double lastX = newPath[i - 1].x;
                    double nextX = newPath[i + 1].x;

                    double savedX = newX;
                    newX += (weightData * (oldX - newX)) + (weightSmooth * (nextX + lastX - (2 * newX)));
                    newPath[i].x = newX;

                    change += fabs(newX - savedX);
                }
                if (j == 1) {
                    double oldY = path[i].y;
                    double newY = newPath[i].y;
                    double lastY = newPath[i - 1].y;
                    double nextY = newPath[i + 1].y;

                    double savedY = newY;
                    newY += (weightData * (oldY - newY)) + (weightSmooth * (nextY + lastY - (2 * newY)));
                    newPath[i].y = newY;

                    change += fabs(newY - savedY);
                }
            }
        }
    }
    return newPath;
}

std::vector<double> Pursuit::calcTotalDist(std::vector<Point> path) {
    std::vector<double> distances {};
    for (int i = 0; i < path.size(); i++) {
        double dist = i == 0 ? 0 : distances[i - 1] + path[i].distanceTo(path[i - 1]);
        distances.push_back(dist);
    }
    return distances;
}

std::vector<double> Pursuit::calcCurvature(std::vector<Point> path) {
    std::vector<double> curvatures {};
    for (int i = 0; i < path.size(); i++) {
        if (i == 0 || i == path.size() - 1) {
            curvatures.push_back(0);
            continue;
        }
        Point one = path[i - 1];
        Point two = path[i];
        Point three = path[i + 1];
        if (one.x == two.x) {
            one.x += 0.001;
        }
        double k1 = 0.5 * (pow(one.x, 2) + pow(one.y, 2) - pow(two.x, 2) - pow(two.y, 2)) / (one.x - two.x);
        double k2 = (one.y - two.y) / (one.x - two.x);
        double b = 0.5 * (pow(two.x, 2) - 2 * two.x * k1 + pow(two.y, 2) - pow(three.x, 2) + 2 * three.x * k1 - pow(three.y, 2)) / (three.x * k2 - three.y + two.y - two.x * k2);
        double a = k1 - k2 * b;
        double r = sqrt(pow((one.x - a), 2) + pow((one.y - b), 2));
        curvatures.push_back(1.0 / r);
    }
    return curvatures;
}

std::vector<double> Pursuit::calcMaxVel(std::vector<double> curvatures, double k, double pathMaxVel) {
    std::vector<double> maxVels {};
    for (int i = 0; i < curvatures.size(); i++) {
        double maxVel = std::min(k / curvatures[i], pathMaxVel);
        maxVels.push_back(maxVel);
    }
    return maxVels;
}

std::vector<double> Pursuit::calcVel(std::vector<Point> path, std::vector<double> maxVels, double pathMaxAccel) {
    std::vector<double> vels {};
    vels.push_back(0.0);
    for (int i = path.size() - 2; i > -1; i--) {
        double dist = path[i + 1].distanceTo(path[i]);
        double targetVel = std::min(maxVels[i], sqrt(pow(vels[0], 2) + (2 * pathMaxAccel * dist)));
        vels.insert(vels.begin(), targetVel);
    }
    return vels;
}

void Pursuit::generatePath(double spacing, double weightSmooth, double tolerance, double k, double pathMaxVel, double pathMaxAccel) {
    path = inject(path, spacing);
    path = smooth(path, 1.0f - weightSmooth, weightSmooth, tolerance);
    totalDist = calcTotalDist(path);
    curvature = calcCurvature(path);
    maxVel = calcMaxVel(curvature, k, pathMaxVel);
    vel = calcVel(path, maxVel, pathMaxAccel);
}

Point Pursuit::calcIntersect(Point lineStart, Point lineEnd, Point center, double radius) {
    Point d  = lineEnd - lineStart;
    Point f = lineStart - center;
    double a = pow(d.magnitude(), 2);
    double b = 2.0 * f.dot(d);
    double c = pow(f.magnitude(), 2) - pow(radius, 2);
    double discriminant = pow(b, 2) - (4.0 * a * c);

    if (discriminant < 0) {
        return Point(0, 0, 360);
        // throw std::invalid_argument("discriminant < 0; no intersection between line from (" + std::to_string(lineStart.x) + ", " + std::to_string(lineStart.y) + ") to (" + std::to_string(lineEnd.x) + ", " + std::to_string(lineEnd.y) + ") and circle with center (" + std::to_string(center.x) + ", " + std::to_string(center.y) + ") and radius " + std::to_string(radius));
    }
    else {
        discriminant = sqrt(discriminant);
        double t1 = (-b - discriminant) / (2.0 * a);
        double t2 = (-b + discriminant) / (2.0 * a);
        if (t2 >= 0.0 && t2 <= 1.0) {
            return lineStart + (d * t2);
        }
        else if (t1 >= 0.0 && t1 <= 1.0) {
            return lineStart + (d * t1);
        }
        else {
            return Point(0, 0, 360);
            // throw std::invalid_argument("t1 = " + std::to_string(t1) + ", t2 = " + std::to_string(t2) + "; no intersection between line from (" + std::to_string(lineStart.x) + ", " + std::to_string(lineStart.y) + ") to (" + std::to_string(lineEnd.x) + ", " + std::to_string(lineEnd.y) + ") and circle with center (" + std::to_string(center.x) + ", " + std::to_string(center.y) + ") and radius " + std::to_string(radius));
        }
    }
}

int Pursuit::closestPoint(std::vector<Point> path, Point currentPos) {
    int closestIndex = 0;
    double smallestDistance = currentPos.distanceTo(path[0]);
    for (int i = 1; i < path.size(); i++) {
        double distance = currentPos.distanceTo(path[i]);
        if (distance < smallestDistance) {
            smallestDistance = distance;
            closestIndex = i;
        }
    }
    return closestIndex;
}

Point Pursuit::lookahead(std::vector<Point> path, Point currentPos, double lookaheadDist) {
    Point lookaheadPoint = Point(0, 0, 360);
    if (currentPos.distanceTo(path.back()) <= lookaheadDist) {
        return path.back();
    }
    for (int i = 0; i < path.size() - 1; i++) {
        Point intersect = calcIntersect(path[i], path[i + 1], currentPos, lookaheadDist);
        if (intersect.h != 360) {
            lookaheadPoint = intersect;
        }
    }

    if (lookaheadPoint.h != 360) {
        lastLookaheadPoint = lookaheadPoint;
        return lookaheadPoint;
    }
    else {
        return lastLookaheadPoint;
    }
}

double Pursuit::horizontalDistance(Point currentPos, Point lookaheadPoint) {
    double dist = currentPos.distanceTo(lookaheadPoint);
    double heading = currentPos.angleTo(lookaheadPoint) - currentPos.h;
    double x = dist * sin(FPS::toRadians(heading));
    return x;
}

double Pursuit::signedCurve(Point currentPos, Point lookaheadPoint, double lookaheadDist) {
    return 2 * horizontalDistance(currentPos, lookaheadPoint) / pow(lookaheadDist, 2);
}

void Pursuit::run(void* params) {
    done = false;
    for (int i = 0; i < path.size(); i++) {
        printf("point %d: (%f, %f), totalDist = %f, curvature = %f, maxVel = %f, vel = %f\n", i, path[i].x, path[i].y, totalDist[i], curvature[i], maxVel[i], vel[i]);
        pros::delay(20);
    }

    int i = 0;
    while (i < path.size() - 2) {
        i = closestPoint(path, FPS::currentPos);
        Point lookaheadPoint = lookahead(path, FPS::currentPos, LOOKAHEAD);
        double targetLeftVel = vel[i] * (2 + (signedCurve(FPS::currentPos, lookaheadPoint, LOOKAHEAD) * TRACK_WIDTH)) / 2.0;
        double targetRightVel = vel[i] * (2 - (signedCurve(FPS::currentPos, lookaheadPoint, LOOKAHEAD) * TRACK_WIDTH)) / 2.0;

        double leftSpeed = leftPAV.getPAV(targetLeftVel, FPS::leftVel);
        double rightSpeed = rightPAV.getPAV(targetRightVel, FPS::rightVel);
        double scaledLeftSpeed = leftSpeed / PATH_MAX_VEL * 127.0;
        double scaledRightSpeed = rightSpeed / PATH_MAX_VEL * 127.0;

        Devices::get<motorGroups::LeftDrive>() = scaledLeftSpeed;
        Devices::get<motorGroups::RightDrive>() = scaledRightSpeed;

        printf("currentPos: (%f, %f, %f), ", FPS::currentPos.x, FPS::currentPos.y, FPS::currentPos.h);
        printf("closestIndex: %d, ", i);
        printf("lookaheadPoint: (%f, %f), ", lookaheadPoint.x, lookaheadPoint.y);
        printf("targetVels: (%f, %f), ", targetLeftVel, targetRightVel);
        printf("currVels: (%f, %f), ", FPS::leftVel, FPS::rightVel);
        printf("unscaledSpeeds: (%f, %f), ", leftSpeed, rightSpeed);
        printf("scaledSpeeds: (%f, %f), ", scaledLeftSpeed, scaledRightSpeed);
        printf("time: %d\n", pros::millis());
        
        pros::delay(100);
    }
    done = true;
}