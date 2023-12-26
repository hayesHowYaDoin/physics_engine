#ifndef USECASES_STEP_HPP_
#define USECASES_STEP_HPP_

#include "core/concepts.hpp"

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
    return particles | std::views::transform(resolveMotion);
}

} // namespace usecases

#endif // USECASES_STEP_HPP_