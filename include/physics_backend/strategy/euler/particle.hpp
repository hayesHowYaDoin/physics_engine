#ifndef PHYSICS_BACKEND_STRATEGY_EULER_PARTICLE_HPP
#define PHYSICS_BACKEND_STRATEGY_EULER_PARTICLE_HPP

#include <any>

#include "physics_backend/units.hpp"

namespace physics::euler
{

template<physics::units::IsUnitSystem Units>
struct Particle
{
    using Mass = typename Units::Mass;
    using Position = typename Units::Length;
    using Velocity = typename Units::Velocity;
    using Force = typename Units::Force;

    Mass const mass;
    physics::units::PositionVector2D<Position> const position;
    physics::units::VelocityVector2D<Velocity> const velocity;
    std::vector<physics::units::ForceVector2D<Force>> const forces;

    std::any metadata = nullptr;
};

template <typename T>
concept IsParticle = requires(T t)
{
    physics::units::IsMassUnit<decltype(t.mass)>;
    physics::units::IsPositionVector2D<decltype(t.position)>;
    physics::units::IsVelocityVector2D<decltype(t.velocity)>;
    physics::units::IsForceVector2D<std::ranges::range_value_t<decltype(t.forces)>>;
};

} // namespace physics::euler

#endif // PHYSICS_BACKEND_STRATEGY_EULER_PARTICLE_HPP
