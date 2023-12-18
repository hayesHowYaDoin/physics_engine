#include "domain/vector.hpp"

#include <gtest/gtest.h>

TEST(PhysicsVectorTest, MagnitudeAndAngle)
{
    using namespace domain::literals;

    domain::PhysicsVector vector(5.0f, 45.0_deg);

    EXPECT_FLOAT_EQ(vector.getMagnitude(), 5.0f);
    EXPECT_EQ(vector.getAngle(), 45.0_deg);
}

TEST(PhysicsVectorTest, Addition)
{
    using namespace domain::literals;

    domain::PhysicsVector vector1(3.0f, 30.0_deg);
    domain::PhysicsVector vector2(4.0f, 60.0_deg);

    domain::PhysicsVector result { vector1 + vector2 };

    EXPECT_FLOAT_EQ(result.getMagnitude(), 6.76643f);
    EXPECT_EQ(result.getAngle(), 47.1921_deg);
}

TEST(PhysicsVectorTest, Subtraction)
{
    using namespace domain::literals;

    domain::PhysicsVector vector1(5.0f, 45.0_deg);
    domain::PhysicsVector vector2(2.0f, 30.0_deg);

    domain::PhysicsVector result { vector1 - vector2 };

    EXPECT_FLOAT_EQ(result.getMagnitude(), 3.0f);
    EXPECT_EQ(result.getAngle(), 15.0_deg);
}

TEST(PhysicsVectorTest, ScalarMultiplication)
{
    using namespace domain::literals;

    domain::PhysicsVector vector(2.0f, 60.0_deg);
    float scalar = 3.0f;

    domain::PhysicsVector result { vector * scalar };

    EXPECT_FLOAT_EQ(result.getMagnitude(), 6.0f);
    EXPECT_EQ(result.getAngle(), 60.0_deg);
}

TEST(PhysicsVectorTest, ScalarDivision)
{
    using namespace domain::literals;

    domain::PhysicsVector vector(6.0f, 90.0_deg);
    float scalar = 2.0f;

    domain::PhysicsVector result { vector / scalar };

    EXPECT_FLOAT_EQ(result.getMagnitude(), 3.0f);
    EXPECT_EQ(result.getAngle(), 90.0_deg);
}

TEST(PhysicsVectorTest, Components)
{
    using namespace domain::literals;

    domain::PhysicsVector vector(5.0f, 45.0_deg);

    auto [x, y] = domain::PhysicsVector::getComponents(vector);

    EXPECT_FLOAT_EQ(x, 3.53553390593f);
    EXPECT_FLOAT_EQ(y, 3.53553390593f);
}
