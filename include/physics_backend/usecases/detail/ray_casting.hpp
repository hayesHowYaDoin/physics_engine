#ifndef PHYSICS_BACKEND_DOMAIN_COLLISION_HPP
#define PHYSICS_BACKEND_DOMAIN_COLLISION_HPP

#include "physics_backend/domain/geometry.hpp"
#include "physics_backend/usecases/edge.hpp"
#include "physics_backend/usecases/polygon.hpp"

namespace physics::detail
{

template <physics::units::IsLengthUnit Length>
[[nodiscard]] constexpr
std::optional<Length> findEdgeXAtY(
    Length const& y,
    physics::usecases::Edge2D<Length> const& edge,
    float const& epsilon = 1e-6)
{
    auto x1 {edge.first.template getX<Length>()};
    auto y1 {edge.first.template getY<Length>()};

    auto x2 {edge.second.template getX<Length>()};
    auto y2 {edge.second.template getY<Length>()};

    // Vertical edge
    if(x1 == x2)
    {
        if(y <= y1 && y >= y2 || y >= y1 && y <= y2)
            return x1;

        return std::nullopt;
    }

    // Horizontal edge
    if(y1 == y2)
    {
        if(y == y1)
            return x1;

        return std::nullopt;
    }

    auto m {(y2 - y1) / (x2 - x1)};
    auto b {y1 - m * x1};
    auto x {(y - b) / m};

    return x >= x1 && x < x2 ? std::make_optional(x) : std::nullopt;
}

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