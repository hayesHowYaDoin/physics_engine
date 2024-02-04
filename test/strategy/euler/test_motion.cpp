#include <gtest/gtest.h>

#include "physics_backend/strategy/euler/particle.hpp"
#include "physics_backend/strategy/euler/motion.hpp"
#include "physics_backend/units.hpp"

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(EulerResolve, resolveMotion)
{
    using namespace physics::units::literals;
    using Mass = physics::units::mass::kilograms<double>;
    using Position = physics::units::length::meters<double>;
    using Velocity = physics::units::velocity::meters_per_second<double>;
    using Force = physics::units::force::newtons<double>;
    using Time = physics::units::time::seconds<double>;

    physics::euler::Particle<physics::units::SI> const particle {
        .mass {1.0_kg},
        .position {physics::units::PositionVector2D(0.0_m, 10.0_m)},
        .velocity {physics::units::VelocityVector2D(0.0_mps, 0.0_mps)},
        .forces {physics::units::ForceVector2D(0.0_N, -9.81_N)}
    };
    Time const timeStep {1};

    auto const result {physics::euler::resolveMotion(particle, timeStep)};

    EXPECT_TRUE(physics::units::Vector2D::compare(
        result.position,
        physics::units::PositionVector2D(0.0_m, 0.19_m),
        REQUIRED_PRECISION));
    EXPECT_TRUE(physics::units::Vector2D::compare(
        result.velocity,
        physics::units::VelocityVector2D(0.0_mps, -9.81_mps),
        REQUIRED_PRECISION));
    EXPECT_NEAR(result.mass.to<float>(), 1.0f, REQUIRED_PRECISION);
}
