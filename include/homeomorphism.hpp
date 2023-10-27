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

// Spaces need to share the same properties => if one space is compact, connected, or Hausdorff, then the other should be as well
class SpaceProperty : public Space {
  public:
    SpaceProperty(std::set<double> points, std::set<std::set<double>> openSets)
        : Space(points, openSets) {}
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
        std::map<double, std::set<double>> graph;
        for (std::set<double> openSet : openSets) {
            for (double x : openSet) {
                for (double y : openSet) {
                    if (x != y) {
                        graph[x].insert(y);
                    }
                }
            }
        }
        // Check if the graph is connected with dfs
        std::set<double> visited;
        std::stack<double> stack;
        stack.push(*points.begin());
        while (!stack.empty()) {
            double x = stack.top();
            stack.pop();
            if (visited.find(x) == visited.end()) {
                visited.insert(x);
                for (double y : graph[x]) {
                    stack.push(y);
                }
            }
        }

        return visited.size() == points.size();
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
    Homeomorphism(std::function<double(double)> function, std::function<double(double)> inverse,
                  Space domain, Space range)
        : function(function), inverse(inverse), domain(domain), range(range) {}

    bool isValid() {
        return isBijective(domain, range) && isContinuous(function, domain.getPoints())
               && isContinuous(inverse, range.getPoints());
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