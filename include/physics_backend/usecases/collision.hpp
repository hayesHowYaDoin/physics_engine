#ifndef PHYSICS_BACKEND_DOMAIN_COLLISION_HPP
#define PHYSICS_BACKEND_DOMAIN_COLLISION_HPP

#include "physics_backend/domain/geometry.hpp"
#include "physics_backend/usecases/polygon.hpp"

namespace physics::usecases
{

template <units::IsLengthUnit Length>
[[nodiscard]] constexpr
bool pointWithinPolygon(
    physics::domain::PositionVector2D<Length> const& point, 
    physics::usecases::Polygon2D<Length> const& polygon)
{
    uint32_t leftIntersections {0};

    auto const& pointX {point.template getX<Length>()};
    auto const& pointY {point.template getY<Length>()};

    for(auto const& edge : polygon.getEdges())
    {
        auto const& [start, end] = edge;
        auto const& x1 {start.template getX<Length>()};
        auto const& y1 {start.template getY<Length>()};
        auto const& x2 {end.template getX<Length>()};
        auto const& y2 {start.template getY<Length>()};

        if(y1 > pointY && y2 <= pointY ||
	       y2 > pointY && y1 <= pointY)
        {
            if(x1 <= pointX || x2 <= pointX)
                leftIntersections++;
        }
    }

    return (leftIntersections % 2) != 0;
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_DOMAIN_COLLISION_HPP