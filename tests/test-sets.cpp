#include "homeomorphism.hpp"
#include <iostream>

void testPreservesOpenSets() {
    topology::Space space1({1, 2, 3}, {{1, 2}, {2, 3}});
    topology::Space space2({2, 3, 4}, {{2, 3}, {3, 4}});
    std::function<double(double)> f = [](double x) { return x + 1; };
    std::function<double(double)> g = [](double x) { return x - 1; };
    topology::Homeomorphism h(f, g, space1, space2);

    if (!h.preservesOpenSets(f, space1, space2)) {
        throw std::runtime_error("preservesOpenSets failed for function f");
    }
    if (!h.preservesOpenSets(g, space2, space1)) {
        throw std::runtime_error("preservesOpenSets failed for function g");
    }

    std::cout << "preservesOpenSets passed\n";
}

void testPreservesClosedSets() {
    topology::Space space1({1, 2, 3}, {{1, 2}, {2, 3}});
    topology::Space space2({2, 3, 4}, {{2, 3}, {3, 4}});
    std::function<double(double)> f = [](double x) { return x + 1; };
    std::function<double(double)> g = [](double x) { return x - 1; };
    topology::Homeomorphism h(f, g, space1, space2);

    if (!h.preservesClosedSets(f, space1, space2)) {
        throw std::runtime_error("preservesClosedSets failed for function f");
    }
    if (!h.preservesClosedSets(g, space2, space1)) {
        throw std::runtime_error("preservesClosedSets failed for function g");
    }

    std::cout << "preservesClosedSets passed\n";
}

void testNonHomeomorphicSpaces() {
    std::set<double> points1 = {1, 2, 3};
    std::set<std::set<double>> openSets1 = {{1}, {2}, {3}};
    topology::SpaceProperty space1(points1, openSets1);

    std::set<double> points2 = {4, 5, 6, 7};
    std::set<std::set<double>> openSets2 = {{4}, {5}, {6}, {7}};
    topology::SpaceProperty space2(points2, openSets2);

    std::function<double(double)> f = [](double x) { return x + 3; };
    std::function<double(double)> g = [](double x) { return x - 3; };
    topology::Homeomorphism h(f, g, space1, space2);

    if (h.preservesOpenSets(f, space1, space2)) {
        throw std::runtime_error("preservesOpenSets didn't fail for function f");
    }
    if (h.preservesOpenSets(g, space2, space1)) {
        throw std::runtime_error("preservesOpenSets didn't fail for function g");
    }

    if (h.preservesClosedSets(f, space1, space2)) {
        throw std::runtime_error("preservesClosedSets didn't fail for function f");
    }
    if (h.preservesClosedSets(g, space2, space1)) {
        throw std::runtime_error("preservesClosedSets didn't fail for function g");
    }

    std::cout << "Non-homeomorphic test passed\n";
}

int main() {
    try {
        testPreservesOpenSets();
        testPreservesClosedSets();
        testNonHomeomorphicSpaces();
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << '\n';
        return 1;
    }

    std::cout << "All tests passed\n";
    return 0;
}
