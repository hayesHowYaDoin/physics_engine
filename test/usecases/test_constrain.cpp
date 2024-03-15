#include <gtest/gtest.h>

#include "common/precision.hpp"
#include "physics_engine/domain/vector.hpp"
#include "physics_engine/simulation.hpp"
#include "physics_engine/usecases/constrain.hpp"

TEST(ConstrainTest, CenterInPeekingOut)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::usecases::Polygon2D<Length> constraint {
        {
            physics::domain::PositionVector2D(0.0_m, 0.0_m),
            physics::domain::PositionVector2D(1.0_m, 0.0_m),
            physics::domain::PositionVector2D(1.0_m, 1.0_m),
            physics::domain::PositionVector2D(0.0_m, 1.0_m)
        }
    };

    physics::usecases::Particle<physics::units::SI> particle {
        .mass {1.0_kg},
        .radius {0.25_m},
        .position {physics::domain::PositionVector2D(0.1_m, 0.05_m)},
        .velocity {physics::domain::VelocityVector2D(-1.0_mps, 1.0_mps)},
        .forces {physics::domain::ForceVector2D(0.0_N, -9.81_N)}
    };

    auto updatedParticle {physics::usecases::resolveConstraint(particle, constraint)};

    auto expectedPosition {physics::domain::PositionVector2D(0.25_m, 0.25_m)};
    EXPECT_TRUE(physics::domain::Vector2D::compare(updatedParticle.position, expectedPosition, physics::test::REQUIRED_PRECISION));

}

TEST(ConstrainTest, SingleEdgeReflection)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::usecases::Polygon2D<Length> constraint {
        {
            physics::domain::PositionVector2D(0.0_m, 0.0_m),
            physics::domain::PositionVector2D(10.0_m, 0.0_m),
            physics::domain::PositionVector2D(10.0_m, 10.0_m),
            physics::domain::PositionVector2D(0.0_m, 10.0_m)
        }
    };

    physics::usecases::Particle<physics::units::SI> particle {
        .mass {1.0_kg},
        .radius {0.25_m},
        .position {physics::domain::PositionVector2D(0.1_m, 5.0_m)},
        .velocity {physics::domain::VelocityVector2D(-1.0_mps, 1.0_mps)},
        .forces {physics::domain::ForceVector2D(0.0_N, -9.81_N)}
    };

    auto updatedParticle {physics::usecases::resolveConstraint(particle, constraint)};

    auto expectedVelocity {physics::domain::Vector2D::fromComponents(1.0_mps, 1.0_mps)};
    EXPECT_TRUE(physics::domain::Vector2D::compare(updatedParticle.velocity, expectedVelocity, physics::test::REQUIRED_PRECISION));
}

TEST(ConstrainTest, InBounds)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::usecases::Polygon2D<Length> constraint {
        {
            physics::domain::PositionVector2D(0.0_m, 0.0_m),
            physics::domain::PositionVector2D(1.0_m, 0.0_m),
            physics::domain::PositionVector2D(1.0_m, 1.0_m),
            physics::domain::PositionVector2D(0.0_m, 1.0_m)
        }
    };

    physics::usecases::Particle<physics::units::SI> particle {
        .mass {1.0_kg},
        .radius {0.25_m},
        .position {physics::domain::PositionVector2D(0.5_m, 0.5_m)},
        .velocity {physics::domain::VelocityVector2D(1.0_mps, -1.0_mps)},
        .forces {physics::domain::ForceVector2D(0.0_N, -9.81_N)}
    };

    auto updatedParticle {physics::usecases::resolveConstraint(particle, constraint)};

    auto expectedPosition {physics::domain::Vector2D::fromComponents(0.5_m, 0.5_m)};
    EXPECT_TRUE(physics::domain::Vector2D::compare(updatedParticle.position, expectedPosition, physics::test::REQUIRED_PRECISION));

    auto expectedVelocity {physics::domain::Vector2D::fromComponents(1.0_mps, -1.0_mps)};
    EXPECT_TRUE(physics::domain::Vector2D::compare(updatedParticle.velocity, expectedVelocity, physics::test::REQUIRED_PRECISION));
}
