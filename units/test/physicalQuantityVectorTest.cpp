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

	static_assert(std::is_same<Length, typename Metres::PhysicalDimensions>::value,
				  "PhysicalDimensions is incorrectly assigned in @class PhysicalQuantityVector.");

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

	EXPECT_EQ(196.85039370, i1.scalar());
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

TEST(PhysicalQuantityVector, HomogenousSelfAddition)
{
	const Metres m1(5.0);
	Metres m2(12.0);

	m2 += m1;

	EXPECT_EQ(17.0, m2.scalar());
}

TEST(PhysicalQuantityVector, HeterogenousSelfAddition)
{
	Metres m1(5.0);
	const Inches i1(30.0);
	const PhysicalQuantityVector<InchesPhysicalUnit, float> i2(7.f);

	m1 += i1;

	EXPECT_DOUBLE_EQ(5.762, m1.scalar());
}

TEST(PhysicalQuantityVector, HomogenousSelfSubtraction)
{
	const Metres m1(5.0);
	Metres m2(12.0);

	m2 -= m1;

	EXPECT_EQ(7.0, m2.scalar());
}

TEST(PhysicalQuantityVector, HeterogenousSelfSubtraction)
{
	Metres m1(5.0);
	const Inches i1(30.0);
	const PhysicalQuantityVector<InchesPhysicalUnit, float> i2(7.f);

	m1 -= i1;

	EXPECT_DOUBLE_EQ(4.283, m1.scalar());
}

} // End of namespace units.
} // End of namespace cppYard.
