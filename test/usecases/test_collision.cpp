#include <gtest/gtest.h>

#include "common/precision.hpp"
#include "physics_backend/units.hpp"
#include "physics_backend/usecases/collision.hpp"
#include "physics_backend/usecases/polygon.hpp"

TEST(CollisionTest, PointInsidePolygon)
{
    /*
        +-----+
        |  *  |
        |     |
        +-----+
    */

    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::domain::PositionVector2D<Length> point {0.5_m, 0.5_m};
    physics::usecases::Polygon2D<Length> polygon
    {
        {
            {0_m, 0_m},
            {0_m, 1_m},
            {1_m, 1_m},
            {1_m, 0_m}
        }
    };

    ASSERT_TRUE(physics::usecases::pointWithinPolygon(point, polygon));
}

TEST(CollisionTest, PointOutsidePolygon)
{
    /*
                   *
        +-----+
        |     |
        |     |
        +-----+
    */
    
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::domain::PositionVector2D<Length> point {2_m, 2_m};
    physics::usecases::Polygon2D<Length> polygon
    {
        {
            {-1_m, -1_m},
            {-1_m, 1_m},
            {1_m, 1_m},
            {1_m, -1_m}
        }
    };

    ASSERT_FALSE(physics::usecases::pointWithinPolygon(point, polygon));
}

TEST(CollisionTest, InLineWithCorners)
{
    /*
            ^
          /   \
        <   *   >
          \   /
            v
    */
        
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::domain::PositionVector2D<Length> point {0_m, 0_m};
    physics::usecases::Polygon2D<Length> polygon
    {
        {
            {-1_m, 0_m},
            {0_m, 1_m},
            {1_m, 0_m},
            {0_m, -1_m}
        }
    };

    ASSERT_TRUE(physics::usecases::pointWithinPolygon(point, polygon));
}

TEST(CollisionTest, PointOnCorners)
{
    /*
        *---*
        |   |
        |   |
        *---*
    */
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::domain::PositionVector2D<Length> upperRight {1_m, 1_m};
    physics::domain::PositionVector2D<Length> lowerRight {1_m, -1_m};
    physics::domain::PositionVector2D<Length> lowerLeft {-1_m, -1_m};
    physics::domain::PositionVector2D<Length> upperLeft {-1_m, 1_m};
    physics::usecases::Polygon2D<Length> polygon
    {
        {
            {-1_m, -1_m},
            {-1_m, 1_m},
            {1_m, 1_m},
            {1_m, -1_m}
        }
    };

    ASSERT_FALSE(physics::usecases::pointWithinPolygon(upperRight, polygon));
    ASSERT_TRUE(physics::usecases::pointWithinPolygon(lowerRight, polygon));
    ASSERT_FALSE(physics::usecases::pointWithinPolygon(lowerLeft, polygon));
    ASSERT_FALSE(physics::usecases::pointWithinPolygon(upperLeft, polygon));
}

TEST(CollisionTest, ConcavePolygonUpper)
{
    /*
        +       +---+
        |*\   /   * |     *
        |   +       |
        |           |
        +-----------+
    */
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::domain::PositionVector2D<Length> point1 {1.5_m, 0.5_m};
    physics::domain::PositionVector2D<Length> point2 {-0.9_m, 0.1_m};
    physics::domain::PositionVector2D<Length> point3 {3_m, 0.5_m};
    physics::usecases::Polygon2D<Length> polygon
    {
        {
            {-1_m, 1_m},
            {0_m, 0_m},
            {1_m, 1_m},
            {2_m, 1_m},
            {2_m, -1_m},
            {-1_m, -1_m}
        }
    };

    // ASSERT_TRUE(physics::usecases::pointWithinPolygon(point1, polygon));
    ASSERT_TRUE(physics::usecases::pointWithinPolygon(point2, polygon));
    ASSERT_FALSE(physics::usecases::pointWithinPolygon(point3, polygon));
}

TEST(CollisionTest, ConcavePolygonLower)
{
    /*
        +-----------+
        |           |
        |       +   |
        |   * /   \*|     *
        +---+       +
    */
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    physics::domain::PositionVector2D<Length> point1 {1.9_m, -0.25_m};
    physics::domain::PositionVector2D<Length> point2 {-0.5_m, -0.5_m};
    physics::domain::PositionVector2D<Length> point3 {3_m, -0.5_m};
    physics::usecases::Polygon2D<Length> polygon
    {
        {
            {2_m, -1_m},
            {1_m, 0_m},
            {0_m, -1_m},
            {-1_m, -1_m},
            {-1_m, 1_m},
            {2_m, 1_m}
        }
    };

    ASSERT_TRUE(physics::usecases::pointWithinPolygon(point1, polygon));
    ASSERT_TRUE(physics::usecases::pointWithinPolygon(point2, polygon));
    ASSERT_FALSE(physics::usecases::pointWithinPolygon(point3, polygon));
}

TEST(CollisionTest, PointOnEdges)
{
    /*
        +-----+
        |     *
        |     |
        +--*--+
    */

   // TODO: Implement this test
}
