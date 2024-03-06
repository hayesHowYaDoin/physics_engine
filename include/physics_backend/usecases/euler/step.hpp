#ifndef PHYSICS_BACKEND_USECASES_EULER_STEP_HPP
#define PHYSICS_BACKEND_USECASES_EULER_STEP_HPP

#include <ranges>

#include "physics_backend/units.hpp"
#include "physics_backend/usecases/collision.hpp"
#include "physics_backend/usecases/constrain.hpp"
#include "physics_backend/usecases/polygon.hpp"
#include "physics_backend/usecases/detail/fmaps.hpp"
#include "physics_backend/usecases/euler/motion.hpp"
#include "physics_backend/usecases/euler/particle.hpp"

namespace physics::euler
{

template<
    template <typename...> class Container,
    physics::units::IsUnitSystem Units,
    physics::units::IsTimeUnit Time>
auto step(
    Container<Particle<Units>> const& particles,
    physics::usecases::Polygon2D<typename Units::Length> const& constraint,
    Time time,
    size_t substeps = 1)
{
    auto motion = [&time](auto const& particle){ return resolveMotion(particle, time); };
    auto constrain = [&constraint](auto const& particle){ return physics::usecases::resolveConstraint(particle, constraint); };

    auto updatedParticles {physics::detail::fmaps(particles, motion, constrain)};

    for(size_t step {0}; step < substeps; ++step)
    {
        updatedParticles = physics::usecases::resolveCollisions(updatedParticles);
    }

    return Container<Particle<Units>>(updatedParticles.begin(), updatedParticles.end());
}

} // namespace physics::euler

#endif // PHYSICS_BACKEND_USECASES_EULER_STEP_HPP
