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

#include <units/si.hpp>
#include <units/imperial.hpp>
#include <gtest/gtest.h>

namespace units
{


TEST(AffineQuantity, StaticChecks)
{
    static_assert(std::is_same<MetresPhysicalUnit, typename Metres::PhysicalUnits>::value,
                  "PhysicalUnits is incorrectly assigned in @class AffineQuantity.");

    static_assert(std::is_same<double, typename Metres::FloatType>::value,
                  "FloatType is incorrectly assigned in @class AffineQuantity.");

    static_assert(std::is_same<Metres, typename Metres::SelfType>::value,
                  "SelfType is incorrectly assigned in @class AffineQuantity.");
}


TEST(AffineQuantity, DefaultConstruction)
{
    const Metres m;
    EXPECT_EQ(0.0, m.scalar());
}


TEST(AffineQuantity, Construction)
{
    const Metres m(5.0);
    EXPECT_EQ(5.0, m.scalar());
}


TEST(AffineQuantity, CopyConstruction)
{
    const Metres m1(5.0);
    const Metres m2(m1);

    EXPECT_EQ(m1.scalar(), m2.scalar());
}


TEST(AffineQuantity, MoveConstruction)
{
    Metres m1(5.0);
    const Metres m2(std::move(m1));

    EXPECT_EQ(5.0, m2.scalar());
}


TEST(AffineQuantity, ConvertConstruction)
{
    const Metres m1(5.0);
    const Inches i1(m1);

    EXPECT_EQ(5.0 / 0.0254, i1.scalar());
}


TEST(AffineQuantity, CopyAssignment)
{
    Metres m1(5.0);
    Metres m2;
    m2 = m1;

    EXPECT_EQ(5.0, m2.scalar());
}


TEST(AffineQuantity, MoveAssignment)
{
    Metres m1(5.0);
    Metres m2;
    m2 = std::move(m1);

    EXPECT_EQ(5.0, m2.scalar());
}


TEST(AffineQuantity, AdditionAssignment)
{
    const Metres m1(5.0);
    Metres m2(12.0);

    m2 += m1;

    EXPECT_EQ(17.0, m2.scalar());
}


TEST(AffineQuantity, HeterogenousAdditionAssignment)
{
    Metres m1(5.0);
    const Inches i1(30.0);

    m1 += i1;

    EXPECT_DOUBLE_EQ(5.762, m1.scalar());
}


TEST(AffineQuantity, SubstrationAssignment)
{
    const Metres m1(5.0);
    Metres m2(12.0);

    m2 -= m1;

    EXPECT_EQ(7.0, m2.scalar());
}


TEST(AffineQuantity, HeterogenousSubstractionAssignment)
{
    Metres m1(5.0);
    const Inches i1(30.0);

    m1 -= i1;

    EXPECT_DOUBLE_EQ(4.238, m1.scalar());
}


TEST(AffineQuantity, ScalarMultiplicationAssignment)
{
    Metres m1(5.0);
    m1 *= 4.0;
    EXPECT_EQ(20.0, m1.scalar());
}


TEST(AffineQuantity, ScalarDivisionOperator)
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


TEST(AffineQuantity, Scalar)
{
    const Metres m1(3.0);
    EXPECT_EQ(3.0, m1.scalar());
}


TEST(AffineQuantity, AdditionOperator)
{
    const Metres m1(3.0);
    const Metres m2(5.0);

    const Metres m3 = m1 + m2;

    EXPECT_EQ(8.0, m3.scalar());
}


TEST(AffineQuantity, HeterogenousAdditionOperator)
{
    const Metres m1(3.0);
    const Inches i1(5.0);

    const Metres m2 = m1 + i1;

    EXPECT_EQ(3.127, m2.scalar());
}


TEST(AffineQuantity, SubtractionOperator)
{
    const Metres m1(3.0);
    const Metres m2(5.0);

    const Metres m3 = m1 - m2;

    EXPECT_EQ(-2.0, m3.scalar());
}


TEST(AffineQuantity, HeterogenousSubtractionOperator)
{
    const Metres m1(3.0);
    const Inches i1(5.0);

    const Metres m2 = m1 - i1;

    EXPECT_EQ(2.873, m2.scalar());
}


TEST(AffineQuantity, MultiplicationOperator)
{
    const Metres m1(4.0);
    const Inches i1(5.0);

    const auto area1 = m1 * i1;

    EXPECT_EQ(20.0, area1.scalar());
}


TEST(AffineQuantity, DivisionOperator)
{
    const Metres m1(4.0);
    const Inches i1(5.0);

    const auto area1 = m1 / i1;

    EXPECT_EQ(0.8, area1.scalar());
}


TEST(AffineQuantity, EqualityOperator)
{
    EXPECT_TRUE(Metres(5.0) == Metres(5.0));
    EXPECT_FALSE(Inches(3.0) == Inches(4.0));
}


TEST(AffineQuantity, HeterogeneousEqualityOperator)
{
    EXPECT_TRUE(Metres(0.0254) == Inches(1.0));
    EXPECT_FALSE(Metres(3.0) == Inches(3.0));
}


TEST(AffineQuantity, InequalityOperator)
{
    EXPECT_FALSE(Metres(5.0) != Metres(5.0));
    EXPECT_TRUE(Inches(3.0) != Inches(4.0));
}


TEST(AffineQuantity, HeterogeneousInequalityOperator)
{
    EXPECT_FALSE(Metres(0.0254) != Inches(1.0));
    EXPECT_TRUE(Metres(3.0) != Inches(3.0));
}


TEST(AffineQuantity, LesserThanInequalityOperator)
{
    EXPECT_FALSE(Metres(5.0) < Metres(4.0));
    EXPECT_FALSE(Metres(4.0) < Metres(4.0));
    EXPECT_TRUE(Metres(3.9) < Metres(4.0));
}


TEST(AffineQuantity, HeterogeneousLesserThanInequalityOperator)
{
    EXPECT_FALSE(Metres(0.0255) < Inches(1.0));
    EXPECT_FALSE(Metres(0.0254) < Inches(1.0));
    EXPECT_TRUE(Metres(0.0253) < Inches(1.0));
}


TEST(AffineQuantity, LesserThanOrEqualToInequalityOperator)
{
    EXPECT_FALSE(Metres(5.0) <= Metres(4.0));
    EXPECT_TRUE(Metres(4.0) <= Metres(4.0));
    EXPECT_TRUE(Inches(3.0) <= Inches(4.0));
}


TEST(AffineQuantity, HeterogeneousLesserThanOrEqualToInequalityOperator)
{
    EXPECT_FALSE(Metres(0.0255) <= Inches(1.0));
    EXPECT_TRUE(Metres(0.0254) <= Inches(1.0));
    EXPECT_TRUE(Metres(0.0253) <= Inches(1.0));
}


TEST(AffineQuantity, GreaterThanInequalityOperator)
{
    EXPECT_TRUE(Metres(5.0) > Metres(4.0));
    EXPECT_FALSE(Metres(4.0) > Metres(4.0));
    EXPECT_FALSE(Metres(3.9) > Metres(4.0));
}


TEST(AffineQuantity, HeterogeneousGreaterThanInequalityOperator)
{
    EXPECT_TRUE(Metres(0.0255) > Inches(1.0));
    EXPECT_FALSE(Metres(0.0254) > Inches(1.0));
    EXPECT_FALSE(Metres(0.0253) > Inches(1.0));
}


TEST(AffineQuantity, GreaterThanOrEqualToInequalityOperator)
{
    EXPECT_TRUE(Metres(5.0) >= Metres(4.0));
    EXPECT_TRUE(Metres(4.0) >= Metres(4.0));
    EXPECT_FALSE(Inches(3.0) >= Inches(4.0));
}


TEST(AffineQuantity, HeterogeneousGreaterThanOrEqualToInequalityOperator)
{
    EXPECT_TRUE(Metres(0.0255) >= Inches(1.0));
    EXPECT_TRUE(Metres(0.0254) >= Inches(1.0));
    EXPECT_FALSE(Metres(0.0253) >= Inches(1.0));
}


} // End of namespace units.