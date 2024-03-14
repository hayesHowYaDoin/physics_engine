#ifndef PHYSICS_BACKEND_USECASES_EULER_CONSTRAIN_HPP
#define PHYSICS_BACKEND_USECASES_EULER_CONSTRAIN_HPP

#include "physics_backend/domain/geometry.hpp"
#include "physics_backend/usecases/detail/ray_casting.hpp"
#include "physics_backend/usecases/edge.hpp"
#include "physics_backend/usecases/objects.hpp"
#include "physics_backend/usecases/polygon.hpp"

namespace 
{

template <physics::units::IsLengthUnit Length>
physics::domain::PositionVector2D<Length> findClosestPoint(
    physics::domain::PositionVector2D<Length> const& point,
    physics::usecases::Edge2D<Length> const& edge)
{
    auto edgeFirstX {edge.first.template getX<Length>()};
    auto edgeFirstY {edge.first.template getY<Length>()};

    auto edgeSecondX {edge.second.template getX<Length>()};
    auto edgeSecondY {edge.second.template getY<Length>()};

    auto pointX {point.template getX<Length>()};
    auto pointY {point.template getY<Length>()};

    auto dx {edgeSecondX - edgeFirstX};
    auto dy {edgeSecondY - edgeFirstY};

    auto u {((pointX - edgeFirstX) * dx + (pointY - edgeFirstY) * dy) / (dx * dx + dy * dy)};

    if(u < 0)
        edge.first;
    else if(u > 1)
        edge.second;

    return physics::domain::PositionVector2D<Length>{edgeFirstX + u * dx, edgeFirstY + u * dy};
}

} // namespace

namespace physics::usecases
{

template <IsCircular Object, physics::units::IsLengthUnit Length>
Object resolveConstraint(Object& object, physics::usecases::Polygon2D<Length> const& constraint)
{
    using Angle = physics::units::angle::radians<double>;

    auto center {object.template getCenter()};
    auto radius {object.template getRadius()};

    auto objectCopy {object};

    for(auto const& edge : constraint.getEdges())
    {
        auto normal {center - findClosestPoint(center, edge)};
        auto distance {normal.template getMagnitude<Length>()};

        if(distance < radius)
        {
            auto normalAngle {normal.template getAngle<Angle>()};

            auto correction {physics::domain::Vector2D::fromPolar(normalAngle, radius - distance)};
            objectCopy.position = objectCopy.position + correction;

            objectCopy.velocity = physics::domain::reflect(objectCopy.velocity, normalAngle);
        }
    }

    return objectCopy;
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_EULER_CONSTRAIN_HPP
