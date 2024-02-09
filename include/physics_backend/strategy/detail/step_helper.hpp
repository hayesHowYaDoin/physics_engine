#ifndef PHYSICS_BACKEND_STRATEGY_DETAIL_STEP_HELPER_HPP
#define PHYSICS_BACKEND_STRATEGY_DETAIL_STEP_HELPER_HPP

#include <concepts>
#include <functional>
#include <ranges>

#include "physics_backend/units.hpp"

namespace physics::detail
{

template <std::ranges::range Range, typename... Function>
auto step_helper(Range&& particles, Function&&... motion)
{
    using RangeType = std::ranges::range_value_t<Range>;

    // TODO: Static assert fails with euler::Particle.
    // static_assert(
    //     (std::invocable<Function, RangeType>, ...),
    //     "Resolve strategy must take the aggregated particle type.");
    // static_assert(
    //     (std::same_as<std::invoke_result_t<Function, RangeType>, RangeType>, ...),
    //     "Resolve strategy must return the aggregated particle type.");

    return (std::forward<Range>(particles) | ... | std::views::transform(motion));
}

} // namespace physics::detail

#endif // PHYSICS_BACKEND_STRATEGY_DETAIL_STEP_HELPER_HPP
