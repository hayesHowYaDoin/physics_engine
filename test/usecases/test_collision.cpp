#include <gtest/gtest.h>

#include "common/precision.hpp"
#include "physics_backend/units.hpp"
#include "physics_backend/usecases/collision.hpp"
#include "physics_backend/usecases/polygon.hpp"

TEST(CollisionTest, PointInsidePolygon)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::usecases::Polygon2D<Length> polygon
    {
        {
            {0_m, 0_m},
            {0_m, 1_m},
            {1_m, 1_m},
            {1_m, 0_m}
        }
    };

    physics::domain::PositionVector2D<Length> point {0.5_m, 0.5_m};

    ASSERT_TRUE(physics::usecases::pointWithinPolygon(point, polygon));
}

TEST(CollisionTest, PointOutsidePolygon)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::usecases::Polygon2D<Length> polygon
    {
        {
            {0_m, 0_m},
            {0_m, 1_m},
            {1_m, 1_m},
            {1_m, 0_m}
        }
    };

    physics::domain::PositionVector2D<Length> point {2_m, 2_m};

    ASSERT_FALSE(physics::usecases::pointWithinPolygon(point, polygon));
}

TEST(CollisionTest, Corner)
{
    // TODO: Test when point X is in line with a vertex's X
}