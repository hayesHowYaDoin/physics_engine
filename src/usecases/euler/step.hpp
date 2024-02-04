#ifndef USECASES_PARTICLE_HPP_
#define USECASES_PARTICLE_HPP_

#include <ranges>

#include "core/concepts.hpp"
#include "usecases/step.hpp"

namespace usecases::euler
{

template<std::ranges::range Range, core::IsTimeUnit Time>
auto step(Range&& particle, Time time)
{
    auto motion = [time](auto const& particle){return resolveMotion(particle, time)};

    return usecases::step(std::forward<Range>(particle), motion);
}

} // namespace usecases::euler

#endif // USECASES_PARTICLE_HPP_