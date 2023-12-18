#include "domain/core/vector.hpp"

#include <gtest/gtest.h>

namespace
{
    constexpr float REQUIRED_PRECISION = 0.001f;
}

TEST(Vector2DTest, MagnitudeAndAngle)
{
    using namespace domain::literals;

    domain::Vector2D vector(5.0f, 45.0_deg);

    EXPECT_NEAR(vector.getMagnitude(), 5.0f, REQUIRED_PRECISION);
    EXPECT_EQ(vector.getAngle(), 45.0_deg);
}

TEST(Vector2DTest, Addition)
{
    using namespace domain::literals;

    domain::Vector2D vector1(3.0f, 30.0_deg);
    domain::Vector2D vector2(4.0f, 60.0_deg);

    domain::Vector2D result { vector1 + vector2 };

    EXPECT_NEAR(result.getMagnitude(), 6.76643f, REQUIRED_PRECISION);
    EXPECT_EQ(result.getAngle(), 47.1921_deg);
}

TEST(Vector2DTest, Subtraction)
{
    using namespace domain::literals;

    domain::Vector2D vector1(5.0f, 45.0_deg);
    domain::Vector2D vector2(2.0f, 30.0_deg);

    domain::Vector2D result { vector1 - vector2 };

    EXPECT_NEAR(result.getMagnitude(), 3.1115f, REQUIRED_PRECISION);
    EXPECT_EQ(result.getAngle(), 54.5764_deg);
}

TEST(Vector2DTest, ScalarMultiplication)
{
    using namespace domain::literals;

    domain::Vector2D vector(2.0f, 60.0_deg);
    float scalar = 3.0f;

    domain::Vector2D result { vector * scalar };

    EXPECT_NEAR(result.getMagnitude(), 6.0f, REQUIRED_PRECISION);
    EXPECT_EQ(result.getAngle(), 60.0_deg);
}

TEST(Vector2DTest, ScalarDivision)
{
    using namespace domain::literals;

    domain::Vector2D vector(6.0f, 90.0_deg);
    float scalar = 2.0f;

    domain::Vector2D result { vector / scalar };

    EXPECT_NEAR(result.getMagnitude(), 3.0f, REQUIRED_PRECISION);
    EXPECT_EQ(result.getAngle(), 90.0_deg);
}

TEST(Vector2DTest, Components)
{
    using namespace domain::literals;

    domain::Vector2D vector(5.0f, 45.0_deg);

    auto [x, y] = domain::Vector2D::getComponents(vector);

    EXPECT_NEAR(x, 3.53553390593f, REQUIRED_PRECISION);
    EXPECT_NEAR(y, 3.53553390593f, REQUIRED_PRECISION);
}
