#ifndef PHYSICS_BACKEND_USECASES_CONSTRAIN_HPP
#define PHYSICS_BACKEND_USECASES_CONSTRAIN_HPP

#include "physics_engine/domain/geometry.hpp"
#include "physics_engine/usecases/edge.hpp"
#include "physics_engine/usecases/polygon.hpp"


namespace physics::usecases
{

namespace __detail
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

} // namespace __detail

template <physics::units::IsUnitSystem Units>
Particle<Units> resolveConstraint(
    Particle<Units> const& particle,
    physics::usecases::Polygon2D<typename Units::Length> const& constraint)
{
    using Angle = physics::units::angle::radians<double>;

    auto center {particle.template position};
    auto radius {particle.template radius};

    auto particleCopy {particle};

    for(auto const& edge : constraint.getEdges())
    {
        auto normal {center - findClosestPoint(center, edge)};
        auto distance {normal.template getMagnitude<typename Units::Length>()};

        if(distance < radius)
        {
            auto normalAngle {normal.template getAngle<Angle>()};

            auto correction {physics::domain::Vector2D::fromPolar(normalAngle, radius - distance)};
            particleCopy.position = particleCopy.position + correction;

            particleCopy.velocity = physics::domain::reflect(particleCopy.velocity, normalAngle);
        }
    }

    return particleCopy;
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_CONSTRAIN_HPP
