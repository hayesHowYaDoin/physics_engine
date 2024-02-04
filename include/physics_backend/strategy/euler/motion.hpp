#ifndef PHYSICS_BACKEND_STRATEGY_EULER_MOTION_HPP
#define PHYSICS_BACKEND_STRATEGY_EULER_MOTION_HPP

#include "physics_backend/domain/motion.hpp"
#include "physics_backend/strategy/euler/particle.hpp"
#include "physics_backend/units.hpp"

namespace physics::euler
{

template <physics::units::IsUnitSystem Units, physics::units::IsTimeUnit Time>
[[nodiscard]] constexpr
auto resolveMotion(Particle<Units> const& particle, Time const& timeStep)
{
    using namespace units::literals;

    auto forcesSum {std::accumulate(particle.forces.begin(), particle.forces.end(), domain::ForceVector2D(0.0_N, 0.0_N))};

    auto acceleration {physics::domain::acceleration(forcesSum, particle.mass)};
    auto velocity {physics::domain::nextVelocity(particle.velocity, acceleration, timeStep)};
    auto position {physics::domain::nextPosition(particle.position, velocity, timeStep)};

    return Particle<Units> {
        .mass = particle.mass,
        .position = position,
        .velocity = velocity,
        .forces = particle.forces};
}

} // namespace physics::euler

#endif // PHYSICS_BACKEND_STRATEGY_EULER_MOTION_HPP
