#include <gtest/gtest.h>

#include "common/precision.hpp"
#include "physics_backend/domain/vector.hpp"
#include "physics_backend/euler.hpp"
#include "physics_backend/usecases/constrain.hpp"

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

    physics::euler::Particle<physics::units::SI> particle {
        .mass {1.0_kg},
        .radius {0.25_m},
        .position {physics::domain::PositionVector2D(0.1_m, 0.05_m)},
        .velocity {physics::domain::VelocityVector2D(0.0_mps, 0.0_mps)},
        .forces {physics::domain::ForceVector2D(0.0_N, -9.81_N)}
    };

    auto updatedParticle {physics::usecases::resolveConstraint(particle, constraint)};
    auto expectedPosition {physics::domain::PositionVector2D(0.25_m, 0.25_m)};

    std::cout << "Updated particle position: " << updatedParticle.position.repr() << std::endl;
    std::cout << "Expected position: " << expectedPosition.repr() << std::endl;

    EXPECT_TRUE(physics::domain::Vector2D::compare(updatedParticle.position, expectedPosition, physics::test::REQUIRED_PRECISION));
}

TEST(ConstrainTest, Tunneling)
{
    // TODO: Solve the tunneling problem.

    // using namespace physics::units::literals;
    // using Length = physics::units::SI::Length;

    // physics::usecases::Polygon2D<Length> constraint {
    //     {
    //         physics::domain::PositionVector2D(0.0_m, 0.0_m),
    //         physics::domain::PositionVector2D(1.0_m, 0.0_m),
    //         physics::domain::PositionVector2D(1.0_m, 1.0_m),
    //         physics::domain::PositionVector2D(0.0_m, 1.0_m)
    //     }
    // };

    // physics::euler::Particle<physics::units::SI> particle {
    //     .mass {1.0_kg},
    //     .radius {0.25_m},
    //     .position {physics::domain::PositionVector2D(-1.0_m, -1.0_m)},
    //     .velocity {physics::domain::VelocityVector2D(0.0_mps, 0.0_mps)},
    //     .forces {physics::domain::ForceVector2D(0.0_N, -9.81_N)}
    // };

    // auto updatedParticle {physics::usecases::resolveConstraint(particle, constraint)};
    // auto expectedPosition {physics::domain::PositionVector2D(0.5_m, 0.5_m)};

    // std::cout << "Updated particle position: " << updatedParticle.position.repr() << std::endl;
    // std::cout << "Expected position: " << expectedPosition.repr() << std::endl;

    // EXPECT_TRUE(physics::domain::Vector2D::compare(updatedParticle.position, expectedPosition, physics::test::REQUIRED_PRECISION));
}