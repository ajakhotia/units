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
#include <units/si.h>
#include <units/imperial.h>
#include <gtest/gtest.h>

namespace units
{

TEST(PhysicalUnits, StaticChecks)
{
    using PrimeNumberDimensions = PhysicalDimensions<
            std::ratio<1, 2>, std::ratio<3, 5>, std::ratio<7, 11>, std::ratio<13, 17>,
            std::ratio<19, 23>, std::ratio<29, 31>, std::ratio<37, 41>>;

    using PrimeNumberUnits = PhysicalUnits<PrimeNumberDimensions, std::ratio<43, 47>>;

    static_assert(std::is_same<PrimeNumberDimensions, typename PrimeNumberUnits::PhysicalDimensions>::value,
                  "Physical dimensions are incorrectly assigned for @class PhysicalUnits");

    static_assert(std::is_same<std::ratio<43, 47>, typename PrimeNumberUnits::Scale>::value,
                  "Scale is incorrectly assigned for @class PhysicalUnits");

    static_assert(std::is_same<PrimeNumberUnits, typename PrimeNumberUnits::SelfType>::value,
                  "SelfType is incorrectly assigned for @class PhysicalUnits");
}

TEST(PhysicalUnitsConversionHelper, StaticChecks)
{
    using FeetInchesConverter = PhysicalUnitsConversionHelper<FeetPhysicalUnit, InchesPhysicalUnit, double>;

    static_assert(std::is_same<FeetPhysicalUnit, typename FeetInchesConverter::LhsPhysicalUnits>::value,
                  "LhsPhysicalUnits is incorrectly assigned for @class PhysicalUnitsConversionHelper");

    static_assert(std::is_same<InchesPhysicalUnit, typename FeetInchesConverter::RhsPhysicalUnits>::value,
                  "RhsPhysicalUnits is incorrectly assigned for @class PhysicalUnitsConversionHelper");

    static_assert(std::is_same<double, typename FeetInchesConverter::FloatType>::value,
                  "Float is incorrectly assigned for @class PhysicalUnitsConversionHelper");

    static_assert(std::is_same<FeetInchesConverter, typename FeetInchesConverter::SelfType>::value,
                  "SelfType is incorrectly assigned for @class PhysicalUnitsConversionHelper");

    static_assert(std::is_same<std::ratio<1, 12>, typename FeetInchesConverter::Result>::value,
                  "Result is incorrectly computed in @class PhysicalUnitsConversionHelper");

    static_assert(FeetInchesConverter::kFloatRatio == 1.0 / 12.0,
                  "kFloatRatio has been incorrectly computed in @class PhysicalUnitsConversionHelper"

    );
}

TEST(MultiplyPhysicalUnits, StaticChecks)
{
    using MultiplyMeterPoundsUnits = MultiplyPhysicalUnits<MetresPhysicalUnit, PoundsPhysicalUnit>;

    static_assert(std::is_same<MetresPhysicalUnit, typename MultiplyMeterPoundsUnits::LhsPhysicalUnits>::value,
                  "LhsPhysicalUnits is incorrectly assigned in @class MultiplyPhysicalUnits");

    static_assert(std::is_same<PoundsPhysicalUnit, typename MultiplyMeterPoundsUnits::RhsPhysicalUnits>::value,
                  "RhsPhysicalUnits is incorrectly assigned in @class MultiplyPhysicalUnits");

    static_assert(std::is_same<MultiplyMeterPoundsUnits, typename MultiplyMeterPoundsUnits::SelfType>::value,
                  "SelfType is incorrectly assigned in @class MultiplyPhysicalUnits");

    using Result = typename MultiplyMeterPoundsUnits::Result;

    static_assert(std::is_same<typename MultiplyPhysicalDimensions<Length, Mass>::Result,
                          typename Result::PhysicalDimensions>::value,
                  "Dimension of the resulting physical unit is incorrectly computed in @class MultiplyPhysicalUnits");

    static_assert(std::is_same<std::ratio<45359237, 100000000>,
                          typename Result::Scale>::value,
                  "Scale of the resulting physical unit is incorrectly computed in @class MultiplyPhysicalUnits");
}


TEST(DividePhysicalUnits, StaticChecks)
{
    using DivideMeterPoundsUnits = DividePhysicalUnits<MetresPhysicalUnit, PoundsPhysicalUnit>;

    static_assert(std::is_same<MetresPhysicalUnit, typename DivideMeterPoundsUnits::LhsPhysicalUnits>::value,
                  "LhsPhysicalUnits is incorrectly assigned in @class DividePhysicalUnits");

    static_assert(std::is_same<PoundsPhysicalUnit, typename DivideMeterPoundsUnits::RhsPhysicalUnits>::value,
                  "RhsPhysicalUnits is incorrectly assigned in @class DividePhysicalUnits");

    static_assert(std::is_same<DivideMeterPoundsUnits, typename DivideMeterPoundsUnits::SelfType>::value,
                  "SelfType is incorrectly assigned in @class DividePhysicalUnits");


    using Result = typename DivideMeterPoundsUnits::Result;

    static_assert(std::is_same<typename DividePhysicalDimensions<Length, Mass>::Result,
                          typename Result::PhysicalDimensions>::value,
                  "Dimension of the resulting physical unit is incorrectly computed in @class DividePhysicalUnits");

    static_assert(std::is_same<std::ratio<100000000, 45359237>,
                          typename Result::Scale>::value,
                  "Scale of the resulting physical unit is incorrectly computed in @class DividePhysicalUnits");
}

} // End of namespace units.
