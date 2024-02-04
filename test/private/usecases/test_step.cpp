#include <cstdint>
#include <vector>

#include <units.h>
#include <gtest/gtest.h>

#include "usecases/euler/resolve.hpp"
#include "usecases/step.hpp"
#include "domain/constants.hpp"


static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(Step, vector)
{
    std::vector<uint16_t> objects {0, 1, 2};

    auto resolveMotion {[](uint16_t object) -> uint16_t {
        return object + 1;
    }};

    auto results {usecases::step(objects, resolveMotion)};
    EXPECT_TRUE(results.size() == 3);

    EXPECT_TRUE(results[0] == 1);
    EXPECT_TRUE(results[1] == 2);
    EXPECT_TRUE(results[2] == 3);
}

TEST(Step, array)
{
    std::array<uint16_t, 3> objects {0, 1, 2};

    auto resolveMotion {[](uint16_t object) -> uint16_t {
        return object + 1;
    }};

    auto results {usecases::step(objects, resolveMotion)};
    EXPECT_TRUE(results.size() == 3);

    EXPECT_TRUE(results[0] == 1);
    EXPECT_TRUE(results[1] == 2);
    EXPECT_TRUE(results[2] == 3);
}

TEST(Step, variadic)
{
    std::array<uint16_t, 3> objects {0, 1, 2};

    auto first {[](uint16_t object) -> uint16_t {
        return object + 1;
    }};
    auto second {[](uint16_t object) -> uint16_t {
        return object * 2;
    }};
    auto third {[](uint16_t object) -> uint16_t {
        return object + 2;
    }};

    auto results {usecases::step(objects, first, second, third)};
    EXPECT_TRUE(results.size() == 3);

    EXPECT_TRUE(results[0] == 4);
    EXPECT_TRUE(results[1] == 6);
    EXPECT_TRUE(results[2] == 8);
}
