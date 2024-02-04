#ifndef USECASES_EULER_RESOLVE_HPP_
#define USECASES_EULER_RESOLVE_HPP_

#include <algorithm>

#include "physics_backend/units.hpp"
#include "usecases/euler/particle.hpp"
#include "domain/motion.hpp"
#include "domain/vector.hpp"
#include "core/concepts.hpp"

namespace usecases::euler
{

template <physics_backend::IsUnitSystem Units, core::IsTimeUnit TimeUnit>
[[nodiscard]] constexpr
auto resolveMotion(EulerParticle<Units> const& particle, TimeUnit const& timeStep)
{
    using namespace units::literals;

    auto forcesSum {std::accumulate(particle.forces.begin(), particle.forces.end(), domain::ForceVector2D(0.0_N, 0.0_N))};

    auto acceleration {domain::motion::acceleration(forcesSum, particle.mass)};
    auto velocity {domain::motion::nextVelocity(particle.velocity, acceleration, timeStep)};
    auto position {domain::motion::nextPosition(particle.position, velocity, timeStep)};

    return EulerParticle<Units> {
        .mass = particle.mass,
        .position = position,
        .velocity = velocity,
        .forces = particle.forces};
}

} // namespace usecases::euler

#endif // USECASES_EULER_RESOLVE_HPP_
