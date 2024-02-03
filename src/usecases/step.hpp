#ifndef USECASES_STEP_HPP_
#define USECASES_STEP_HPP_

#include "core/concepts.hpp"

#include <concepts>
#include <functional>
#include <ranges>

namespace usecases
{

    template <std::ranges::range Range, std::invocable<std::ranges::range_value_t<Range>> ResolveFunc>
    auto step(Range&& particles, ResolveFunc&& resolve)
    {
        return std::forward<Range>(particles) | std::views::transform(resolve);
    }

} // namespace usecases

#endif // USECASES_STEP_HPP_