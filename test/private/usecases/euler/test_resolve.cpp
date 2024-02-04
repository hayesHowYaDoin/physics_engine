#include <units.h>
#include <gtest/gtest.h>

#include "physics_backend/units.hpp"
#include "usecases/euler/resolve.hpp"
#include "domain/constants.hpp"

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(EulerResolve, resolveMotion)
{
    using namespace units::literals;
    using Mass = units::mass::kilograms<double>;
    using Position = units::length::meters<double>;
    using Velocity = units::velocity::meters_per_second<double>;
    using Force = units::force::newtons<double>;
    using Time = units::time::seconds<double>;

    usecases::euler::EulerParticle<physics_backend::SI> const particle {
        .mass {1.0_kg},
        .position {domain::PositionVector2D(0.0_m, 10.0_m)},
        .velocity {domain::VelocityVector2D(0.0_mps, 0.0_mps)},
        .forces {domain::ForceVector2D(0.0_N, domain::constants::G * 1.0_kg)}
    };
    Time const timeStep {1};

    auto const result {usecases::euler::resolveMotion(particle, timeStep)};

    EXPECT_TRUE(domain::Vector2D::compare(
        result.position,
        domain::PositionVector2D(0.0_m, 0.19_m),
        REQUIRED_PRECISION));
    EXPECT_TRUE(domain::Vector2D::compare(
        result.velocity,
        domain::VelocityVector2D(0.0_mps, -9.81_mps),
        REQUIRED_PRECISION));
    EXPECT_NEAR(result.mass.to<float>(), 1.0f, REQUIRED_PRECISION);
}
