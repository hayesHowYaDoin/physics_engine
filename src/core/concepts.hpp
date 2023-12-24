#ifndef CORE_CONCEPTS_HPP_
#define CORE_CONCEPTS_HPP_

#include <units.h>

namespace core
{

template<typename UnitType>
concept IsUnit = units::traits::is_unit_v<UnitType>;

template<typename UnitType>
concept IsNumberType = std::is_arithmetic_v<UnitType>;

template<typename UnitType>
concept IsAreaUnit = units::traits::is_area_unit_v<UnitType>;

template<typename UnitType>
concept IsLengthUnit = units::traits::is_length_unit_v<UnitType>;

template<typename UnitType>
concept IsVolumeUnit = units::traits::is_volume_unit_v<UnitType>;

template<typename UnitType>
concept IsMassUnit = units::traits::is_mass_unit_v<UnitType>;

template<typename UnitType>
concept IsTimeUnit = units::traits::is_time_unit_v<UnitType>;

template<typename UnitType>
concept IsVelocityUnit = units::traits::is_velocity_unit_v<UnitType>;

template<typename UnitType>
concept IsAccelerationUnit = units::traits::is_acceleration_unit_v<UnitType>;

template<typename UnitType>
concept IsForceUnit = units::traits::is_force_unit_v<UnitType>;

template<typename UnitType>
concept IsAngleUnit = units::traits::is_angle_unit_v<UnitType>;

template<typename UnitType>
concept IsMagnitudeUnit = units::traits::is_length_unit_v<UnitType> ||
                          units::traits::is_force_unit_v<UnitType> ||
                          units::traits::is_velocity_unit_v<UnitType> ||
                          units::traits::is_acceleration_unit_v<UnitType>;


} // namespace domain

#endif // CORE_CONCEPTS_HPP_