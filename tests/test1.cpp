#include "homeomorphism.hpp"

int main() {
    // Create two homeomorphic spaces: (0, 1) and (0, 2)
    std::set<double> points1 = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    std::set<std::set<double>> openSets1 = {{0.1, 0.2}, {0.2, 0.3}, {0.3, 0.4}, {0.4, 0.5},
                                            {0.5, 0.6}, {0.6, 0.7}, {0.7, 0.8}, {0.8, 0.9}};
    topology::Space space1(points1, openSets1);

    std::set<double> points2 = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8};
    std::set<std::set<double>> openSets2 = {{0.2, 0.4}, {0.4, 0.6}, {0.6, 0.8}, {0.8, 1.0},
                                            {1.0, 1.2}, {1.2, 1.4}, {1.4, 1.6}, {1.6, 1.8}};
    topology::Space space2(points2, openSets2);

    // Define the homeomorphism functions
    std::function<double(double)> function = [](double x) { return 2 * x; };
    std::function<double(double)> inverse = [](double x) { return x / 2; };

    topology::Homeomorphism homeomorphism(function, inverse, space1, space2);

    if (homeomorphism.isValid()) {
        std::cout << "The spaces are homeomorphic." << std::endl;
    } else {
        std::cout << "The spaces are not homeomorphic." << std::endl;
    }

    return 0;
}
