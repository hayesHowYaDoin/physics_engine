#include "domain/vector.hpp"
#include <units.h>

#include <iostream>

int temp_func_for_test()
{
    using namespace units::literals;

    auto force = 10.0_N * units::cos(45.0_deg);
    std::cout << force << std::endl;

    return 0;
}