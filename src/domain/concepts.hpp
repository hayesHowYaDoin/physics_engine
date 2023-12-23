#ifndef DOMAIN_CONCEPTS_HPP_
#define DOMAIN_CONCEPTS_HPP_

#include <units.h>

namespace domain
{

    template<typename Number>
    concept NumberType = std::is_arithmetic_v<Number>;

    template<typename Units>
    concept AreaUnit = units::traits::is_area_unit_v<Units>;

    template<typename Units>
    concept LengthUnit = units::traits::is_length_unit_v<Units>;

    template<typename Units>
    concept VolumeUnit = units::traits::is_volume_unit_v<Units>;

    template<typename Units>
    concept MassUnit = units::traits::is_mass_unit_v<Units>;

    template<typename Units>
    concept TimeUnit = units::traits::is_time_unit_v<Units>;

    template<typename Units>
    concept VelocityUnit = units::traits::is_velocity_unit_v<Units>;

    template<typename Units>
    concept AccelerationUnit = units::traits::is_acceleration_unit_v<Units>;

    template<typename Units>
    concept ForceUnit = units::traits::is_force_unit_v<Units>;

    template<typename Units>
    concept AngleUnit = units::traits::is_angle_unit_v<Units>;

    template<typename Units>
    concept MagnitudeUnit = units::traits::is_length_unit_v<Units> ||
                            units::traits::is_force_unit_v<Units> ||
                            units::traits::is_velocity_unit_v<Units> ||
                            units::traits::is_acceleration_unit_v<Units>;


} // namespace domain

#endif // DOMAIN_CONCEPTS_HPP_