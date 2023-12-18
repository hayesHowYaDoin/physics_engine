#include "domain/degrees.hpp"

#include <gtest/gtest.h>

TEST(AngleDegreesTest, AdditionOperator)
{
    domain::AngleDegrees angle1(45.0f);
    domain::AngleDegrees angle2(30.0f);
    domain::AngleDegrees result { angle1 + angle2 };

    EXPECT_FLOAT_EQ(result(), 75.0f);
}

TEST(AngleDegreesTest, ConstrainAdditionOperator)
{
    domain::AngleDegrees angle1(150.0f);
    domain::AngleDegrees angle2(45.0f);
    domain::AngleDegrees result { angle1 + angle2 };

    EXPECT_FLOAT_EQ(result(), -165.0f);
}

TEST(AngleDegreesTest, SubtractionOperator)
{
    domain::AngleDegrees angle1(90.0f);
    domain::AngleDegrees angle2(45.0f);
    domain::AngleDegrees result { angle1 - angle2 };

    EXPECT_FLOAT_EQ(result(), 45.0f);
}

TEST(AngleDegreesTest, ConstrainSubtractionOperator)
{
    domain::AngleDegrees angle1(30.0f);
    domain::AngleDegrees angle2(45.0f);
    domain::AngleDegrees result { angle1 - angle2 };

    EXPECT_FLOAT_EQ(result(), -15.0f);
}

TEST(AngleDegreesTest, Constrain)
{
    domain::AngleDegrees anglePositive(200.0f);
    EXPECT_FLOAT_EQ(anglePositive(), -160.0f);

    domain::AngleDegrees angleNegative(-200.0f);
    EXPECT_FLOAT_EQ(angleNegative(), 160.0f);
}

TEST(AngleDegreesTest, LiteralOperator)
{
    using namespace domain::literals;

    domain::AngleDegrees angle { 45.0_degrees };
    EXPECT_FLOAT_EQ(angle(), 45.0f);
}
