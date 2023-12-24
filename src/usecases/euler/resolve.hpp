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

namespace usecases
{

template <core::IsForceUnit ForceUnit, core::IsTimeUnit TimeUnit>
[[nodiscard]] constexpr
EulerParticle resolveMotion(
    EulerParticle const& particle,
    std::vector<domain::ForceVector2D<ForceUnit>> const& forces,
    TimeUnit const& timeStep)
{
    auto forcesSum {std::accumulate(forces.begin(), forces.end(), ForceUnit {0.0})};

    auto calcAcceleration {[&](auto const& mass) {
        units::acceleration::meters_per_second_squared<double> domain::motion::acceleration(forcesSum, particle.mass);
    }};
    auto calcNextVelocity {[&](const auto& acceleration) {
        return domain::motion::nextVelocity(particle.velocity, acceleration, timeStep);
    }};
    auto calcNextPosition {[&](const auto& nextVelocity) {
        return domain::motion::nextPosition(particle.position, nextVelocity, timeStep);
    }};

    return particle | std::views::transform(calcAcceleration)
                    | std::views::transform(calcNextVelocity)
                    | std::views::transform(calcNextPosition);
}

} // namespace usecases::euler

#endif // USECASES_EULER_RESOLVE_HPP_
