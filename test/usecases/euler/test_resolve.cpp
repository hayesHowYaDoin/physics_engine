#include "usecases/euler/resolve.hpp"
#include "domain/constants.hpp"

#include <units.h>
#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(EulerResolve, resolveMotion)
{
    using namespace units::literals;

    usecases::EulerParticle const particle {
        domain::PositionVector2D(0.0_m, 10.0_m),
        domain::VelocityVector2D(0.0_mps, 0.0_mps),
        1.0_kg,
        {domain::ForceVector2D(0.0_N, domain::constants::G * 1.0_kg)}
    };
    auto const forces {std::vector<domain::ForceVector2D<units::force::newtons<double>>> {
        domain::ForceVector2D(0.0_N, domain::constants::G * particle.mass)
    }};
    auto const timeStep {units::time::seconds<double> {1}};

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

TEST(EulerResolve, step)
{
    using namespace units::literals;

    auto const particles {std::vector<usecases::EulerParticle> {
        usecases::EulerParticle {
            domain::PositionVector2D(0.0_m, 10.0_m),
            domain::VelocityVector2D(0.0_mps, 0.0_mps),
            1.0_kg,
            {domain::ForceVector2D(0.0_N, domain::constants::G * 1.0_kg)}
        }
    }};
    auto const timeStep {units::time::seconds<double> {1}};
    auto const resolveMotion {[&timeStep](usecases::EulerParticle const& particle) {
        return usecases::euler::resolveMotion(particle, timeStep);
    }};

    auto const results {usecases::euler::step(particles, timeStep, resolveMotion)};
    EXPECT_TRUE(results.size() == 1);

    auto const result {results[0]};

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