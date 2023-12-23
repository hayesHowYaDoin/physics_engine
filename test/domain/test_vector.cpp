#include "domain/concepts.hpp"
#include "domain/vector.hpp"
#include <units.h>

#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(VectorTest, ConstructFromAngleAndMagnitude)
{
    using namespace units::literals;

    constexpr auto vector {domain::Vector2D(45.0_deg, 10.0_N)};

    constexpr auto angle {vector.getAngle<units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    constexpr auto magnitude {vector.getMagnitude<units::force::newtons<float>>()};
    EXPECT_NEAR(magnitude.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto components {vector.getComponents<units::force::newtons<float>>()};
    EXPECT_NEAR(components.x.to<float>(), 7.071'068f, REQUIRED_PRECISION);
    EXPECT_NEAR(components.y.to<double>(), 7.071'068f, REQUIRED_PRECISION);
}

TEST(VectorTest, ConstructFromComponents)
{
    using namespace units::literals;

    constexpr auto vector = domain::Vector2D(10.0_N, 10.0_N);

    constexpr auto angle {vector.getAngle<units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    constexpr auto magnitude {vector.getMagnitude<units::force::newtons<float>>()};
    EXPECT_NEAR(magnitude.to<float>(), 14.142'136f, REQUIRED_PRECISION);

    constexpr auto components {vector.getComponents<units::force::newtons<float>>()};
    EXPECT_NEAR(components.x.to<float>(), 10.0f, REQUIRED_PRECISION);
    EXPECT_NEAR(components.y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, CopyConstructor)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D(10.0_N, 10.0_N)};
    constexpr auto vector2 {domain::Vector2D(vector1)};

    constexpr auto angle1 {vector1.getAngle<units::angle::radians<float>>()};
    constexpr auto angle2 {vector2.getAngle<units::angle::radians<float>>()};
    EXPECT_NEAR(angle1.to<float>(), angle2.to<float>(), REQUIRED_PRECISION);

    constexpr auto magnitude1 {vector1.getMagnitude<units::force::pounds<float>>()};
    constexpr auto magnitude2 {vector2.getMagnitude<units::force::pounds<float>>()};
    EXPECT_NEAR(magnitude1.to<float>(), magnitude2.to<float>(), REQUIRED_PRECISION);

    constexpr auto components1 {vector1.getComponents<units::force::pounds<float>>()};
    constexpr auto components2 {vector2.getComponents<units::force::pounds<float>>()};
    EXPECT_NEAR(components1.x.to<float>(), components2.x.to<float>(), REQUIRED_PRECISION);
    EXPECT_NEAR(components1.y.to<float>(), components2.y.to<float>(), REQUIRED_PRECISION);
}
