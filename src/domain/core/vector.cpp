#include "domain/core/constants.hpp"
#include "domain/core/vector.hpp"

#include <cmath>

namespace domain
{

Vector2D::Vector2D(float magnitude, domain::Angle const& angle) :
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

float Vector2D::getMagnitude() const
{
    return m_magnitude;
}

domain::Angle Vector2D::getAngle() const
{
    return m_angle;
}

Vector2D Vector2D::operator+(Vector2D const& other) const
{
    auto [thisX, thisY] { getComponents(*this) };
    auto [otherX, otherY] { getComponents(other) };

    float resultX { thisX + otherX };
    float resultY { thisY + otherY };

    float resultMagnitude { std::sqrt(resultX * resultX + resultY * resultY) };
    domain::Angle resultAngle { Angle::fromRadians(std::atan2(resultY, resultX)) };

    return Vector2D(resultMagnitude, std::move(resultAngle));
}

Vector2D Vector2D::operator-(Vector2D const& other) const
{
    auto [thisX, thisY] { getComponents(*this) };
    auto [otherX, otherY] { getComponents(other) };

    float resultX { thisX - otherX };
    float resultY { thisY - otherY };

    float resultMagnitude { std::sqrt(resultX * resultX + resultY * resultY) };
    domain::Angle resultAngle { Angle::fromRadians(std::atan2(resultY, resultX)) };

    return Vector2D(resultMagnitude, std::move(resultAngle));
}

Vector2D Vector2D::operator*(float scalar) const
{
    return Vector2D(m_magnitude * scalar, std::move(m_angle));
}

Vector2D Vector2D::operator/(float scalar) const
{
    return Vector2D(m_magnitude / scalar, std::move(m_angle));
}

domain::Coordinates2D Vector2D::getComponents(Vector2D const& vector)
{
    using namespace domain::math;

    float x { vector.getMagnitude() * cos(vector.getAngle()) };
    float y { vector.getMagnitude() * sin(vector.getAngle()) };

    return { x, y };
}

} // namespace domain
