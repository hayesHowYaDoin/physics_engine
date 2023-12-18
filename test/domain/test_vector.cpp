#include "domain/vector.hpp"

#include <gtest/gtest.h>

namespace
{
    constexpr float REQUIRED_PRECISION = 0.001f;
}

TEST(PhysicsVectorTest, MagnitudeAndAngle)
{
    using namespace domain::literals;

    domain::PhysicsVector vector(5.0f, 45.0_deg);

    EXPECT_NEAR(vector.getMagnitude(), 5.0f, REQUIRED_PRECISION);
    EXPECT_EQ(vector.getAngle(), 45.0_deg);
}

TEST(PhysicsVectorTest, Addition)
{
    using namespace domain::literals;

    domain::PhysicsVector vector1(3.0f, 30.0_deg);
    domain::PhysicsVector vector2(4.0f, 60.0_deg);

    domain::PhysicsVector result { vector1 + vector2 };

    EXPECT_NEAR(result.getMagnitude(), 6.76643f, REQUIRED_PRECISION);
    EXPECT_EQ(result.getAngle(), 47.1921_deg);
}

TEST(PhysicsVectorTest, Subtraction)
{
    using namespace domain::literals;

    domain::PhysicsVector vector1(5.0f, 45.0_deg);
    domain::PhysicsVector vector2(2.0f, 30.0_deg);

    domain::PhysicsVector result { vector1 - vector2 };

    EXPECT_NEAR(result.getMagnitude(), 3.1115f, REQUIRED_PRECISION);
    EXPECT_EQ(result.getAngle(), 54.5764_deg);
}

TEST(PhysicsVectorTest, ScalarMultiplication)
{
    using namespace domain::literals;

    domain::PhysicsVector vector(2.0f, 60.0_deg);
    float scalar = 3.0f;

    domain::PhysicsVector result { vector * scalar };

    EXPECT_NEAR(result.getMagnitude(), 6.0f, REQUIRED_PRECISION);
    EXPECT_EQ(result.getAngle(), 60.0_deg);
}

TEST(PhysicsVectorTest, ScalarDivision)
{
    using namespace domain::literals;

    domain::PhysicsVector vector(6.0f, 90.0_deg);
    float scalar = 2.0f;

    domain::PhysicsVector result { vector / scalar };

    EXPECT_NEAR(result.getMagnitude(), 3.0f, REQUIRED_PRECISION);
    EXPECT_EQ(result.getAngle(), 90.0_deg);
}

TEST(PhysicsVectorTest, Components)
{
    using namespace domain::literals;

    domain::PhysicsVector vector(5.0f, 45.0_deg);

    auto [x, y] = domain::PhysicsVector::getComponents(vector);

    EXPECT_NEAR(x, 3.53553390593f, REQUIRED_PRECISION);
    EXPECT_NEAR(y, 3.53553390593f, REQUIRED_PRECISION);
}
