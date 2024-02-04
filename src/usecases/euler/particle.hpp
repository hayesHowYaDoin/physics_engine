#ifndef USECASES_PARTICLE_HPP_
#define USECASES_PARTICLE_HPP_

#include <vector>

#include <units.h>

#include "physics_backend/euler.hpp"
#include "physics_backend/units.hpp"
#include "domain/vector.hpp"
#include "core/concepts.hpp"

namespace usecases::euler
{

template<physics_backend::IsUnitSystem Units>
struct EulerParticle
{
    using Mass = typename Units::Mass;
    using Position = typename Units::Length;
    using Velocity = typename Units::Velocity;
    using Force = typename Units::Force;

    Mass const mass;
    domain::PositionVector2D<Position> const position;
    domain::VelocityVector2D<Velocity> const velocity;
    std::vector<domain::ForceVector2D<Force>> const forces;

};

} // namespace usecases::euler

#endif // USECASES_PARTICLE_HPP_