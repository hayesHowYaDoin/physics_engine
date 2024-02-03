#ifndef USECASES_PARTICLE_HPP_
#define USECASES_PARTICLE_HPP_

#include "physics_backend/euler/si.hpp"
#include "domain/vector.hpp"
#include "core/concepts.hpp"
#include <units.h>

#include <vector>

namespace usecases
{

template<core::IsMassUnit Mass, core::IsLengthUnit Position, core::IsVelocityUnit Velocity, core::IsForceUnit Force>
struct EulerParticle
{
    Mass const mass;
    domain::PositionVector2D<Position> const position;
    domain::VelocityVector2D<Velocity> const velocity;
    std::vector<domain::ForceVector2D<Force>> const forces;
};

template<typename T>
concept IsEulerParticle = requires(T t)
{
    { EulerParticle{t} } -> std::same_as<T>;
};

} // namespace usecases

#endif // USECASES_PARTICLE_HPP_