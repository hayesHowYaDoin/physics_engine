#ifndef USECASES_PARTICLE_HPP_
#define USECASES_PARTICLE_HPP_

#include "physics_backend/euler/si.hpp"
#include "domain/vector.hpp"
#include "core/concepts.hpp"
#include <units.h>

#include <vector>

namespace usecases::euler
{

template<
    core::IsMassUnit Mass,
    core::IsLengthUnit Position,
    core::IsVelocityUnit Velocity,
    core::IsForceUnit Force>
struct EulerParticle
{
    Mass const mass;
    domain::PositionVector2D<Position> const position;
    domain::VelocityVector2D<Velocity> const velocity;
    std::vector<domain::ForceVector2D<Force>> const forces;
};

template <typename T>
struct is_euler_particle : std::false_type {};

template <
    core::IsMassUnit Mass,
    core::IsLengthUnit Position,
    core::IsVelocityUnit Velocity,
    core::IsForceUnit Force>
struct is_euler_particle<EulerParticle<Mass, Position, Velocity, Force>> : std::true_type
{
    using mass_type = Mass;
    using position_type = Position;
    using velocity_type = Velocity;
    using force_type = Force;
};

template<typename T>
concept IsEulerParticle = is_euler_particle<T>::value;

template<IsEulerParticle Particle>
[[nodiscard]] constexpr
auto buildEulerParticle(
    double mass,
    std::pair<double, double> const& position,
    std::pair<double, double> const& velocity,
    std::vector<std::pair<double, double>> const& forces = {})
{
    using Mass = typename is_euler_particle<Particle>::mass_type;
    using Position = typename is_euler_particle<Particle>::position_type;
    using Velocity = typename is_euler_particle<Particle>::velocity_type;
    using Force = typename is_euler_particle<Particle>::force_type;

    using PositionVector = domain::PositionVector2D<Position>;
    using VelocityVector = domain::VelocityVector2D<Velocity>;
    using ForceVector = domain::ForceVector2D<Force>;

    Mass massUnit {mass};
    PositionVector positionVector {Position{position.first}, Position{position.second}};
    VelocityVector velocityVector {Velocity{velocity.first}, Velocity{velocity.second}};

    std::vector<ForceVector> forceVectors;
    for(auto const& force : forces)
    {
        forceVectors.push_back({Force{force.first}, Force{force.second}});
    }

    return Particle {
        .mass = massUnit,
        .position = positionVector,
        .velocity = velocityVector,
        .forces = forceVectors};
}

} // namespace usecases::euler

#endif // USECASES_PARTICLE_HPP_