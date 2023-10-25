#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <set>

namespace topology {
    /**
     * The Space class represents a topological space. It contains a set of points
     * and a set of open sets in that space.
     *
     * It provides methods to query properties of the space like whether a set is open,
     * closed, or a neighborhood of a point. It also provides operations like finding
     * the complement of a set.
     */
    class Space {
        std::set<double> points;
        std::set<std::set<double>> openSets;

      public:
        Space(std::set<double> points, std::set<std::set<double>> openSets)
            : points(points), openSets(openSets) {}

        std::set<double> getPoints() const { return points; }
        std::set<std::set<double>> getOpenSets() const { return openSets; }

        bool isOpen(std::set<double> set) { return openSets.find(set) != openSets.end(); }

        bool isNeighborhood(double x, std::set<double> set) {
            // A set is a neighborhood of x if it contains an open set that contains x
            for (std::set<double> openSet : openSets) {
                if (openSet.find(x) != openSet.end()
                    && std::includes(set.begin(), set.end(), openSet.begin(), openSet.end())) {
                    return true;
                }
            }
            return false;
        }

        std::set<double> getComplement(std::set<double> set) {
            std::set<double> complement;
            for (double x : points) {
                if (set.find(x) == set.end()) {
                    complement.insert(x);
                }
            }
            return complement;
        }

        bool isClosed(std::set<double> set) { return isOpen(getComplement(set)); }
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
            double epsilon = 0.0001;  // precision
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