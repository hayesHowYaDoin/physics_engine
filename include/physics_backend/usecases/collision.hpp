#ifndef PHYSICS_BACKEND_USECASES_COLLISION_HPP
#define PHYSICS_BACKEND_USECASES_COLLISION_HPP

#include "physics_backend/units.hpp"
#include "physics_backend/domain/geometry.hpp"
#include "physics_backend/usecases/particle.hpp"
#include "physics_backend/domain/vector.hpp"

#include <algorithm>
#include <ranges>
#include <functional>

namespace {

template <physics::units::IsUnitSystem Units>
void resolvePenetration(
    physics::usecases::Particle<Units>& first,
    physics::usecases::Particle<Units>& second,
    physics::domain::PositionVector2D<typename Units::Length> const& normal,
    typename Units::Length const& distance,
    typename Units::Length const& sumRadii)
{
    using Length = typename Units::Length;

    Length penetration {sumRadii - distance};
    physics::domain::PositionVector2D<Length> correction {normal * (penetration / Length(2.0))};

    first.position = first.position + correction;
    second.position = second.position - correction;
}

template <physics::units::IsUnitSystem Units>
void resolveRebound(
    physics::usecases::Particle<Units>& first,
    physics::usecases::Particle<Units>& second,
    physics::domain::PositionVector2D<typename Units::Length> const& normal)
{
    using Length = typename Units::Length;
    using Velocity = typename Units::Velocity;
    using Mass = typename Units::Mass;
    using Angle = typename physics::units::angle::radians<double>;
    using physics::units::literals::operator""_s;

    static constexpr float epsilon {1.0f};  // Fully elastic collision

    physics::domain::VelocityVector2D<Velocity> relativeVelocity {first.velocity - second.velocity};

    float impulseMagnitude {-(1 + epsilon) * relativeVelocity.dot(normal) /
                            (1 / first.mass + 1 / second.mass)};
    auto impulseDirection {normal.template getAngle<Angle>()};

    physics::domain::VelocityVector2D<Velocity> jn {
        physics::domain::Vector2D::fromPolar(impulseDirection, Velocity(impulseMagnitude))
    };

    first.velocity = first.velocity + jn / (first.mass / Mass(1.0f));
    second.velocity = second.velocity - jn / (second.mass / Mass(1.0f));
}

template <physics::units::IsUnitSystem Units>
void resolveCollisionImpl(physics::usecases::Particle<Units>& first, physics::usecases::Particle<Units>& second)
{
    using Length = typename Units::Length;

    Length distance {physics::domain::distance(first.position, second.position)};
    Length sumRadii {first.radius + second.radius};

    if(distance < sumRadii)
    {
        physics::domain::PositionVector2D<Length> normal {
            physics::domain::normalize(first.position - second.position)
        };
        
        resolvePenetration(first, second, normal, distance, sumRadii);
        resolveRebound(first, second, normal);
    }
}

} // namespace

namespace physics::usecases
{

template <template <typename...> class Container, physics::units::IsUnitSystem Units>
void resolveCollisions(Container<Particle<Units>>& particles)
{
    for(auto first {particles.begin()}; first != particles.end(); ++first)
    {
        for(auto second {std::next(first)}; second != particles.end(); ++second)
        {
            resolveCollisionImpl(*first, *second);
        }
    }
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_COLLISION_HPP