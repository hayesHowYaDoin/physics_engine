#include "domain/vector.hpp"
#include <units.h>

#include <gtest/gtest.h>

TEST(VectorTest, ConstructFromAngleAndMagnitude)
{
    using namespace units::literals;

    auto vector = domain::Vector2D(45.0_deg, 10.0_N);

    EXPECT_EQ(vector.getAngle<units::degrees<double>>(), 45.0_deg);
    EXPECT_EQ(vector.getMagnitude<units::newtons<double>>(), 10.0_N);
}
