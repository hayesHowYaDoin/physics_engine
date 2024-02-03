#ifndef USECASES_STEP_HPP_
#define USECASES_STEP_HPP_

#include "core/concepts.hpp"

#include <concepts>
#include <functional>
#include <ranges>

namespace usecases
{

    template <std::ranges::range Range, typename ResolveFunc>
    auto step(Range&& particles, ResolveFunc&& resolve)
    {
        using RangeType = std::ranges::range_value_t<Range>;

        static_assert(
            std::invocable<ResolveFunc, RangeType>,
            "Resolve strategy must take the aggregated particle type.");
        static_assert(
            std::same_as<std::invoke_result_t<ResolveFunc, RangeType>, RangeType>,
            "Resolve strategy must return the aggregated particle type.");

        return std::forward<Range>(particles) | std::views::transform(resolve);
    }

    } // namespace usecases

    #endif // USECASES_STEP_HPP_
