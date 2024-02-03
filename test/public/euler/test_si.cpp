#include <gtest/gtest.h>

// #include "physics_backend/euler/si.hpp"
#include "adapters/euler/si_p.hpp"


static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(EulerSI, buildParticle)
{
    auto particle {physics_backend::euler::si::Particle(1.0, 2.0, 3.0, 4.0, 5.0)};

    EXPECT_NEAR(particle.getMass(), 1.0, REQUIRED_PRECISION);
    EXPECT_NEAR(particle.getPosition().first, 2.0, REQUIRED_PRECISION);
    EXPECT_NEAR(particle.getPosition().second, 3.0, REQUIRED_PRECISION);
    EXPECT_NEAR(particle.getVelocity().first, 4.0, REQUIRED_PRECISION);
    EXPECT_NEAR(particle.getVelocity().second, 5.0, REQUIRED_PRECISION);
}