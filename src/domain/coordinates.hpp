#ifndef DOMAIN_COORDINATES_HPP_
#define DOMAIN_COORDINATES_HPP_

#include "domain/concepts.hpp"
#include <units.h>

namespace domain
{
    #include <units.h> // Add this line

    class Coordinates2D
    {
    public:
        template<LengthUnit Length>
        constexpr Coordinates2D(Length x, Length y): 
            m_x {x},
            m_y {y}
        {
            // Intentionally blank.
        }

        template<LengthUnit Length>
        [[nodiscard]] constexpr Length getX() const
        {
            return m_x;
        }

        template<LengthUnit Length>
        [[nodiscard]] constexpr Length getY() const
        {
            return m_y;
        }

    private:
        units::meters<double> m_x;
        units::meters<double> m_y;
    };

} // namespace domain

#endif // DOMAIN_COORDINATES_HPP_