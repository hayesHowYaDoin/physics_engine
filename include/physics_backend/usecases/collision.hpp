#ifndef PHYSICS_BACKEND_DOMAIN_COLLISION_HPP
#define PHYSICS_BACKEND_DOMAIN_COLLISION_HPP

#include "physics_backend/domain/geometry.hpp"
#include "physics_backend/usecases/edge.hpp"
#include "physics_backend/usecases/polygon.hpp"

namespace physics::usecases
{

template <units::IsLengthUnit Length>
[[nodiscard]] constexpr
bool pointWithinPolygon(
    physics::domain::PositionVector2D<Length> const& point, 
    physics::usecases::Polygon2D<Length> const& polygon)
{
    bool oddIntersectionsOnLeft {false};

    auto pointX {point.template getX<Length>()};
    auto pointY {point.template getY<Length>()};

    for(auto const& edge : polygon.getEdges())
    {
        auto intersectX {findEdgeXAtY(pointY, edge)};
        if(intersectX && intersectX.value() < pointX)
            oddIntersectionsOnLeft = !oddIntersectionsOnLeft;
    }

    return oddIntersectionsOnLeft;
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_DOMAIN_COLLISION_HPP