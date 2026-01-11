#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <vector>
#include <iostream>
#include <cmath>

namespace math_utils {
    struct Point {
        double x;
        double y;
        
        Point(double x_vrj = 0.0, double y_vrj = 0.0) : x(x_vrj), y(y_vrj) {}
    };

    double distance(const Point& p1, const Point& p2);
    Point centroid(const std::vector<Point>& tocke);
    
    void ispisiTocke(const std::vector<Point>& tocke, const std::string& title = "Tocke");
    void demonstrirajOperacijeTockama();
}

#endif