#include "domain/concepts.hpp"
#include "domain/vector.hpp"
#include <units.h>

#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(VectorTest, ConstructFromAngleAndMagnitude)
{
    using namespace units::literals;

    auto vector {domain::Vector2D(45.0_deg, 10.0_N)};

    auto angle {vector.getAngle<units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    auto magnitude {vector.getMagnitude<units::force::newtons<float>>()};
    EXPECT_NEAR(magnitude.to<float>(), 10.0f, REQUIRED_PRECISION);

    auto components {vector.getComponents<units::force::newtons<float>>()};
    EXPECT_NEAR(components.x.to<float>(), 7.071'068f, REQUIRED_PRECISION);
    EXPECT_NEAR(components.y.to<double>(), 7.071'068f, REQUIRED_PRECISION);
}

TEST(VectorTest, ConstructFromComponents)
{
    using namespace units::literals;

    auto vector = domain::Vector2D(10.0_N, 10.0_N);

    auto angle {vector.getAngle<units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    auto magnitude {vector.getMagnitude<units::force::newtons<float>>()};
    EXPECT_NEAR(magnitude.to<float>(), 14.142'136f, REQUIRED_PRECISION);

    auto components {vector.getComponents<units::force::newtons<float>>()};
    EXPECT_NEAR(components.x.to<float>(), 10.0f, REQUIRED_PRECISION);
    EXPECT_NEAR(components.y.to<float>(), 10.0f, REQUIRED_PRECISION);
}
