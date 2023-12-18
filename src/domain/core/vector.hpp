#ifndef DOMAIN_VECTOR_HPP
#define DOMAIN_VECTOR_HPP

#include "domain/core/angle.hpp"
#include "domain/core/coordinates.hpp"

#include <tuple>

namespace domain
{

class Vector2D
{
public:
    Vector2D(float magnitude, Angle const& angle);

    float getMagnitude() const;

    domain::Angle getAngle() const;

    Vector2D operator+(const Vector2D& other) const;

    Vector2D operator-(const Vector2D& other) const;

    Vector2D operator*(float scalar) const;

    Vector2D operator/(float scalar) const;
    
    static domain::Coordinates2D getComponents(Vector2D const& vector);

private:
    float m_magnitude;
    domain::Angle m_angle;
};

} // namespace domain

#endif // DOMAIN_VECTOR_HPP
