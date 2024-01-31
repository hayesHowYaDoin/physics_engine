#ifndef USECASES_PARTICLE_HPP_
#define USECASES_PARTICLE_HPP_

#include "domain/vector.hpp"
#include "core/concepts.hpp"
#include <units.h>

#include <vector>

namespace usecases
{

struct EulerParticle
{
    units::mass::kilograms<double> const mass;
    domain::PositionVector2D<units::length::meters<double>> const position;
    domain::VelocityVector2D<units::velocity::meters_per_second<double>> const velocity;
    std::vector<domain::ForceVector2D<units::force::newtons<double>>> const forces;
};

} // namespace usecases

#endif // USECASES_PARTICLE_HPP_