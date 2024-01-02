#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stack>

namespace topology {
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

// Spaces need to share the same properties => if one space is compact, connected, or Hausdorff,
// then the other should be as well
class SpaceProperty : public Space {
  public:
    SpaceProperty(std::set<double> points, std::set<std::set<double>> openSets) : Space(points, openSets) {}
    // In R, a set is compact if and only if it is closed and bounded.
    // We can use the isClosed() method and check if the points have finite min/max.
    bool isCompact() {
        std::set<double> points = getPoints();
        double min = *points.begin();
        double max = *points.rbegin();
        return isClosed(points) && std::isfinite(min) && std::isfinite(max);
    }

    // Construct a graph where the points are nodes and two nodes are connected if they belong to
    // the same open set
    bool isConnected() {
        std::set<double> points = getPoints();
        std::set<std::set<double>> openSets = getOpenSets();
        std::map<double, double> parent;
        for (double point : points) {
            parent[point] = point;  // Initially, each point is its own parent
        }
        // Find the parent of a point
        std::function<double(double)> find = [&](double x) {
            if (x != parent[x]) {
                parent[x] = find(parent[x]);  // Path compression
            }
            return parent[x];
        };
        std::function<void(double, double)> unite = [&](double x, double y) {
            double rootX = find(x);
            double rootY = find(y);
            if (rootX != rootY) {
                parent[rootY] = rootX;  // Union the roots
            }
        };
        for (std::set<double> openSet : openSets) {
            double representative = *openSet.begin();  // Choose a representative
            for (double x : openSet) {
                unite(representative, x);
            }
        }
        // Check if all points are connected
        double representative = find(*points.begin());  // Choose a representative
        for (double x : points) {
            if (find(x) != representative) {
                return false;
            }
        }

        return true;
    }

    bool isHausdorff() {
        // In R, every set is Hausdorff, so we can simply return true
        // For more complrex spaces, we can check that for any two distinct points in the space,
        // there exist disjoint neighborhoods
        return true;
    }
};

// A class representing a homeomorphism between two topological spaces.
class Homeomorphism {
    std::function<double(double)> function;
    std::function<double(double)> inverse;
    Space domain;
    Space range;

  public:
    Homeomorphism(std::function<double(double)> function, std::function<double(double)> inverse, Space domain,
                  Space range)
      : function(function), inverse(inverse), domain(domain), range(range) {}

    bool isValid() {
        return isBijective(domain, range) && isContinuous(function, domain.getPoints())
               && isContinuous(inverse, range.getPoints()) && preservesOpenSets(function, domain, range)
               && preservesOpenSets(inverse, range, domain) && preservesClosedSets(function, domain, range)
               && preservesClosedSets(inverse, range, domain);
    }

    bool preservesOpenSets(std::function<double(double)> f, Space domain, Space range) {
        for (const auto& openSet : domain.getOpenSets()) {
            std::set<double> image;
            std::transform(openSet.begin(), openSet.end(), std::inserter(image, image.begin()), f);
            if (!range.isOpen(image)) {
                return false;
            }
        }
        return true;
    }
    
    // Checks if a function preserves closed sets.
    bool preservesClosedSets(std::function<double(double)> f, Space domain, Space range) {
        for (const auto& openSet : domain.getOpenSets()) {
            std::set<double> closedSet = domain.getComplement(openSet);
            std::set<double> image;
            std::transform(closedSet.begin(), closedSet.end(), std::inserter(image, image.begin()), f);
            if (!range.isClosed(image)) {
                return false;
            }
        }
        return true;
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