#include "homeomorphism.hpp"

int test() {
    // Define two pairs of topological spaces
    std::set<double> points1 = {1, 2, 3};
    std::set<double> points2 = {4, 5, 6};
    std::set<double> points3 = {1, 2, 3};
    std::set<double> points4 = {4, 5, 7};  // Not homeomorphic to points3

    topology::Space space1(points1);
    topology::Space space2(points2);
    topology::Space space3(points3);
    topology::Space space4(points4);

    // Define a function and its inverse
    std::function<double(double)> function = [](double x) { return x + 3; };
    std::function<double(double)> inverse = [](double y) { return y - 3; };

    // Test case 1: Homeomorphic spaces
    topology::Homeomorphism homeomorphism1(function, inverse, space1, space2);
    std::cout << "Test case 1: "
              << (homeomorphism1.isBijective(space1, space2)
                          && homeomorphism1.isContinuous(function, space1.getPoints())
                          && homeomorphism1.isContinuous(inverse, space2.getPoints())
                      ? "Homeomorphic"
                      : "Not homeomorphic")
              << std::endl;

    // Test case 2: Non-homeomorphic spaces
    topology::Homeomorphism homeomorphism2(function, inverse, space3, space4);
    std::cout << "Test case 2: "
              << (homeomorphism2.isBijective(space3, space4)
                          && homeomorphism2.isContinuous(function, space3.getPoints())
                          && homeomorphism2.isContinuous(inverse, space4.getPoints())
                      ? "Homeomorphic"
                      : "Not homeomorphic")
              << std::endl;

    // Test case 3: Homeomorphic spaces with different points
    std::set<double> points5 = {0, 1, 2};
    std::set<double> points6 = {3, 4, 5};
    topology::Space space5(points5);
    topology::Space space6(points6);
    std::function<double(double)> function2 = [](double x) { return x + 3; };
    std::function<double(double)> inverse2 = [](double y) { return y - 3; };
    topology::Homeomorphism homeomorphism3(function2, inverse2, space5, space6);
    std::cout << "Test case 3: "
              << (homeomorphism3.isBijective(space5, space6)
                          && homeomorphism3.isContinuous(function2, space5.getPoints())
                          && homeomorphism3.isContinuous(inverse2, space6.getPoints())
                      ? "Homeomorphic"
                      : "Not homeomorphic")
              << std::endl;

    // Add more test cases here...

    return 0;

}