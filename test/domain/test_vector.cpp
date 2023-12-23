#include "domain/concepts.hpp"
#include "domain/vector.hpp"
#include <units.h>

#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(VectorTest, ConstructFromComponents)
{
    using namespace units::literals;

    constexpr auto vector {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    auto angle {vector.getAngle<units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    constexpr auto magnitude {vector.getMagnitude<units::force::newtons<float>>()};
    EXPECT_NEAR(magnitude.to<float>(), 14.142'136f, REQUIRED_PRECISION);

    constexpr auto x {vector.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, ConstructFromAngleAndMagnitude)
{
    using namespace units::literals;

    auto vector {domain::Vector2D::fromPolar(45.0_deg, 10.0_N)};

    auto angle {vector.getAngle<units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    auto magnitude {vector.getMagnitude<units::force::newtons<float>>()};
    EXPECT_NEAR(magnitude.to<float>(), 10.0f, REQUIRED_PRECISION);

    auto x {vector.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 7.071'068f, REQUIRED_PRECISION);

    auto y {vector.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<double>(), 7.071'068f, REQUIRED_PRECISION);
}

TEST(VectorTest, AddVectors)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto vector2 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector3 {vector1 + vector2};

    constexpr auto x {vector3.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {vector3.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, SubtractVectors)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(20.0_N, 20.0_N)};
    constexpr auto vector2 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector3 {vector1 - vector2};

    constexpr auto x {vector3.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector3.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, MultiplyVectorByScalar)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector2 {vector1 * 2.0f};

    constexpr auto x {vector2.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {vector2.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, DivideVectorByScalar)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(20.0_N, 20.0_N)};

    constexpr auto vector2 {vector1 / 2.0f};

    constexpr auto x {vector2.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector2.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}
