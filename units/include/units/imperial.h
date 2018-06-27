/*  Copyright 2016. All rights reserved by the author.
 *  Author: Anurag Jakhotia <anuragjakhotia@gmail.com>
 */
#pragma once

#include "physicalQuantityVector.h"

namespace cppYard
{
namespace units
{

/// Physical units to measure angles in imperial system.

/// Physical units to measure lenght in imperial system.
using InchesPhysicalUnit = PhysicalUnits<Length, std::ratio<254, 10000>>;
using FeetPhysicalUnit = PhysicalUnits<Length, std::ratio<3048, 10000>>;

/// Physical units to measure mass in imperial system.
using PoundsPhysicalUnit = PhysicalUnits<Mass, std::ratio<45359237, 100000000>>;

/// Inches
using Inches = PhysicalQuantityVector<InchesPhysicalUnit, double>;

/// Feet.
using Feet = PhysicalQuantityVector<FeetPhysicalUnit, double>;

/// Pounds
using Pounds = PhysicalQuantityVector<PoundsPhysicalUnit, double>;

} // End of namespace units.
} // End of namespace cppYard