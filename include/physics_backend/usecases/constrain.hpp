#ifndef PHYSICS_BACKEND_USECASES_EULER_CONSTRAIN_HPP
#define PHYSICS_BACKEND_USECASES_EULER_CONSTRAIN_HPP

#include <cmath>

#include "physics_backend/usecases/detail/ray_casting.hpp"
#include "physics_backend/usecases/edge.hpp"
#include "physics_backend/usecases/polygon.hpp"

namespace 
{

template <typename T>
concept IsCircular = requires(T t)
{
    {t.getRadius()};
    {t.getCenter()};
};

template <physics::units::IsLengthUnit Length>
Length distanceToEdge(physics::domain::PositionVector2D<Length> const& point, physics::usecases::Edge2D<Length> const& edge)
{
    auto const& [a, b] {edge};
    auto const& [x, y] {point};

    auto const dx {b.x - a.x};
    auto const dy {b.y - a.y};

    auto const u {((x - a.x) * dx + (y - a.y) * dy) / (dx * dx + dy * dy)};

    if(u < 0)
        return physics::domain::distance(point, a);
    if(u > 1)
        return physics::domain::distance(point, b);

    auto const intersection {physics::domain::PositionVector2D<Length>{a.x + u * dx, a.y + u * dy}};
    return physics::domain::distance(point, intersection);
}

template <IsCircular Object, physics::units::IsUnitSystem Units>
bool isInBounds(Object const& object, physics::usecases::Polygon2D<Units> const& constraint)
{
    auto objectCenter {object.template getCenter<typename Units::Length>()};

    if(!physics::detail::pointWithinPolygon(objectCenter, constraint))
        return false;

    for(auto const& edge : constraint.getEdges())
    {
        auto distance {distanceToEdge(objectCenter, edge)};

        if(distance < object.template getRadius<typename Units::Length>())
            return false;
    }

    return true;
}

} // namespace

namespace physics::usecases
{

template<typename Object, physics::units::IsUnitSystem Units>
auto resolveConstraint(Object const& object, physics::usecases::Polygon2D<Units> const& constraint)
{
    if(isInBounds(object, constraint))
        return object;

    return applyConstraint(object, constraint);
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_EULER_CONSTRAIN_HPP
