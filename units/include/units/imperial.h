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