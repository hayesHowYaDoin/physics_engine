#ifndef PHYSICS_BACKEND_STRATEGY_EULER_STEP_HPP
#define PHYSICS_BACKEND_STRATEGY_EULER_STEP_HPP

#include <ranges>

#include "physics_backend/units.hpp"
#include "physics_backend/strategy/detail/step_helper.hpp"
#include "physics_backend/strategy/euler/particle.hpp"

namespace physics::euler
{

template<std::ranges::range Range, physics::units::IsTimeUnit Time>
auto step(Range&& particle, Time time)
{
    // TODO: Static assert fails with euler::Particle.
    // static_assert(
    //     physics::euler::IsParticle<std::ranges::range_value_t<Range>>,
    //     "Range value type must be a Particle."
    // );

    auto motion = [time](auto const& particle){ return resolveMotion(particle, time); };

    return physics::detail::step_helper(std::forward<Range>(particle), motion);
}

} // namespace physics::euler

#endif // PHYSICS_BACKEND_STRATEGY_EULER_STEP_HPP
