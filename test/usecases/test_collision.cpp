#include <gtest/gtest.h>

#include "common/precision.hpp"
#include "physics_engine/units.hpp"
#include "physics_engine/domain/vector.hpp"
#include "physics_engine/usecases/collision.hpp"
#include "physics_engine/usecases/particle.hpp"

TEST(CollisionTest, ResolveIdentical)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;
    using Velocity = physics::units::SI::Velocity;

    auto particle1 {physics::usecases::Particle<physics::units::SI>{
        .mass = 1.0_kg,
        .radius = 1.0_m,
        .position = physics::domain::PositionVector2D{0.0_m, 0.0_m},
        .velocity = physics::domain::VelocityVector2D{1.0_mps, -1.0_mps},
        .forces = {}
    }};
    auto particle2 {physics::usecases::Particle<physics::units::SI>{
        .mass = 1.0_kg,
        .radius = 1.0_m,
        .position = physics::domain::PositionVector2D{1.0_m, 0.0_m},
        .velocity = physics::domain::VelocityVector2D{-1.0_mps, 1.0_mps},
        .forces = {}
    }};

    std::vector<physics::usecases::Particle<physics::units::SI>> particles {particle1, particle2};
    physics::usecases::resolveCollisions(particles);

    EXPECT_NEAR(particles.at(0).position.getX<Length>().to<float>(), -0.5f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(0).position.getY<Length>().to<float>(), 0.0f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).position.getX<Length>().to<float>(), 1.5f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).position.getY<Length>().to<float>(), 0.0f, physics::test::REQUIRED_PRECISION);

    EXPECT_NEAR(particles.at(0).velocity.getX<Velocity>().to<float>(), -1.0f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(0).velocity.getY<Velocity>().to<float>(), -1.0f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).velocity.getX<Velocity>().to<float>(), 1.0f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).velocity.getY<Velocity>().to<float>(), 1.0f, physics::test::REQUIRED_PRECISION);
}

TEST(CollisionTest, ResolveMassDifference)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;
    using Velocity = physics::units::SI::Velocity;
    using Angle = physics::units::angle::degrees<float>;

    auto particle1 {physics::usecases::Particle<physics::units::SI>{
        .mass = 1.0_kg,
        .radius = 1.6_m,
        .position = physics::domain::PositionVector2D{7.0_m, 9.5_m},
        .velocity = physics::domain::VelocityVector2D{2.0_mps, -2.0_mps},
        .forces = {}
    }};
    auto particle2 {physics::usecases::Particle<physics::units::SI>{
        .mass = 2.0_kg,
        .radius = 3.0_m,
        .position = physics::domain::PositionVector2D{10.5_m, 8.5_m},
        .velocity = physics::domain::VelocityVector2D{-2.0_mps, 2.0_mps},
        .forces = {}
    }};

    std::vector<physics::usecases::Particle<physics::units::SI>> particles {particle1, particle2};
    physics::usecases::resolveCollisions(particles);

    EXPECT_NEAR(particles.at(0).position.getX<Length>().to<float>(), 6.5385f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(0).position.getY<Length>().to<float>(), 9.6319f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).position.getX<Length>().to<float>(), 10.9615f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).position.getY<Length>().to<float>(), 8.3681f, physics::test::REQUIRED_PRECISION);

    EXPECT_NEAR(particles.at(0).velocity.getX<Velocity>().to<float>(), -4.3396f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(0).velocity.getY<Velocity>().to<float>(), -0.1887f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).velocity.getX<Velocity>().to<float>(), 1.1698f, physics::test::REQUIRED_PRECISION);
    EXPECT_NEAR(particles.at(1).velocity.getY<Velocity>().to<float>(), 1.0943f, physics::test::REQUIRED_PRECISION);
}
