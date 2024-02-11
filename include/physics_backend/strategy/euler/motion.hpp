#ifndef PHYSICS_BACKEND_STRATEGY_EULER_MOTION_HPP
#define PHYSICS_BACKEND_STRATEGY_EULER_MOTION_HPP

#include "physics_backend/domain/motion.hpp"
#include "physics_backend/strategy/euler/particle.hpp"
#include "physics_backend/units.hpp"

namespace physics::euler
{

template <physics::euler::IsParticle Particle, physics::units::IsTimeUnit Time>
[[nodiscard]] constexpr
auto resolveMotion(Particle const& particle, Time const& timeStep)
{
    using Force = typename Particle::Force;
    
    auto zeroForce {domain::Vector2D::fromComponents(Force(0.0), Force(0.0))};
    auto forcesSum {std::accumulate(particle.forces.begin(), particle.forces.end(), zeroForce)};

    auto acceleration {physics::domain::acceleration(forcesSum, particle.mass)};
    auto velocity {physics::domain::nextVelocity(particle.velocity, acceleration, timeStep)};
    auto position {physics::domain::nextPosition(particle.position, velocity, timeStep)};

    return Particle {
        .mass = particle.mass,
        .position = position,
        .velocity = velocity,
        .forces = particle.forces,
        .metadata = particle.metadata};
}

} // namespace physics::euler

#endif // PHYSICS_BACKEND_STRATEGY_EULER_MOTION_HPP
