#ifndef ADAPTERS_EULER_SI_HPP_
#define ADAPTERS_EULER_SI_HPP_

#include "physics_backend/euler/si.hpp"
#include "usecases/euler/particle.hpp"

namespace physics_backend::euler::si
{

using MassUnit = units::mass::kilograms<double>;
using PositionUnit = units::length::meters<double>;
using VelocityUnit = units::velocity::meters_per_second<double>;
using ForceUnit = units::force::newtons<double>;
using TimeUnit = units::time::seconds<double>;

using ParticleSI = usecases::euler::EulerParticle<MassUnit, PositionUnit, VelocityUnit, ForceUnit>;

struct Particle::Impl
{
    ParticleSI particle;
};

Particle::Particle(double mass, double x, double y, double vx, double vy) :
    m_pImpl {std::make_unique<Impl>(usecases::euler::buildEulerParticle<ParticleSI>(mass, {x, y}, {vx, vy}))}
{
    // Intentionally left blank.
}

Particle::~Particle() = default;

double Particle::getMass() const
{
    return m_pImpl->particle.mass.to<double>();
}

std::pair<double, double> Particle::getPosition() const
{
    double x {m_pImpl->particle.position.getX<PositionUnit>().to<double>()};
    double y {m_pImpl->particle.position.getY<PositionUnit>().to<double>()};

    return {x, y};
}

std::pair<double, double> Particle::getVelocity() const
{
    double x {m_pImpl->particle.velocity.getX<VelocityUnit>().to<double>()};
    double y {m_pImpl->particle.velocity.getY<VelocityUnit>().to<double>()};

    return {x, y};
}

// Particle step(Particle&& particle, uint32_t seconds)
// {
//     auto resolve = [timeStep](Particle const& particle) {
//         return usecases::euler::resolveMotion(particle, TimeUnit{timeStep});
//     };

//     return usecases::step(std::forward<Particle>(particle), resolve);
// }

} // namespace physics_backend::euler::si

#endif // ADAPTERS_EULER_SI_HPP_
