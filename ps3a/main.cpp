#include <iostream>
#include "Universe.hpp"
#include "CelestialBody.hpp"

int main() {
    testCelestialBody();
    testIOOperators();
    testUniverse();
    testUniverseIndexing();
    testEmptyUniverse();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
