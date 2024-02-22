#ifndef PHYSICS_BACKEND_DOMAIN_POLYGON_HPP
#define PHYSICS_BACKEND_DOMAIN_POLYGON_HPP

#include <vector>

#include "physics_backend/units.hpp"

namespace physics::usecases
{

    template <physics::units::IsLengthUnit Length>
    class Polygon2D
    {
        Polygon2D(std::vector<physics::domain::Vector2D<Length>> vertices): 
            vertices(std::move(vertices))
        {
            if(m_vertices.size() < 3)
            {
                throw std::invalid_argument("A polygon must have at least 3 vertices.");
            }

            m_edges.reserve(m_vertices.size());
            
            m_edges.push_back({m_vertices.back(), m_vertices.front()});
            for(auto vertex {m_vertices.begin()+1}; vertex != m_vertices.end(); ++vertex)
            {
                m_edges.push_back({*(vertex-1), *vertex});
            }
        }

        [[nodiscard]] std::vector<physics::domain::Edge2D<Length>> getVertices() const
        {
            return m_vertices;
        }

        [[nodiscard]] std::vector<physics::domain::Edge2D<Length>> getEdges() const
        {
            return m_edges;
        }

    private:
        std::vector<physics::domain::Vector2D<Length>> m_vertices;
        std::vector<physics::domain::Edge2D<Length>> m_edges;
    };

}

#endif // PHYSICS_BACKEND_DOMAIN_POLYGON_HPP
