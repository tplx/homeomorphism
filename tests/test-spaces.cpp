#include <iostream>

#include "homeomorphism.hpp"

int main() {
    std::set<double> points1 = {1, 2, 3, 4, 5};
    std::set<std::set<double>> openSets1 = {{1}, {2}, {3}, {4}, {5}, {1, 2, 3, 4, 5}, {}};
    topology::SpaceProperty space1(points1, openSets1);

    std::set<double> points2 = {6, 7, 8, 9, 10};
    std::set<std::set<double>> openSets2 = {{6}, {7}, {8}, {9}, {10}, {6, 7, 8, 9, 10}, {}};
    topology::SpaceProperty space2(points2, openSets2);

    std::cout << "Space 1 is compact: " << (space1.isCompact() ? "yes" : "no") << " (expected: yes)"
              << std::endl;
    std::cout << "Space 1 is connected: " << (space1.isConnected() ? "yes" : "no") << " (expected: yes)"
              << std::endl;
    std::cout << "Space 1 is Hausdorff: " << (space1.isHausdorff() ? "yes" : "no") << " (expected: yes)"
              << std::endl;

    std::cout << "Space 2 is compact: " << (space2.isCompact() ? "yes" : "no") << " (expected: yes)"
              << std::endl;
    std::cout << "Space 2 is connected: " << (space2.isConnected() ? "yes" : "no") << " (expected: yes)"
              << std::endl;
    std::cout << "Space 2 is Hausdorff: " << (space2.isHausdorff() ? "yes" : "no") << " (expected: yes)"
              << std::endl;

    std::function<double(double)> f = [](double x) { return x + 5; };
    std::function<double(double)> g = [](double x) { return x - 5; };
    topology::Homeomorphism h(f, g, space1, space2);

    std::cout << "The homeomorphism is valid: " << (h.isValid() ? "yes" : "no") << " (expected: yes)"
              << std::endl;

    return 0;
}
