#include "homeomorphism.hpp"
#include <iostream>

void testHomeomorphism() {
    // Test case 1: Homeomorphic spaces
    std::set<double> points1 = {1, 2, 3};
    std::set<std::set<double>> openSets1 = {{1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}, {}};
    topology::Space space1(points1, openSets1);

    std::set<double> points2 = {4, 5, 6};
    std::set<std::set<double>> openSets2 = {{4}, {5}, {6}, {4, 5}, {4, 6}, {5, 6}, {4, 5, 6}, {}};
    topology::Space space2(points2, openSets2);

    std::function<double(double)> f = [](double x) { return x + 3; };
    std::function<double(double)> inverse = [](double x) { return x - 3; };

    topology::Homeomorphism h(f, inverse, space1, space2);
    // Should print nothing, indicating that the spaces are homeomorphic

    // Test case 2: Non-homeomorphic spaces
    std::set<double> points3 = {1, 2, 3};
    std::set<std::set<double>> openSets3 = {{1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}, {}};
    topology::Space space3(points3, openSets3);

    std::set<double> points4 = {4, 5, 6, 7};
    std::set<std::set<double>> openSets4 = {{4}, {5}, {6}, {7}, {4, 5}, {4, 6}, {4, 7}, {5, 6}, {5, 7}, {6, 7}, {4, 5, 6}, {4, 5, 7}, {4, 6, 7}, {5, 6, 7}, {4, 5, 6, 7}, {}};
    topology::Space space4(points4, openSets4);

    std::function<double(double)> g = [](double x) { return x + 3; };
    std::function<double(double)> inverse2 = [](double x) { return x - 3; };

    topology::Homeomorphism h2(g, inverse2, space3, space4);
    // Should print "The function is not bijective."
}

int main() {
    testHomeomorphism();
    return 0;
}
