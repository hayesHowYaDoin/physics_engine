#ifndef PHYSICS_BACKEND_STRATEGY_EULER_STEP_HPP
#define PHYSICS_BACKEND_STRATEGY_EULER_STEP_HPP

#include <ranges>

#include "physics_backend/units.hpp"
#include "physics_backend/strategy/detail/fmaps.hpp"
#include "physics_backend/strategy/euler/motion.hpp"
#include "physics_backend/strategy/euler/particle.hpp"

namespace physics::euler
{

template<
    template <typename...> class Container,
    physics::euler::IsParticle Particle,
    physics::units::IsTimeUnit Time>
auto step(Container<Particle> const& particles, Time time)
{
    auto motion = [time](auto const& particle){ return resolveMotion(particle, time); };

    auto updatedParticles {physics::detail::fmaps(particles, motion)};
    return Container<Particle>(updatedParticles.begin(), updatedParticles.end());
}

} // namespace physics::euler

#endif // PHYSICS_BACKEND_STRATEGY_EULER_STEP_HPP
