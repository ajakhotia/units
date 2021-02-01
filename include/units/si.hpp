/**
 * MIT License
 *
 * Copyright (c) 2018 Anurag Jakhotia
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include "affineQuantity.hpp"

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
using Radians = AffineQuantity<RadiansPhysicalUnit, double>;

/// Meters
using Metres = AffineQuantity<MetresPhysicalUnit, double>;

/// Kilograms
using Kilograms = AffineQuantity<KilogramsPhysicalUnit, double>;

/// Seconds
using Seconds = AffineQuantity<SecondsPhysicalUnit, double>;

/// Ampere
using Ampere = AffineQuantity<AmperesPhysicalUnit, double>;

/// Kelvin temperature difference.
using KelvinTemperatureDifference = AffineQuantity<KelvinPhysicalUnit, double>;

/// Moles
using Moles = AffineQuantity<MolesPhysicalUnits, double>;

/// Candela
using Candela = AffineQuantity<CandelaPhysicalUnit, double>;

} // End of namespace units.