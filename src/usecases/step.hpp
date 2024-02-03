#ifndef USECASES_STEP_HPP_
#define USECASES_STEP_HPP_

#include "core/concepts.hpp"

#include <concepts>
#include <functional>
#include <ranges>

namespace usecases
{

template <typename ObjectType>
[[nodiscard]] constexpr
auto step(
    std::ranges::range auto const& particles,
    std::function<ObjectType(ObjectType const&)> resolveMotion)
{
    static_assert(std::same_as<ObjectType, std::ranges::range_value_t<decltype(particles)>>);
    
    return particles | std::views::transform(resolveMotion);
}

} // namespace usecases

#endif // USECASES_STEP_HPP_