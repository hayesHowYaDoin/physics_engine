#ifndef PHYSICS_BACKEND_USECASES_DETAIL_STEP_HELPER_HPP
#define PHYSICS_BACKEND_USECASES_DETAIL_STEP_HELPER_HPP

#include <concepts>
#include <functional>
#include <ranges>

#include "physics_engine/units.hpp"

namespace physics::detail
{

template <std::ranges::range Range, typename... Function>
auto fmaps(Range&& objects, Function&&... func)
{
    return (std::forward<Range>(objects) | ... | std::views::transform(func));
}

} // namespace physics::detail

#endif // PHYSICS_BACKEND_USECASES_DETAIL_STEP_HELPER_HPP
