#include <gtest/gtest.h>

#include "physics_backend/domain/motion.hpp"

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(MotionTest, NextPosition)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    constexpr auto position {physics::domain::Vector2D::fromComponents(10.0_m, 10.0_m)};
    constexpr auto velocity {physics::domain::Vector2D::fromComponents(10.0_mps, 10.0_mps)};
    constexpr auto dt {1.0_s};

    constexpr auto nextPosition {physics::domain::nextPosition(position, velocity, dt)};

    EXPECT_NEAR(
        nextPosition.getX<length::meters<float>>().to<float>(),
        20.0f,
        REQUIRED_PRECISION);

    EXPECT_NEAR(
        nextPosition.getY<length::meters<float>>().to<float>(),
        20.0f,
        REQUIRED_PRECISION);
}

TEST(MotionTest, NextVelocity)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    constexpr auto velocity {physics::domain::Vector2D::fromComponents(10.0_mps, 10.0_mps)};
    constexpr auto acceleration {physics::domain::Vector2D::fromComponents(10.0_mps_sq, 10.0_mps_sq)};
    constexpr auto dt {1.0_s};

    constexpr auto next {physics::domain::nextVelocity(velocity, acceleration, dt)};

    constexpr auto x {next.getX<meters_per_second<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {next.getY<meters_per_second<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}

TEST(MotionTest, Acceleration)
{
    using namespace physics::units;
    using namespace physics::units::literals;
    using Acceleration = acceleration::meters_per_second_squared<double>;

    constexpr auto force {physics::domain::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto mass {10.0_kg};

    constexpr auto acceleration {physics::domain::acceleration(force, mass)};
    constexpr auto x {acceleration.getX<Acceleration>()};
    EXPECT_NEAR(x.to<float>(), 1.0f, REQUIRED_PRECISION);

    constexpr auto y {acceleration.getY<Acceleration>()};
    EXPECT_NEAR(y.to<float>(), 1.0f, REQUIRED_PRECISION);
}

TEST(MotionTest, AccelerationMassZero)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    constexpr auto force {physics::domain::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto mass {0.0_kg};

    EXPECT_THROW(
        static_cast<void>(physics::domain::acceleration(force, mass)),
        std::invalid_argument);
}

TEST(MotionTest, AccelerationMassNegative)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    constexpr auto force {physics::domain::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto mass {-10.0_kg};

    EXPECT_THROW(
        static_cast<void>(physics::domain::acceleration(force, mass)),
        std::invalid_argument);
}
