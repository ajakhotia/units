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

} // End of namespace units.
} // End of namespace cppYard.
