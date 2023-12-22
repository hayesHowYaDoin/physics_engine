#include "domain/vector.hpp"
#include <units.h>

#include <iostream>

int main()
{
    using namespace units::literals;

    auto force = 10.0_N * units::cos(45.0_deg);
    std::cout << force << std::endl;

    return 0;
}