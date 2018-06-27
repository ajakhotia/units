/*  Copyright 2016. All rights reserved by the author.
 *  Author: Anurag Jakhotia <anuragjakhotia@gmail.com>
 */

#include <units/si.h>
#include <units/imperial.h>
#include <gtest/gtest.h>

namespace cppYard
{
namespace units
{

template<typename TestDimension, intmax_t LN, intmax_t LD, intmax_t MN, intmax_t MD, intmax_t TN, intmax_t TD,
		intmax_t IN, intmax_t ID, intmax_t KN, intmax_t KD, intmax_t NN, intmax_t ND, intmax_t JN, intmax_t JD>
class AssertExponentsOfPhysicalDimensions
{
public:

	static constexpr const bool exponentMatched{(TestDimension::L::num == LN) && (TestDimension::L::den == LD) &&
												(TestDimension::M::num == MN) && (TestDimension::M::den == MD) &&
												(TestDimension::T::num == TN) && (TestDimension::T::den == TD) &&
												(TestDimension::I::num == IN) && (TestDimension::I::den == ID) &&
												(TestDimension::K::num == KN) && (TestDimension::K::den == KD) &&
												(TestDimension::N::num == NN) && (TestDimension::N::den == ND) &&
												(TestDimension::J::num == JN) && (TestDimension::J::den == JD)};

	/// Deleted constructor and destructors.
	AssertExponentsOfPhysicalDimensions() = delete;

	AssertExponentsOfPhysicalDimensions(const AssertExponentsOfPhysicalDimensions&) = delete;

	AssertExponentsOfPhysicalDimensions(AssertExponentsOfPhysicalDimensions&&) = delete;

	~AssertExponentsOfPhysicalDimensions() = delete;

private:
	static_assert((TestDimension::L::num == LN) && (TestDimension::L::den == LD),
				  "Exponent of length is incorrectly assigned in @class PhysicalDimensions.");

	static_assert((TestDimension::M::num == MN) && (TestDimension::M::den == MD),
				  "Exponent of mass is incorrectly assigned in @class PhysicalDimensions.");

	static_assert((TestDimension::T::num == TN) && (TestDimension::T::den == TD),
				  "Exponent of time is incorrectly assigned in @class PhysicalDimensions.");

	static_assert((TestDimension::I::num == IN) && (TestDimension::I::den == ID),
				  "Exponent of electric current is incorrectly assigned in @class PhysicalDimensions.");

	static_assert((TestDimension::K::num == KN) && (TestDimension::K::den == KD),
				  "Exponent of temperature is incorrectly assigned in @class PhysicalDimensions.");

	static_assert((TestDimension::N::num == NN) && (TestDimension::N::den == ND),
				  "Exponent of amount of substance is incorrectly assigned in @class PhysicalDimensions.");

	static_assert((TestDimension::J::num == JN) && (TestDimension::J::den == JD),
				  "Exponent of luminous intensity is incorrectly assigned in @class PhysicalDimensions.");
};

TEST(PhysicalDimensions, StaticTests)
{
	// Create a physical dimension with all prime number and test for the exponent for each
	// physical dimension.
	using PrimeNumberDimensions = PhysicalDimensions<
			std::ratio<1, 2>, std::ratio<3, 5>, std::ratio<7, 11>, std::ratio<13, 17>,
			std::ratio<19, 23>, std::ratio<29, 31>, std::ratio<37, 41>>;

	using Assertion = AssertExponentsOfPhysicalDimensions<PrimeNumberDimensions,
			1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41>;

	static_assert(std::is_same<PrimeNumberDimensions, typename PrimeNumberDimensions::SelfType>::value,
				  "SelfType is incorrectly assigned for @class PhysicalDimensions.");

	static_assert(Assertion::exponentMatched, "Physical dimensions exponent mis-matched.");
}

TEST(MultiplyPhysicalDimensions, StaticTests)
{
	using MultiplyLengthAndTime = MultiplyPhysicalDimensions<Length, Time>;

	static_assert(std::is_same<Length, typename MultiplyLengthAndTime::LhsPhysicalDimensions>::value,
				  "LhsPhysicalDimensions is incorrectly assigned for @class MultiplyPhysicalDimensions.");
	static_assert(std::is_same<Time, typename MultiplyLengthAndTime::RhsPhysicalDimensions>::value,
				  "RhsPhysicalDimensions is incorrectly assigned for @class MultiplyPhysicalDimensions.");
	static_assert(std::is_same<MultiplyLengthAndTime, typename MultiplyLengthAndTime::SelfType>::value,
				  "SelfType is incorrectly assigned for @class MultiplyPhysicalDimensions.");
}

TEST(MultiplyPhysicalDimensions, ResultExponentChecks)
{
	using SquaredAngle = typename MultiplyPhysicalDimensions<Angle, Angle>::Result;
	using AssertSquaredAngle = AssertExponentsOfPhysicalDimensions<SquaredAngle,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertSquaredAngle::exponentMatched, "Physical dimensions exponent mis-matched.");


	using SquaredLength = typename MultiplyPhysicalDimensions<Length, Length>::Result;
	using AssertSquaredLength = AssertExponentsOfPhysicalDimensions<SquaredLength,
			2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertSquaredLength::exponentMatched, "Physical dimensions exponent mis-matched.");


	using SquaredMass = typename MultiplyPhysicalDimensions<Mass, Mass>::Result;
	using AssertSquaredMass = AssertExponentsOfPhysicalDimensions<SquaredMass,
			0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertSquaredMass::exponentMatched, "Physical dimensions exponent mis-matched.");


	using SquaredTime = typename MultiplyPhysicalDimensions<Time, Time>::Result;
	using AssertSquaredTime = AssertExponentsOfPhysicalDimensions<SquaredTime,
			0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertSquaredTime::exponentMatched, "Physical dimensions exponent mis-matched.");


	using SquaredCurrent = typename MultiplyPhysicalDimensions<Current, Current>::Result;
	using AssertSquaredCurrent = AssertExponentsOfPhysicalDimensions<SquaredCurrent,
			0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertSquaredCurrent::exponentMatched, "Physical dimensions exponent mis-matched.");


	using SquaredTemperature = typename MultiplyPhysicalDimensions<Temperature, Temperature>::Result;
	using AssertSquaredTemperature = AssertExponentsOfPhysicalDimensions<SquaredTemperature,
			0, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1>;
	static_assert(AssertSquaredTemperature::exponentMatched, "Physical dimensions exponent mis-matched.");


	using SquaredSubstance = typename MultiplyPhysicalDimensions<Substance, Substance>::Result;
	using AssertSquaredSubstance = AssertExponentsOfPhysicalDimensions<SquaredSubstance,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1>;
	static_assert(AssertSquaredSubstance::exponentMatched, "Physical dimensions exponent mis-matched.");


	using SquaredLuminousIntensity = typename MultiplyPhysicalDimensions<LuminousIntensity, LuminousIntensity>::Result;
	using AssertSquaredLuminousIntensity = AssertExponentsOfPhysicalDimensions<SquaredLuminousIntensity,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1>;
	static_assert(AssertSquaredLuminousIntensity::exponentMatched, "Physical dimensions exponent mis-matched.");
}

TEST(DividePhysicalDimensions, StaticTests)
{
	using DivideLengthAndTime = DividePhysicalDimensions<Length, Time>;

	static_assert(std::is_same<Length, typename DivideLengthAndTime::LhsPhysicalDimensions>::value,
				  "LhsPhysicalDimensions is incorrectly assigned for @class DividePhysicalDimensions.");
	static_assert(std::is_same<Time, typename DivideLengthAndTime::RhsPhysicalDimensions>::value,
				  "RhsPhysicalDimensions is incorrectly assigned for @class DividePhysicalDimensions.");
	static_assert(std::is_same<DivideLengthAndTime, typename DivideLengthAndTime::SelfType>::value,
				  "SelfType is incorrectly assigned for @class DividePhysicalDimensions.");
}

TEST(DividePhysicalDimensions, ResultExponentChecks)
{
	using AngleOverAngle = typename DividePhysicalDimensions<Angle, Angle>::Result;
	using AssertAngleOverAngle = AssertExponentsOfPhysicalDimensions<AngleOverAngle,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertAngleOverAngle::exponentMatched, "Physical dimensions exponent mis-matched.");


	using AngleOverLength = typename DividePhysicalDimensions<Angle, Length>::Result;
	using AssertAngleOverLength = AssertExponentsOfPhysicalDimensions<AngleOverLength,
			-1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertAngleOverLength::exponentMatched, "Physical dimensions exponent mis-matched.");


	using AngleOverMass = typename DividePhysicalDimensions<Angle, Mass>::Result;
	using AssertAngleOverMass = AssertExponentsOfPhysicalDimensions<AngleOverMass,
			0, 1, -1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertAngleOverMass::exponentMatched, "Physical dimensions exponent mis-matched.");


	using AngleOverTime = typename DividePhysicalDimensions<Angle, Time>::Result;
	using AssertAngleOverTime = AssertExponentsOfPhysicalDimensions<AngleOverTime,
			0, 1, 0, 1, -1, 1, 0, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertAngleOverTime::exponentMatched, "Physical dimensions exponent mis-matched.");


	using AngleOverCurrent = typename DividePhysicalDimensions<Angle, Current>::Result;
	using AssertAngleOverCurrent = AssertExponentsOfPhysicalDimensions<AngleOverCurrent,
			0, 1, 0, 1, 0, 1, -1, 1, 0, 1, 0, 1, 0, 1>;
	static_assert(AssertAngleOverCurrent::exponentMatched, "Physical dimensions exponent mis-matched.");


	using AngleOverTemperature = typename DividePhysicalDimensions<Angle, Temperature>::Result;
	using AssertAngleOverTemperature = AssertExponentsOfPhysicalDimensions<AngleOverTemperature,
			0, 1, 0, 1, 0, 1, 0, 1, -1, 1, 0, 1, 0, 1>;
	static_assert(AssertAngleOverTemperature::exponentMatched, "Physical dimensions exponent mis-matched.");


	using AngleOverSubstance = typename DividePhysicalDimensions<Angle, Substance>::Result;
	using AssertAngleOverSubstance = AssertExponentsOfPhysicalDimensions<AngleOverSubstance,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, -1, 1, 0, 1>;
	static_assert(AssertAngleOverSubstance::exponentMatched, "Physical dimensions exponent mis-matched.");


	using AngleOverLuminousIntensity = typename DividePhysicalDimensions<Angle, LuminousIntensity>::Result;
	using AssertAngleOverLuminousIntensity = AssertExponentsOfPhysicalDimensions<AngleOverLuminousIntensity,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, -1, 1>;
	static_assert(AssertAngleOverLuminousIntensity::exponentMatched, "Physical dimensions exponent mis-matched.");
}


} // End of namespace units.
} // End of namespace cppYard.
