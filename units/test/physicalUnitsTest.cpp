/*  Copyright 2018. All rights reserved by the author.
 *  Author: Anurag Jakhotia <anuragjakhotia@gmail.com>
 */

#include <units/si.h>
#include <units/imperial.h>
#include <gtest/gtest.h>

namespace cppYard
{
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
	using MetresInchesConverter = PhysicalUnitsConversionHelper<MetresPhysicalUnit, InchesPhysicalUnit, double>;

	static_assert(std::is_same<MetresPhysicalUnit, typename MetresInchesConverter::LhsPhysicalUnits>::value,
				  "LhsPhysicalUnits is incorrectly assigned for @class PhysicalUnitsConversionHelper");

	static_assert(std::is_same<InchesPhysicalUnit, typename MetresInchesConverter::RhsPhysicalUnits>::value,
				  "RhsPhysicalUnits is incorrectly assigned for @class PhysicalUnitsConversionHelper");

	static_assert(std::is_same<double, typename MetresInchesConverter::FloatType>::value,
				  "Float is incorrectly assigned for @class PhysicalUnitsConversionHelper");

	static_assert(std::is_same<MetresInchesConverter, typename MetresInchesConverter::SelfType>::value,
				  "SelfType is incorrectly assigned for @class PhysicalUnitsConversionHelper");

	static_assert(std::is_same<std::ratio<127, 5000>, typename MetresInchesConverter::Result>::value,
				  "Result is incorrectly computed in @class PhysicalUnitsConversionHelper");

	static_assert(MetresInchesConverter::kFloatRatio == 0.0254,
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
				  "Dimension of the resulting physical unit is incorrcetly computed in @class MultiplyPhysicalUnits");

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
				  "Dimension of the resulting physical unit is incorrcetly computed in @class DividePhysicalUnits");

	static_assert(std::is_same<std::ratio<100000000, 45359237>,
						  typename Result::Scale>::value,
				  "Scale of the resulting physical unit is incorrectly computed in @class DividePhysicalUnits");
}

} // End of namespace units.
} // End of namespace cppYard.
