/*  Copyright 2016. All rights reserved by the author.
 *  Author: Anurag Jakhotia <anuragjakhotia@gmail.com>
 */
#pragma once

#include "physicalQuantityVector.h"

namespace cppYard
{
namespace units
{

/// Physical units representing angles in SI system.
using RadiansPhysicalUnit = PhysicalUnits<Angle, std::ratio<1, 1>>;

/// Physical units representing length in SI units.
using MetresPhysicalUnit = PhysicalUnits<Length, std::ratio<1, 1>>;

/// Physical units representing mass in SI units.
using KilogramsPhysicalUnit = PhysicalUnits<Mass, std::ratio<1, 1>>;

/// Physical unit representing time in SI units.
using SecondsPhysicalUnit = PhysicalUnits<Time, std::ratio<1, 1>>;

/// Physical unit representing current / flow of charge in SI units.
using AmperesPhysicalUnit = PhysicalUnits<Current, std::ratio<1, 1>>;

/// Physical unit representing temperature difference in SI units.
using KelvinPhysicalUnit = PhysicalUnits<Temperature, std::ratio<1, 1>>;

/// Physical unit representing the amount of substance in SI units.
using MolesPhysicalUnits = PhysicalUnits<Substance, std::ratio<1, 1>>;

/// Physical unit representing the luminous intensity in SI units.
using CandelaPhysicalUnit = PhysicalUnits<LuminousIntensity, std::ratio<1, 1>>;

/// Radians
using Radians = PhysicalQuantityVector<RadiansPhysicalUnit, double>;

/// Meters
using Metres = PhysicalQuantityVector<MetresPhysicalUnit, double>;

/// Kilograms
using Kilograms = PhysicalQuantityVector<KilogramsPhysicalUnit, double>;

/// Seconds
using Seconds = PhysicalQuantityVector<SecondsPhysicalUnit, double>;

/// Ampere
using Ampere = PhysicalQuantityVector<AmperesPhysicalUnit, double>;

/// Kelvin temperature difference.
using KelvinTemperatureDifference = PhysicalQuantityVector<KelvinPhysicalUnit, double>;

/// Moles
using Moles = PhysicalQuantityVector<MolesPhysicalUnits, double>;

/// Candela
using Candela = PhysicalQuantityVector<CandelaPhysicalUnit, double>;

} // End of namespace units.
} // End of namespace cppYard.