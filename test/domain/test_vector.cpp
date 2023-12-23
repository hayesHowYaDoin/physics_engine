#include "domain/vector.hpp"
#include <units.h>

#include <gtest/gtest.h>

TEST(VectorTest, ConstructFromAngleAndMagnitude)
{
    using namespace units::literals;

    auto vector = domain::Vector2D(45.0_deg, 10.0_N);
    EXPECT_EQ(vector.m_angle, 45.0_deg);
    EXPECT_EQ(vector.m_magnitude, 10.0_N);
}
