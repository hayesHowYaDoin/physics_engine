#ifndef USECASES_EULER_RESOLVE_HPP_
#define USECASES_EULER_RESOLVE_HPP_

#include "usecases/euler/particle.hpp"
#include "domain/motion.hpp"
#include "domain/vector.hpp"
#include "core/concepts.hpp"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

namespace usecases::euler
{

template <core::IsTimeUnit TimeUnit>
[[nodiscard]] constexpr
EulerParticle resolveMotion(
    EulerParticle const& particle,
    TimeUnit const& timeStep)
{
    using namespace units::literals;

    auto forcesSum {std::accumulate(particle.forces.begin(), particle.forces.end(), domain::ForceVector2D(0.0_N, 0.0_N))};

    auto acceleration {domain::motion::acceleration<units::acceleration::meters_per_second_squared<double>>(forcesSum, particle.mass)};
    auto velocity {domain::motion::nextVelocity(particle.velocity, acceleration, timeStep)};
    auto position {domain::motion::nextPosition(particle.position, velocity, timeStep)};

    return EulerParticle {
        .position = position,
        .velocity = velocity,
        .mass = particle.mass,
        .forces = particle.forces};
}

template <core::IsTimeUnit TimeUnit>
[[nodiscard]] constexpr
auto step(
    std::ranges::range auto const& particles,
    TimeUnit const& timeStep,
    std::function<EulerParticle(EulerParticle const&)> const& resolveMotion)
{
    return particles | std::views::transform(resolveMotion);
}

} // namespace usecases::euler

#endif // USECASES_EULER_RESOLVE_HPP_
