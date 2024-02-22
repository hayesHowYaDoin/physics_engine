#ifndef PHYSICS_BACKEND_DOMAIN_POLYGON_HPP
#define PHYSICS_BACKEND_DOMAIN_POLYGON_HPP

#include <vector>

#include "physics_backend/units.hpp"
#include "physics_backend/usecases/edge.hpp"

namespace physics::usecases
{

template <physics::units::IsLengthUnit Length>
class Polygon2D
{
public:
    Polygon2D(std::vector<physics::domain::PositionVector2D<Length>> vertices): 
        m_vertices {std::move(vertices)}
    {
        if(m_vertices.size() < 3)
        {
            throw std::invalid_argument("A polygon must have at least 3 vertices (" + 
                                        std::to_string(m_vertices.size()) + " provided).");
        }

        m_edges.reserve(m_vertices.size());
        
        m_edges.push_back({m_vertices.back(), m_vertices.front()});
        for(auto vertex {m_vertices.begin()+1}; vertex != m_vertices.end(); ++vertex)
        {
            m_xBoundaries.lower = std::min(m_xBoundaries.lower, vertex->template getX<Length>());
            m_xBoundaries.upper = std::max(m_xBoundaries.upper, vertex->template getX<Length>());

            m_yBoundaries.lower = std::min(m_yBoundaries.lower, vertex->template getY<Length>());
            m_yBoundaries.upper = std::max(m_yBoundaries.upper, vertex->template getY<Length>());

            m_edges.push_back({*(vertex-1), *vertex});
        }
    }

    [[nodiscard]] std::vector<physics::domain::PositionVector2D<Length>> getVertices() const
    {
        return m_vertices;
    }

    [[nodiscard]] std::vector<physics::usecases::Edge2D<Length>> getEdges() const
    {
        return m_edges;
    }

    struct Boundaries
    {
        Length lower;
        Length upper;
    };

    [[nodiscard]] Boundaries getXBoundaries() const
    {
        return m_xBoundaries;
    }

    [[nodiscard]] Boundaries getYBoundaries() const
    {
        return m_yBoundaries;
    }

private:
    std::vector<physics::domain::PositionVector2D<Length>> m_vertices;
    std::vector<physics::usecases::Edge2D<Length>> m_edges;
    Boundaries m_xBoundaries;
    Boundaries m_yBoundaries;
};

}

#endif // PHYSICS_BACKEND_DOMAIN_POLYGON_HPP
