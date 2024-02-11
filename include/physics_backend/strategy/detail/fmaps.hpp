#ifndef PHYSICS_BACKEND_STRATEGY_DETAIL_STEP_HELPER_HPP
#define PHYSICS_BACKEND_STRATEGY_DETAIL_STEP_HELPER_HPP

#include <concepts>
#include <functional>
#include <ranges>

#include "physics_backend/units.hpp"

namespace physics::detail
{

template <std::ranges::range Range, typename... Function>
auto fmaps(Range&& object, Function&&... func)
{
    return (std::forward<Range>(object) | ... | std::views::transform(func));
}

} // namespace physics::detail

#endif // PHYSICS_BACKEND_STRATEGY_DETAIL_STEP_HELPER_HPP
