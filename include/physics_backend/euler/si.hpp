#ifndef PHYSICS_BACKEND_EULER_SI_H_
#define PHYSICS_BACKEND_EULER_SI_H_

#include <string>
#include <memory>

#include <units.h>

namespace physics_backend::euler::si
{

struct Particle
{
    Particle(double massKg, double x, double y, double vx, double vy);
    ~Particle();

    double getMass() const;
    std::pair<double, double> getPosition() const;
    std::pair<double, double> getVelocity() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

// Particle step(Particle&& particle, uint32_t seconds);

} // namespace physics_backend::euler::si

#endif // PHYSICS_BACKEND_EULER_SI_H_