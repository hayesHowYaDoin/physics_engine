#ifndef PHYSICS_BACKEND_USECASES_EULER_PARTICLE_HPP
#define PHYSICS_BACKEND_USECASES_EULER_PARTICLE_HPP

#include <any>

#include "physics_backend/units.hpp"
#include "physics_backend/domain/vector.hpp"

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
    physics::domain::PositionVector2D<Position> const position;
    physics::domain::VelocityVector2D<Velocity> const velocity;
    std::vector<physics::domain::ForceVector2D<Force>> const forces;

    std::any metadata = nullptr;
};

template <typename T>
concept IsParticle = requires(T t)
{
    physics::units::IsMassUnit<decltype(t.mass)>;
    physics::domain::IsPositionVector2D<decltype(t.position)>;
    physics::domain::IsVelocityVector2D<decltype(t.velocity)>;
    physics::domain::IsForceVector2D<std::ranges::range_value_t<decltype(t.forces)>>;
};

} // namespace physics::euler

#endif // PHYSICS_BACKEND_USECASES_EULER_PARTICLE_HPP
