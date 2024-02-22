#include <gtest/gtest.h>

#include "physics_backend/domain/vector.hpp"
#include "physics_backend/usecases/polygon.hpp"

#include <iostream>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

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
                return physics::domain::Vector2D::compare(returnedVertex, vertex, REQUIRED_PRECISION);
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
                return physics::domain::Vector2D::compare(returnedEdge.first, *vertex, REQUIRED_PRECISION) &&
                       physics::domain::Vector2D::compare(returnedEdge.second, *nextVertex, REQUIRED_PRECISION);
            })};

        ASSERT_TRUE(edgeIter != returnedEdges.end());
    }
}