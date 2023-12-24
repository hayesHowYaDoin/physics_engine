#include "usecases/euler/resolve.hpp"
#include "domain/constants.hpp"

#include <units.h>
#include <gtest/gtest.h>

TEST(EulerResolve, resolveMotion)
{
    using namespace units::literals;

    usecases::EulerParticle const particle {
        domain::PositionVector2D(0.0_m, 0.0_m),
        domain::VelocityVector2D(0.0_mps, 0.0_mps),
        1.0_kg
    };
    auto const forces {std::vector<domain::ForceVector2D<units::force::newtons<double>>> {
        domain::ForceVector2D(0.0_N, domain::constants::G * particle.mass)
    }};
    auto const timeStep {units::time::seconds<double> {1}};

    auto const result {usecases::resolveMotion(particle, forces, timeStep)};

    // EXPECT_EQ(result.position, PositionVector2D<units::length::meter<double>> {0, 0});
    // EXPECT_EQ(result.velocity, VelocityVector2D<units::velocity::meters_per_second<double>> {0, 0});
    // EXPECT_EQ(result.mass, units::mass::kilogram<double> {1});
}