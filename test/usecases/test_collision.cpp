#include <gtest/gtest.h>

#include "common/precision.hpp"
#include "physics_backend/units.hpp"
#include "physics_backend/domain/vector.hpp"
#include "physics_backend/usecases/collision.hpp"
#include "physics_backend/usecases/euler/particle.hpp"

TEST(CollisionTest, ResolveIdentical)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;
    using Velocity = physics::units::SI::Velocity;

    auto particle1 {physics::euler::Particle<physics::units::SI>{
        .mass = 1.0_kg,
        .radius = 1.0_m,
        .position = physics::domain::PositionVector2D{0.0_m, 0.0_m},
        .velocity = physics::domain::VelocityVector2D{1.0_mps, -1.0_mps},
        .forces = {}
    }};
    auto particle2 {physics::euler::Particle<physics::units::SI>{
        .mass = 1.0_kg,
        .radius = 1.0_m,
        .position = physics::domain::PositionVector2D{1.0_m, 0.0_m},
        .velocity = physics::domain::VelocityVector2D{-1.0_mps, 1.0_mps},
        .forces = {}
    }};

    std::vector<physics::euler::Particle<physics::units::SI>> particles {particle1, particle2};
    physics::usecases::resolveCollisions(particles);

    EXPECT_NEAR(particles.at(0).position.getX<Length>().to<float>(), -0.5f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(0).position.getY<Length>().to<float>(), 0.0f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).position.getX<Length>().to<float>(), 1.5f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).position.getY<Length>().to<float>(), 0.0f, physics::test::REQUIRED_PRECISION);

    // EXPECT_NEAR(particles.at(0).velocity.getX<Velocity>().to<float>(), -1.0f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(0).velocity.getY<Velocity>().to<float>(), -1.0f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(1).velocity.getX<Velocity>().to<float>(), 1.0f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(1).velocity.getX<Velocity>().to<float>(), 1.0f, physics::test::REQUIRED_PRECISION);
}

TEST(CollisionTest, ResolveMassDifference)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;
    using Velocity = physics::units::SI::Velocity;

    auto particle1 {physics::euler::Particle<physics::units::SI>{
        .mass = 4.0_kg,
        .radius = 1.0_m,
        .position = physics::domain::PositionVector2D{0.0_m, 0.0_m},
        .velocity = physics::domain::VelocityVector2D{1.0_mps, -1.0_mps},
        .forces = {}
    }};
    auto particle2 {physics::euler::Particle<physics::units::SI>{
        .mass = 1.0_kg,
        .radius = 1.0_m,
        .position = physics::domain::PositionVector2D{1.0_m, 0.0_m},
        .velocity = physics::domain::VelocityVector2D{-1.0_mps, 1.0_mps},
        .forces = {}
    }};

    std::vector<physics::euler::Particle<physics::units::SI>> particles {particle1, particle2};
    physics::usecases::resolveCollisions(particles);

    // EXPECT_NEAR(particles.at(0).position.getX<Length>().to<float>(), -0.5f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(0).position.getX<Length>().to<float>(), 0.0f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(1).position.getX<Length>().to<float>(), 1.5f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(1).position.getX<Length>().to<float>(), 0.0f, physics::test::REQUIRED_PRECISION);

    // EXPECT_NEAR(particles.at(0).velocity.getX<Velocity>().to<float>(), -1.0f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(0).velocity.getY<Velocity>().to<float>(), -1.0f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(1).velocity.getX<Velocity>().to<float>(), 1.0f, physics::test::REQUIRED_PRECISION);
    // EXPECT_NEAR(particles.at(1).velocity.getX<Velocity>().to<float>(), 1.0f, physics::test::REQUIRED_PRECISION);
}
