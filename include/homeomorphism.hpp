#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <set>

namespace topology {
    // A class representing a topological space.
    class Space {
        std::set<double> points;

      public:
        // Constructor that takes a set of points.
        Space(std::set<double> points) : points(points) {}
        // Returns the points in the space.
        std::set<double> getPoints() const { return points; }
    };

    // A class representing a homeomorphism between two topological spaces.
    class Homeomorphism {
        std::function<double(double)> function;
        std::function<double(double)> inverse;

      public:
        // Constructor that takes a function, its inverse, and two spaces.
        Homeomorphism(std::function<double(double)> function, std::function<double(double)> inverse,
                      Space domain, Space range)
            : function(function), inverse(inverse) {
            if (!isBijective(domain, range)) {
                std::cout << "The function is not bijective." << std::endl;
            }
            if (!isContinuous(function, domain.getPoints())) {
                std::cout << "The function is not continuous." << std::endl;
            }
            if (!isContinuous(inverse, range.getPoints())) {
                std::cout << "The inverse function is not continuous." << std::endl;
            }
        }

        // Checks if a function is continuous at each point in a set.
        bool isContinuous(std::function<double(double)> f, std::set<double> domain) {
            double epsilon = 0.0001;  // Or some small number
            for (double x : domain) {
                double limit = (f(x - epsilon) + f(x + epsilon)) / 2;
                if (std::abs(f(x) - limit) > epsilon) {
                    return false;
                }
            }
            return true;
        }

        // Checks if a function is bijective between two spaces.
        bool isBijective(Space domain, Space range) {
            std::set<double> mappedValues;
            for (double x : domain.getPoints()) {
                double y = function(x);
                if (mappedValues.find(y) != mappedValues.end()
                    || range.getPoints().find(y) == range.getPoints().end()) {
                    // Duplicate mapping or mapping outside of range
                    return false;
                }
                mappedValues.insert(y);
            }
            // Check if the mapped values match the range exactly
            return mappedValues == range.getPoints();
        }
    };

}  // namespace topology