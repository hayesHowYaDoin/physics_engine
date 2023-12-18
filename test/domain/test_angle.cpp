#include "domain/angle.hpp"

#include <gtest/gtest.h>

namespace
{
    constexpr float REQUIRED_PRECISION = 0.001f;
}

TEST(AngleTest, FromDegrees)
{
    domain::Angle angle = domain::Angle::fromDegrees(45.0f);
    EXPECT_NEAR(angle.inDegrees(), 45.0f, REQUIRED_PRECISION);
    EXPECT_NEAR(angle.inRadians(), 0.785398f, REQUIRED_PRECISION);
}

TEST(AngleTest, FromRadians)
{
    domain::Angle angle = domain::Angle::fromRadians(0.785398f);
    EXPECT_NEAR(angle.inDegrees(), 45.0f, REQUIRED_PRECISION);
    EXPECT_NEAR(angle.inRadians(), 0.785398f, REQUIRED_PRECISION);
}

TEST(AngleTest, Addition)
{
    domain::Angle angle1 = domain::Angle::fromDegrees(30.0f);
    domain::Angle angle2 = domain::Angle::fromDegrees(60.0f);
    domain::Angle result = angle1 + angle2;
    EXPECT_NEAR(result.inDegrees(), 90.0f, REQUIRED_PRECISION);
}

TEST(AngleTest, LiteralAddition)
{
    using namespace domain::literals;

    domain::Angle result = 0.523599_rad + 60.0_deg;
    EXPECT_NEAR(result.inDegrees(), 90.0f, REQUIRED_PRECISION);
}

TEST(AngleTest, Subtraction)
{
    domain::Angle angle1 = domain::Angle::fromDegrees(90.0f);
    domain::Angle angle2 = domain::Angle::fromDegrees(45.0f);
    domain::Angle result = angle1 - angle2;
    EXPECT_NEAR(result.inDegrees(), 45.0f, REQUIRED_PRECISION);
}

TEST(AngleTest, LiteralSubtraction)
{
    using namespace domain::literals;
    
    domain::Angle result = 1.5708_rad - 45.0_deg;
    EXPECT_NEAR(result.inDegrees(), 45.0f, REQUIRED_PRECISION);
}

TEST(AngleTest, Constrain)
{
    domain::Angle angle = domain::Angle::fromDegrees(-270.0f);
    EXPECT_NEAR(angle.inDegrees(), 90.0f, REQUIRED_PRECISION);
}

TEST(AngleTest, EdgeConstrain)
{
    domain::Angle angle = domain::Angle::fromDegrees(540.0f);
    EXPECT_NEAR(angle.inDegrees(), 180.0f, REQUIRED_PRECISION);

    angle = domain::Angle::fromDegrees(-540.0f);
    EXPECT_NEAR(angle.inDegrees(), 180.0f, REQUIRED_PRECISION);
}

TEST(AngleTest, Equality)
{
    domain::Angle angle1 = domain::Angle::fromDegrees(45.0f);
    domain::Angle angle2 = domain::Angle::fromRadians(0.785398f);

    EXPECT_TRUE(angle1 == angle2);
}

TEST(AngleTest, EdgeEquality)
{
    domain::Angle angle1 = domain::Angle::fromDegrees(180.0f);
    domain::Angle angle2 = domain::Angle::fromDegrees(-180.0f);

    EXPECT_TRUE(angle1 == angle2);
}

TEST(AngleTest, DegreesLiteral)
{
    using namespace domain::literals;

    domain::Angle angle = 45.0_deg;
    EXPECT_NEAR(angle.inDegrees(), 45.0f, REQUIRED_PRECISION);
}

TEST(AngleTest, RadiansLiteral)
{
    using namespace domain::literals;
    
    domain::Angle angle = 0.785398_rad; // equivalent to 45 degrees
    EXPECT_NEAR(angle.inDegrees(), 45.0f, REQUIRED_PRECISION);
}

TEST(AngleTest, Cos)
{
    domain::Angle angle = domain::Angle::fromDegrees(60.0f);
    float result = domain::cos(angle);
    EXPECT_NEAR(result, 0.5f, REQUIRED_PRECISION);
}

TEST(AngleTest, Sin)
{
    domain::Angle angle = domain::Angle::fromDegrees(30.0f);
    float result = domain::sin(angle);
    EXPECT_NEAR(result, 0.5f, REQUIRED_PRECISION);
}

TEST(AngleTest, Tan)
{
    domain::Angle angle = domain::Angle::fromDegrees(45.0f);
    float result = domain::tan(angle);
    EXPECT_NEAR(result, 1.0f, REQUIRED_PRECISION);
}

