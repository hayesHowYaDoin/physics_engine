#include <gtest/gtest.h>

#include "physics_backend/domain/vector.hpp"
#include "physics_backend/usecases/polygon.hpp"
#include "common/precision.hpp"

#include <iostream>

TEST(PolygonTest, LessThanThreeVertices)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    std::vector<physics::domain::PositionVector2D<Length>> vertices{
        physics::domain::PositionVector2D(0.0_m, 0.0_m),
        physics::domain::PositionVector2D(1.0_m, 0.0_m)
    };

    EXPECT_THROW(physics::usecases::Polygon2D<Length> polygon {vertices}, std::invalid_argument);
}

TEST(PolygonTest, VerticesIntegrity)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    std::vector<physics::domain::PositionVector2D<Length>> vertices{
        physics::domain::PositionVector2D(0.0_m, 0.0_m),
        physics::domain::PositionVector2D(1.0_m, 0.0_m),
        physics::domain::PositionVector2D(1.0_m, 1.0_m),
        physics::domain::PositionVector2D(0.0_m, 1.0_m)
    };

    physics::usecases::Polygon2D<Length> polygon {vertices};

    auto returnedVertices {polygon.getVertices()};

    ASSERT_EQ(returnedVertices.size(), vertices.size());

    for(auto const& vertex : vertices)
    {
        auto vertexIter {std::find_if(returnedVertices.begin(), returnedVertices.end(), 
            [&vertex](auto const& returnedVertex)
            {
                return physics::domain::Vector2D::compare(returnedVertex, vertex, physics::test::REQUIRED_PRECISION);
            }
        )};

        ASSERT_TRUE(vertexIter != returnedVertices.end());
    }
}

TEST(PolygonTest, EdgesIntegrity)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    std::vector<physics::domain::PositionVector2D<Length>> vertices {
        physics::domain::PositionVector2D(0.0_m, 0.0_m),
        physics::domain::PositionVector2D(1.0_m, 0.0_m),
        physics::domain::PositionVector2D(1.0_m, 1.0_m),
        physics::domain::PositionVector2D(0.0_m, 1.0_m)
    };

    physics::usecases::Polygon2D<Length> polygon {vertices};
    std::vector<physics::usecases::Edge2D<Length>> returnedEdges {polygon.getEdges()};

    ASSERT_EQ(returnedEdges.size(), vertices.size());

    for(auto vertex {vertices.begin()}; vertex != vertices.end(); ++vertex)
    {
        auto nextVertex {std::next(vertex)};
        if(nextVertex == vertices.end())
            nextVertex = vertices.begin();

        auto edgeIter {std::find_if(returnedEdges.begin(), returnedEdges.end(), 
            [&vertex, &nextVertex](auto const& returnedEdge)
            {
                return physics::domain::Vector2D::compare(returnedEdge.first, *vertex, physics::test::REQUIRED_PRECISION) &&
                       physics::domain::Vector2D::compare(returnedEdge.second, *nextVertex, physics::test::REQUIRED_PRECISION);
            })};

        ASSERT_TRUE(edgeIter != returnedEdges.end());
    }
}

TEST(PolygonTest, Boundaries)
{
    using namespace physics::units::literals;
    using Length = physics::units::SI::Length;

    std::vector<physics::domain::PositionVector2D<Length>> vertices {
        physics::domain::PositionVector2D(-1.0_m, 0.0_m),
        physics::domain::PositionVector2D(1.0_m, -2.0_m),
        physics::domain::PositionVector2D(2.5_m, 1.0_m),
        physics::domain::PositionVector2D(0.0_m, 1.0_m)
    };

    physics::usecases::Polygon2D<Length> polygon {vertices};

    auto xBoundaries {polygon.getXBoundaries()};
    auto yBoundaries {polygon.getYBoundaries()};

    std::cout << xBoundaries.lower << ", " << xBoundaries.upper << std::endl;
    std::cout << yBoundaries.lower << ", " << yBoundaries.upper << std::endl;

    ASSERT_NEAR(xBoundaries.lower.to<float>(), -1.0f, physics::test::REQUIRED_PRECISION);
    ASSERT_NEAR(xBoundaries.upper.to<float>(), 2.5f, physics::test::REQUIRED_PRECISION);
    ASSERT_NEAR(yBoundaries.lower.to<float>(), -2.0f, physics::test::REQUIRED_PRECISION);
    ASSERT_NEAR(yBoundaries.upper.to<float>(), 1.0f, physics::test::REQUIRED_PRECISION);

}
