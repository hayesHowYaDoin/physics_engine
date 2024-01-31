#include "domain/vector.hpp"
#include "domain/motion.hpp"
#include "core/concepts.hpp"
#include <units.h>

#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(MotionTest, NextPosition)
{
    using namespace domain;
    using namespace units::literals;

    constexpr auto position {Vector2D::fromComponents(10.0_m, 10.0_m)};
    constexpr auto velocity {Vector2D::fromComponents(10.0_mps, 10.0_mps)};
    constexpr auto dt {1.0_s};

    constexpr auto nextPosition {motion::nextPosition(position, velocity, dt)};

    EXPECT_NEAR(
        nextPosition.getX<units::length::meters<float>>().to<float>(),
        20.0f,
        REQUIRED_PRECISION);

    EXPECT_NEAR(
        nextPosition.getY<units::length::meters<float>>().to<float>(),
        20.0f,
        REQUIRED_PRECISION);
}

TEST(MotionTest, NextVelocity)
{
    using namespace domain;
    using namespace units::literals;
    using namespace units::velocity;

    constexpr auto velocity {Vector2D::fromComponents(10.0_mps, 10.0_mps)};
    constexpr auto acceleration {Vector2D::fromComponents(10.0_mps_sq, 10.0_mps_sq)};
    constexpr auto dt {1.0_s};

    constexpr auto next {motion::nextVelocity(velocity, acceleration, dt)};

    constexpr auto x {next.getX<meters_per_second<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {next.getY<meters_per_second<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}

TEST(MotionTest, Acceleration)
{
    using namespace domain;
    using namespace units::literals;
    using mpssUnits = units::acceleration::meters_per_second_squared<double>;

    constexpr auto force {Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto mass {10.0_kg};

    constexpr auto acceleration {motion::acceleration(force, mass)};
    constexpr auto x {acceleration.getX<mpssUnits>()};
    EXPECT_NEAR(x.to<float>(), 1.0f, REQUIRED_PRECISION);

    constexpr auto y {acceleration.getY<mpssUnits>()};
    EXPECT_NEAR(y.to<float>(), 1.0f, REQUIRED_PRECISION);
}

TEST(MotionTest, AccelerationMassZero)
{
    using namespace domain;
    using namespace units::literals;
    using mpssUnits = units::acceleration::meters_per_second_squared<double>;

    constexpr auto force {Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto mass {0.0_kg};

    EXPECT_THROW(
        motion::acceleration(force, mass),
        std::invalid_argument);
}

TEST(MotionTest, AccelerationMassNegative)
{
    using namespace domain;
    using namespace units::literals;
    using mpssUnits = units::acceleration::meters_per_second_squared<double>;

    constexpr auto force {Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto mass {-10.0_kg};

    EXPECT_THROW(
        motion::acceleration(force, mass),
        std::invalid_argument);
}
