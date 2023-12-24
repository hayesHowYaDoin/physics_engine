#include "domain/vector.hpp"
#include "domain/euler.hpp"
#include "core/concepts.hpp"
#include <units.h>

#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(EulerTest, NextPosition)
{
    using namespace units::literals;
    using namespace domain;

    constexpr auto position {Vector2D::fromComponents(10.0_m, 10.0_m)};
    constexpr auto velocity {Vector2D::fromComponents(10.0_mps, 10.0_mps)};
    constexpr auto dt {1.0_s};

    constexpr auto nextPosition {euler::nextPosition(position, velocity, dt)};

    EXPECT_NEAR(
        nextPosition.getX<units::length::meters<float>>().to<float>(),
        20.0f,
        REQUIRED_PRECISION);

    EXPECT_NEAR(
        nextPosition.getY<units::length::meters<float>>().to<float>(),
        20.0f,
        REQUIRED_PRECISION);
}

TEST(EulerTest, NextVelocity)
{
    using namespace units::literals;
    using namespace units::velocity;
    using namespace domain;

    constexpr auto velocity {Vector2D::fromComponents(10.0_mps, 10.0_mps)};
    constexpr auto acceleration {Vector2D::fromComponents(10.0_mps_sq, 10.0_mps_sq)};
    constexpr auto dt {1.0_s};

    constexpr auto nextVelocity {euler::nextVelocity(velocity, acceleration, dt)};

    constexpr auto x {nextVelocity.getX<meters_per_second<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {nextVelocity.getY<meters_per_second<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}
