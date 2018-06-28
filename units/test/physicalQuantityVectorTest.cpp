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

TEST(PhysicalQuantityVector, StaticChecks)
{
	static_assert(std::is_same<MetresPhysicalUnit, typename Metres::PhysicalUnits>::value,
				  "PhysicalUnits is incorrectly assigned in @class PhysicalQuantityVector.");

	static_assert(std::is_same<double, typename Metres::FloatType>::value,
				  "FloatType is incorrectly assigned in @class PhysicalQuantityVector.");

	static_assert(std::is_same<Metres, typename Metres::SelfType>::value,
				  "SelfType is incorrectly assigned in @class PhysicalQuantityVector.");
}

TEST(PhysicalQuantityVector, DefaultConstruction)
{
	const Metres m;
	EXPECT_EQ(0.0, m.scalar());
}

TEST(PhysicalQuantityVector, Construction)
{
	const Metres m(5.0);
	EXPECT_EQ(5.0, m.scalar());
}

TEST(PhysicalQuantityVector, CopyConstruction)
{
	const Metres m1(5.0);
	const Metres m2(m1);

	EXPECT_EQ(m1.scalar(), m2.scalar());
}

TEST(PhysicalQuantityVector, MoveConstruction)
{
	Metres m1(5.0);
	const Metres m2(std::move(m1));

	EXPECT_EQ(5.0, m2.scalar());
}

TEST(PhysicalQuantityVector, ConvertConstruction)
{
	const Metres m1(5.0);
	const Inches i1(m1);

	EXPECT_EQ(5.0 / 0.0254, i1.scalar());
}

TEST(PhysicalQuantityVector, CopyAssignment)
{
	Metres m1(5.0);
	Metres m2;
	m2 = m1;

	EXPECT_EQ(5.0, m2.scalar());
}

TEST(PhysicalQuantityVector, MoveAssignment)
{
	Metres m1(5.0);
	Metres m2;
	m2 = std::move(m1);

	EXPECT_EQ(5.0, m2.scalar());
}

TEST(PhysicalQuantityVector, AdditionAssignment)
{
	const Metres m1(5.0);
	Metres m2(12.0);

	m2 += m1;

	EXPECT_EQ(17.0, m2.scalar());
}

TEST(PhysicalQuantityVector, HeterogenousAdditionAssignment)
{
	Metres m1(5.0);
	const Inches i1(30.0);
	const PhysicalQuantityVector<InchesPhysicalUnit, float> i2(7.f);

	m1 += i1;

	EXPECT_DOUBLE_EQ(5.762, m1.scalar());
}

TEST(PhysicalQuantityVector, SubstrationAssignment)
{
	const Metres m1(5.0);
	Metres m2(12.0);

	m2 -= m1;

	EXPECT_EQ(7.0, m2.scalar());
}

TEST(PhysicalQuantityVector, HeterogenousSubstractionAssignment)
{
	Metres m1(5.0);
	const Inches i1(30.0);
	const PhysicalQuantityVector<InchesPhysicalUnit, float> i2(7.f);

	m1 -= i1;

	EXPECT_DOUBLE_EQ(4.238, m1.scalar());
}

TEST(PhysicalQuantityVector, ScalarMultiplicationAssignment)
{
	Metres m1(5.0);
	m1 *= 4.0;
	EXPECT_EQ(20.0, m1.scalar());
}

TEST(PhysicalQuantityVector, ScalarDivisionOperator)
{
	Metres m1(5.0);
	m1 /= 4.0;
	EXPECT_EQ(1.25, m1.scalar());
}

TEST(PhysicalQunatityVector, PreIncrementOperator)
{
	Metres m1(3.0);
	EXPECT_EQ(4.0, (++m1).scalar());
}

TEST(PhysicalQunatityVector, PostIncrementOperator)
{
	Metres m1(3.0);
	EXPECT_EQ(3.0, (m1++).scalar());
	EXPECT_EQ(4.0, m1.scalar());
}

TEST(PhysicalQunatityVector, PreDecrementOperator)
{
	Metres m1(3.0);
	EXPECT_EQ(2.0, (--m1).scalar());
}


TEST(PhysicalQunatityVector, PostDecrementOperator)
{
	Metres m1(3.0);
	EXPECT_EQ(3.0, (m1--).scalar());
	EXPECT_EQ(2.0, m1.scalar());
}

TEST(PhysicalQunatityVector, Cast)
{
	const Metres m1(5.0);
	auto m2 = m1.cast<float>();

	EXPECT_EQ(5.f, m2.scalar());
	static_assert(std::is_same<decltype(m2)::FloatType, float>::value,
				  "Float representation of the returning type of cast() is incorrectly assigned");
}

TEST(PhysicalQuantityVector, Scalar)
{
	const Metres m1(3.0);
	EXPECT_EQ(3.0, m1.scalar());
}



TEST(PhysicalQuantityVector, AdditionOperator)
{
    const Metres m1(3.0);
    const Metres m2(5.0);

    const Metres  m3 = m1 + m2;

    EXPECT_EQ(8.0, m3.scalar());
}

TEST(PhysicalQuantityVector, HeterogenousAdditionOperator)
{
    const Metres m1(3.0);
    const Inches i1(5.0);

    const Metres m2 = m1 + i1;

    EXPECT_EQ(3.127, m2.scalar());
}


TEST(PhysicalQuantityVector, SubtractionOperator)
{
	const Metres m1(3.0);
	const Metres m2(5.0);

	const Metres  m3 = m1 - m2;

	EXPECT_EQ(-2.0, m3.scalar());
}

TEST(PhysicalQuantityVector, HeterogenousSubtractionOperator)
{
	const Metres m1(3.0);
	const Inches i1(5.0);

	const Metres m2 = m1 - i1;

	EXPECT_EQ(2.873, m2.scalar());
}

TEST(PhysicalQuantityVector, MultiplicationOperator)
{
	const Metres m1(4.0);
	const Inches i1(5.0);

	const auto area1 = m1 * i1;

	EXPECT_EQ(20.0, area1.scalar());
}

TEST(PhysicalQuantityVector, DivisionOperator)
{
	const Metres m1(4.0);
	const Inches i1(5.0);

	const auto area1 = m1 / i1;

	EXPECT_EQ(0.8, area1.scalar());
}

TEST(PhysicalQuantityVector, EqualityOperator)
{
	EXPECT_TRUE(Metres(5.0) == Metres(5.0));
	EXPECT_FALSE(Inches(3.0) == Inches(4.0));
}

TEST(PhysicalQuantityVector, HeterogeneousEqualityOperator)
{
	EXPECT_TRUE(Metres(0.0254) == Inches(1.0));
	EXPECT_FALSE(Metres(3.0) == Inches(3.0));
}

TEST(PhysicalQuantityVector, InequalityOperator)
{
	EXPECT_FALSE(Metres(5.0) != Metres(5.0));
	EXPECT_TRUE(Inches(3.0) != Inches(4.0));
}

TEST(PhysicalQuantityVector, HeterogeneousInequalityOperator)
{
	EXPECT_FALSE(Metres(0.0254) != Inches(1.0));
	EXPECT_TRUE(Metres(3.0) != Inches(3.0));
}

TEST(PhysicalQuantityVector, LesserThanInequalityOperator)
{
	EXPECT_FALSE(Metres(5.0) < Metres(4.0));
	EXPECT_FALSE(Metres(4.0) < Metres(4.0));
	EXPECT_TRUE(Metres(3.9) < Metres(4.0));
}

TEST(PhysicalQuantityVector, HeterogeneousLesserThanInequalityOperator)
{
	EXPECT_FALSE(Metres(0.0255) < Inches(1.0));
	EXPECT_FALSE(Metres(0.0254) < Inches(1.0));
	EXPECT_TRUE(Metres(0.0253) < Inches(1.0));
}

TEST(PhysicalQuantityVector, LesserThanOrEqualToInequalityOperator)
{
	EXPECT_FALSE(Metres(5.0) <= Metres(4.0));
	EXPECT_TRUE(Metres(4.0) <= Metres(4.0));
	EXPECT_TRUE(Inches(3.0) <= Inches(4.0));
}

TEST(PhysicalQuantityVector, HeterogeneousLesserThanOrEqualToInequalityOperator)
{
	EXPECT_FALSE(Metres(0.0255) <= Inches(1.0));
	EXPECT_TRUE(Metres(0.0254) <= Inches(1.0));
	EXPECT_TRUE(Metres(0.0253) <= Inches(1.0));
}

TEST(PhysicalQuantityVector, GreaterThanInequalityOperator)
{
	EXPECT_TRUE(Metres(5.0) > Metres(4.0));
	EXPECT_FALSE(Metres(4.0) > Metres(4.0));
	EXPECT_FALSE(Metres(3.9) > Metres(4.0));
}

TEST(PhysicalQuantityVector, HeterogeneousGreaterThanInequalityOperator)
{
	EXPECT_TRUE(Metres(0.0255) > Inches(1.0));
	EXPECT_FALSE(Metres(0.0254) > Inches(1.0));
	EXPECT_FALSE(Metres(0.0253) > Inches(1.0));
}

TEST(PhysicalQuantityVector, GreaterThanOrEqualToInequalityOperator)
{
	EXPECT_TRUE(Metres(5.0) >= Metres(4.0));
	EXPECT_TRUE(Metres(4.0) >= Metres(4.0));
	EXPECT_FALSE(Inches(3.0) >= Inches(4.0));
}

TEST(PhysicalQuantityVector, HeterogeneousGreaterThanOrEqualToInequalityOperator)
{
	EXPECT_TRUE(Metres(0.0255) >= Inches(1.0));
	EXPECT_TRUE(Metres(0.0254) >= Inches(1.0));
	EXPECT_FALSE(Metres(0.0253) >= Inches(1.0));
}

TEST(MultiplyPhysicalQuantityVector, StaticChecks)
{
	using MultiplyInchesAndPounds = MultiplyPhysicalQuantityVector<Inches, Pounds>;

	static_assert(std::is_same<Inches, typename MultiplyInchesAndPounds::LhsPhysicalQuantityVector>::value,
	              "LHS physical quantity vector is incorrectly assigned in @class "
	              " MultiplyPhysicalQuantityVector.");

	static_assert(std::is_same<Pounds, typename MultiplyInchesAndPounds::RhsPhysicalQuantityVector>::value,
	              "RHS physical quantity vector is incorrectly assigned in @class "
	              " MultiplyPhysicalQuantityVector.");

	static_assert(std::is_same<MultiplyInchesAndPounds, typename MultiplyInchesAndPounds::SelfType>::value,
	              "Self type is incorrectly assigned in @class MultiplyPhysicalQuantityVector.");

	using ResultAreaType = typename MultiplyInchesAndPounds::Result;
	using LengthMassPhysicalDimensions = typename MultiplyPhysicalDimensions<Length, Mass>::Result;

	static_assert(std::is_same<LengthMassPhysicalDimensions,
			                   typename ResultAreaType::PhysicalUnits::PhysicalDimensions>::value,
	              "Resulting dimension of the product of physical quantity vectors is incorrect.");

	EXPECT_EQ(0.011521246198, static_cast<double>(ResultAreaType::PhysicalUnits::Scale::num) /
	                          static_cast<double>(ResultAreaType::PhysicalUnits::Scale::den));
}

TEST(DividePhysicalQuantityVector, StaticChecks)
{
	using DivideInchesAndPounds = DividePhysicalQuantityVector<Inches, Pounds>;

	static_assert(std::is_same<Inches, typename DivideInchesAndPounds::LhsPhysicalQuantityVector>::value,
	              "LHS physical quantity vector is incorrectly assigned in @class "
	              " DividePhysicalQuantityVector.");

	static_assert(std::is_same<Pounds, typename DivideInchesAndPounds::RhsPhysicalQuantityVector>::value,
	              "RHS physical quantity vector is incorrectly assigned in @class "
	              " DividePhysicalQuantityVector.");

	static_assert(std::is_same<DivideInchesAndPounds, typename DivideInchesAndPounds::SelfType>::value,
	              "Self type is incorrectly assigned in @class DividePhysicalQuantityVector.");

	using ResultAreaType = typename DivideInchesAndPounds::Result;
	using LengthOverMassPhysicalDimensions = typename DividePhysicalDimensions<Length, Mass>::Result;

	static_assert(std::is_same<LengthOverMassPhysicalDimensions,
			                   typename ResultAreaType::PhysicalUnits::PhysicalDimensions>::value,
	              "Resulting dimension of the product of physical quantity vectors is incorrect.");

	EXPECT_EQ(0.055997414594958905503635345542,
	          static_cast<double>(ResultAreaType::PhysicalUnits::Scale::num) /
	          static_cast<double>(ResultAreaType::PhysicalUnits::Scale::den));
}

} // End of namespace units.
} // End of namespace cppYard.
