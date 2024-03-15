#ifndef PHYSICS_BACKEND_USECASES_PARTICLE_HPP
#define PHYSICS_BACKEND_USECASES_PARTICLE_HPP

#include <any>

#include "physics_engine/units.hpp"
#include "physics_engine/domain/vector.hpp"

namespace physics::usecases
{

template<physics::units::IsUnitSystem Units>
struct Particle
{
    using Mass = typename Units::Mass;
    using Length = typename Units::Length;
    using Velocity = typename Units::Velocity;
    using Force = typename Units::Force;

    Mass mass;
    Length radius;
    physics::domain::PositionVector2D<Length> position;
    physics::domain::VelocityVector2D<Velocity> velocity;
    std::vector<physics::domain::ForceVector2D<Force>> forces;
    std::any metadata = nullptr;
};

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_PARTICLE_HPP
