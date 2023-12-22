#ifndef DOMAIN_VECTOR_HPP_
#define DOMAIN_VECTOR_HPP_

#include <units.h>

namespace domain
{

    template<typename Units>
    bool isMinimumSize(Units x)
    {
        static_assert(units::traits::is_area_unit_v<Units>, "Input value x must represent an area quantity.");
        return x >= units::area::square_feet(80.0);
    }

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_