#include <gtest/gtest.h>

#include "homeomorphism.hpp"

using namespace topology;

TEST(HomeomorphismTest, HomeomorphicSpaces) {
    std::set<double> points1 = {1, 2, 3};
    std::set<std::set<double>> openSets1 = {{1}, {2}, {3}};
    topology::SpaceProperty space1(points1, openSets1);

    std::set<double> points2 = {4, 5, 6};
    std::set<std::set<double>> openSets2 = {{4}, {5}, {6}};
    topology::SpaceProperty space2(points2, openSets2);

    std::function<double(double)> function = [](double x) { return x + 3; };
    std::function<double(double)> inverse = [](double x) { return x - 3; };

    Homeomorphism homeomorphism(function, inverse, space1, space2);
    EXPECT_TRUE(homeomorphism.isValid());
}

TEST(HomeomorphismTest, NonHomeomorphicSpaces) {
    std::set<double> points1 = {1, 2, 3};
    std::set<std::set<double>> openSets1 = {{1}, {2}, {3}};
    topology::SpaceProperty space1(points1, openSets1);

    std::set<double> points2 = {4, 5, 7};
    std::set<std::set<double>> openSets2 = {{4}, {5}, {7}};
    topology::SpaceProperty space2(points2, openSets2);

    std::function<double(double)> function = [](double x) { return x + 3; };
    std::function<double(double)> inverse = [](double x) { return x - 3; };

    Homeomorphism homeomorphism(function, inverse, space1, space2);
    EXPECT_FALSE(homeomorphism.isValid());
}
