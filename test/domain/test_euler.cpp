#include "domain/vector.hpp"
#include "domain/euler.hpp"
#include "core/concepts.hpp"
#include <units.h>

#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(EulerTest, NextPosition)
{
    using namespace units::literals;

    constexpr auto position {domain::Vector2D::fromComponents(10.0_m, 10.0_m)};
    constexpr auto velocity {domain::Vector2D::fromComponents(10.0_mps, 10.0_mps)};
    constexpr auto dt {1.0_s};

    constexpr auto nextPosition {domain::euler::nextPosition(position, velocity, dt)};

    EXPECT_NEAR(nextPosition.getX<units::length::meters<float>>().to<float>(), 20.0f, REQUIRED_PRECISION);
    EXPECT_NEAR(nextPosition.getY<units::length::meters<float>>().to<float>(), 20.0f, REQUIRED_PRECISION);
}
