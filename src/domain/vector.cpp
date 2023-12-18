#include "domain/math.hpp"
#include "domain/vector.hpp"

#include <cmath>

namespace domain
{

PhysicsVector::PhysicsVector(float magnitude, domain::Angle angle) :
    m_magnitude { magnitude },
    m_angle { angle }
{
    using namespace domain::literals;

    if(m_magnitude < 0.0f)
    {
        m_angle = m_angle + 180.0_deg;
        m_magnitude = std::abs(m_magnitude);
    }
}

float PhysicsVector::getMagnitude() const
{
    return m_magnitude;
}

domain::Angle PhysicsVector::getAngle() const
{
    return m_angle;
}

PhysicsVector PhysicsVector::operator+(PhysicsVector const& other) const
{
    auto [thisX, thisY] { getComponents(*this) };
    auto [otherX, otherY] { getComponents(other) };

    float resultX { thisX + otherX };
    float resultY { thisY + otherY };

    float resultMagnitude { std::sqrt(resultX * resultX + resultY * resultY) };
    domain::Angle resultAngle { Angle::fromRadians(std::atan2(resultY, resultX)) };

    return PhysicsVector(resultMagnitude, resultAngle);
}

PhysicsVector PhysicsVector::operator-(PhysicsVector const& other) const
{
    auto [thisX, thisY] { getComponents(*this) };
    auto [otherX, otherY] { getComponents(other) };

    float resultX { thisX - otherX };
    float resultY { thisY - otherY };

    float resultMagnitude { std::sqrt(resultX * resultX + resultY * resultY) };
    domain::Angle resultAngle { Angle::fromRadians(std::atan2(resultY, resultX)) };

    return PhysicsVector(resultMagnitude, resultAngle);
}

PhysicsVector PhysicsVector::operator*(float scalar) const
{
    return PhysicsVector(m_magnitude * scalar, m_angle);
}

PhysicsVector PhysicsVector::operator/(float scalar) const
{
    return PhysicsVector(m_magnitude / scalar, m_angle);
}

std::tuple<float, float> PhysicsVector::getComponents(PhysicsVector const& vector)
{
    float x { vector.getMagnitude() * domain::cos(vector.getAngle()) };
    float y { vector.getMagnitude() * domain::sin(vector.getAngle()) };

    return { x, y };
}

} // namespace domain
