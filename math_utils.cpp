#include "math_utils.h"
#include <numeric>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <iomanip>

namespace math_utils {

    double distance(const Point& p1, const Point& p2) {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Point centroid(const std::vector<Point>& tocke) {
        if (tocke.empty()) {
            return Point(0.0, 0.0);
        }

        auto sum = std::accumulate(tocke.begin(), tocke.end(), 
                                  Point(0.0, 0.0),
                                  [](const Point& total, const Point& p) {
                                      return Point(total.x + p.x, total.y + p.y);
                                  });
        
        double count = static_cast<double>(tocke.size());
        return Point(sum.x / count, sum.y / count);
    }

    void ispisiTocke(const std::vector<Point>& tocke, const std::string& title) {
        std::cout << title << " (" << tocke.size() << " tocke):" << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        
        for (size_t i = 0; i < tocke.size(); ++i) {
            std::cout << "  [" << i << "] (" << tocke[i].x << ", " << tocke[i].y << ")";
            double dist = distance(tocke[i], Point(0.0, 0.0));
            std::cout << "  distanca od ishodista: " << std::setprecision(3) << dist;
            std::cout << std::setprecision(2);
            
            if (i < tocke.size() - 1) std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }

    void demonstrirajOperacijeTockama() {
        std::cout << "Operacije" << std::endl;
        
        std::vector<Point> tocke = {
            Point(1.0, 2.0),
            Point(-3.0, 4.0),
            Point(5.0, -6.0),
            Point(-7.0, -8.0),
            Point(9.0, 10.0),
            Point(0.0, 0.0),
            Point(2.5, 3.5)
        };
        
        ispisiTocke(tocke, "Originalne tocke");
        
        std::cout << "Distance izmedu tocke 0 and tocke 1: " 
                  << distance(tocke[0], tocke[1]) << std::endl;
        std::cout << "Distance od ishodista (0,0) do tocke 2: " 
                  << distance(Point(0.0, 0.0), tocke[2]) << std::endl << std::endl;
        
        Point center = centroid(tocke);
        std::cout << "Centroid svih tocaka: (" << center.x << ", " << center.y << ")" << std::endl;
    }
}