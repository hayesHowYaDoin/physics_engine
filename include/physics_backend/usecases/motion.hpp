#ifndef PHYSICS_BACKEND_USECASES_MOTION_HPP
#define PHYSICS_BACKEND_USECASES_MOTION_HPP

#include "physics_backend/domain/motion.hpp"
#include "physics_backend/usecases/particle.hpp"
#include "physics_backend/units.hpp"

namespace physics::usecases
{

template <physics::units::IsUnitSystem Units, physics::units::IsTimeUnit Time>
[[nodiscard]] constexpr
auto resolveMotion(Particle<Units> const& particle, Time const& timeStep)
{   
    using Force = typename Units::Force;

    auto zeroForce {domain::Vector2D::fromComponents(Force(0.0), Force(0.0))};
    auto forcesSum {std::accumulate(particle.forces.begin(), particle.forces.end(), zeroForce)};

    auto acceleration {physics::domain::acceleration(forcesSum, particle.mass)};
    auto velocity {physics::domain::nextVelocity(particle.velocity, acceleration, timeStep)};
    auto position {physics::domain::nextPosition(particle.position, velocity, timeStep)};

    return Particle<Units> {
        .mass = particle.mass,
        .radius = particle.radius,
        .position = position,
        .velocity = velocity,
        .forces = particle.forces,
        .metadata = particle.metadata};
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_MOTION_HPP
