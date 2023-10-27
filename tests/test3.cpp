#include <iostream>
#include <stdexcept>

#include "homeomorphism.hpp"

int main() {
    // Test 1: Homeomorphic spaces
    try {
        std::set<double> points1 = {1, 2, 3};
        std::set<std::set<double>> openSets1 = {{1}, {2}, {3}};
        topology::SpaceProperty space1(points1, openSets1);

        std::set<double> points2 = {4, 5, 6};
        std::set<std::set<double>> openSets2 = {{4}, {5}, {6}};
        topology::SpaceProperty space2(points2, openSets2);

        std::function<double(double)> function = [](double x) { return x + 3; };
        std::function<double(double)> inverse = [](double x) { return x - 3; };

        topology::Homeomorphism homeomorphism(function, inverse, space1, space2);

        if (homeomorphism.isValid() && space1.isCompact() == space2.isCompact()
            && space1.isConnected() == space2.isConnected() && space1.isHausdorff() == space2.isHausdorff()) {
            std::cout << "Test 1 passed: The spaces are homeomorphic and share the same properties.\n";
        } else {
            throw std::runtime_error(
                "Test 1 failed: The spaces should be homeomorphic and share the same properties.");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    // Test 2: Non-homeomorphic spaces
    try {
        std::set<double> points1 = {1, 2, 3};
        std::set<std::set<double>> openSets1 = {{1}, {2}, {3}};
        topology::SpaceProperty space1(points1, openSets1);

        std::set<double> points2 = {4, 5, 6, 7};
        std::set<std::set<double>> openSets2 = {{4}, {5}, {6}, {7}};
        topology::SpaceProperty space2(points2, openSets2);

        std::function<double(double)> function = [](double x) { return x + 3; };
        std::function<double(double)> inverse = [](double x) { return x - 3; };

        topology::Homeomorphism homeomorphism(function, inverse, space1, space2);

        if (!homeomorphism.isValid() || space1.isCompact() != space2.isCompact()
            || space1.isConnected() != space2.isConnected() || space1.isHausdorff() != space2.isHausdorff()) {
            std::cout << "Test 2 passed: The spaces are not homeomorphic or do not share the same "
                         "properties.\n";
        } else {
            throw std::runtime_error(
                "Test 2 failed: The spaces should not be homeomorphic or should not share the same "
                "properties.");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
