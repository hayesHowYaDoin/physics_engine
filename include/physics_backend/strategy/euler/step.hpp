#ifndef PHYSICS_BACKEND_STRATEGY_EULER_STEP_HPP
#define PHYSICS_BACKEND_STRATEGY_EULER_STEP_HPP

#include <ranges>

#include "physics_backend/units.hpp"
#include "physics_backend/strategy/detail/step_helper.hpp"
#include "physics_backend/strategy/euler/particle.hpp"

namespace usecases::euler
{

template<std::ranges::range Range, physics::units::IsTimeUnit Time>
auto step(Range&& particle, Time time)
{
    static_assert(
        physics::euler::IsEulerParticle<std::ranges::range_value_t<Range>>,
        "Range value type must be a EulerParticle."
    );

    auto motion = [time](auto const& particle){return resolveMotion(particle, time)};

    return physics::detail::step_helper(std::forward<Range>(particle), motion);
}

} // namespace usecases::euler