#ifndef DOMAIN_VECTOR_HPP
#define DOMAIN_VECTOR_HPP

#include "domain/core/angle.hpp"

#include <tuple>

namespace domain
{

class PhysicsVector
{
public:
    PhysicsVector(float magnitude, domain::Angle const& angle);

    float getMagnitude() const;

    domain::Angle getAngle() const;

    PhysicsVector operator+(const PhysicsVector& other) const;

    PhysicsVector operator-(const PhysicsVector& other) const;

    PhysicsVector operator*(float scalar) const;

    PhysicsVector operator/(float scalar) const;
    
    static std::tuple<float, float> getComponents(PhysicsVector const& vector);

private:
    float m_magnitude;
    domain::Angle m_angle;
};

} // namespace domain

#endif // DOMAIN_VECTOR_HPP
