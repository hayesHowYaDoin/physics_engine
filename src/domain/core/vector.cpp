#include "domain/core/constants.hpp"
#include "domain/core/vector.hpp"

#include <cmath>

namespace domain
{

PhysicsVector::PhysicsVector(float magnitude, domain::Angle const& angle) :
    m_magnitude { magnitude },
    m_angle { std::move(angle) }
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

    return PhysicsVector(resultMagnitude, std::move(resultAngle));
}

PhysicsVector PhysicsVector::operator-(PhysicsVector const& other) const
{
    auto [thisX, thisY] { getComponents(*this) };
    auto [otherX, otherY] { getComponents(other) };

    float resultX { thisX - otherX };
    float resultY { thisY - otherY };

    float resultMagnitude { std::sqrt(resultX * resultX + resultY * resultY) };
    domain::Angle resultAngle { Angle::fromRadians(std::atan2(resultY, resultX)) };

    return PhysicsVector(resultMagnitude, std::move(resultAngle));
}

PhysicsVector PhysicsVector::operator*(float scalar) const
{
    return PhysicsVector(m_magnitude * scalar, std::move(m_angle));
}

PhysicsVector PhysicsVector::operator/(float scalar) const
{
    return PhysicsVector(m_magnitude / scalar, std::move(m_angle));
}

std::tuple<float, float> PhysicsVector::getComponents(PhysicsVector const& vector)
{
    using namespace domain::math;

    float x { vector.getMagnitude() * cos(vector.getAngle()) };
    float y { vector.getMagnitude() * sin(vector.getAngle()) };

    return { x, y };
}

} // namespace domain
