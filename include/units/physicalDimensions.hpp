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

#include <ratio>

namespace units
{


/// Table of primary physical dimensions.
///
///  ---------------------------------------------------------
///  |   Physical Unit       |   SI units    |   DIMENSION   |
///  ---------------------------------------------------------
///  |   Length              |   meter       |   L           |
///  |   Mass                |   kilogram    |   M           |
///  |   Time                |   second      |   T           |
///  |   Electric current    |   Ampere      |   I           |
///  |   Temperature         |   Kelvin      |   K           |
///  |   Substance           |   Mole        |   N           |
///  |   Luminous Intensity  |   Candela     |   J           |
///  ---------------------------------------------------------


/// @brief	Template class to represent physical dimensions of a physical quantity. Every physical quantity can be
///         uniquely decomposed into a product of the 7 fundamental physical dimensions(listed in table above) each
///         raised by a certain exponent. This class represents a physical dimension by statically tracking the
///         exponents of each of fundamental physical dimensions using a std::ratio<>.
///
/// @tparam L_	Ratio denoting the Length exponent of the physical unit.
/// @tparam	M_	Ratio denoting the Mass exponent of the physical unit.
/// @tparam	T_	Ratio denoting the Time exponent of the physical unit.
/// @tparam	I_	Ratio denoting the Electric Current exponent of the physical unit.
/// @tparam	K_	Ratio denoting the Temperature exponent of the physical unit.
/// @tparam	N_  Ratio denoting the Quantity of substance exponent of the physical unit.
/// @tparam	J_	Ratio denoting the Luminous Intensity exponent of the physical unit.

template<typename L_ = std::ratio<0>, typename M_ = std::ratio<0>, typename T_ = std::ratio<0>,
    typename I_ = std::ratio<0>, typename K_ = std::ratio<0>, typename N_ = std::ratio<0>,
    typename J_ = std::ratio<0>>
class PhysicalDimensions
{
public:
    using L = L_;
    using M = M_;
    using T = T_;
    using I = I_;
    using K = K_;
    using N = N_;
    using J = J_;
    using SelfType = PhysicalDimensions<L, M, T, I, K, N, J>;

    PhysicalDimensions() = delete;

    PhysicalDimensions(const PhysicalDimensions &) = delete;

    PhysicalDimensions(PhysicalDimensions &&) = delete;

    ~PhysicalDimensions() = delete;

    SelfType &operator=(const SelfType &) = delete;

    SelfType &operator=(SelfType &&) = delete;
};


///
/// @brief  Helper class to multiply physical dimensions.
/// @tparam Lhs_	Physical dimensions of the LHS.
/// @tparam	Rhs_	Physical dimensions of the RHS.

template<typename Lhs_, typename Rhs_>
class MultiplyPhysicalDimensions
{
public:
    using Lhs = Lhs_;
    using Rhs = Rhs_;
    using SelfType = MultiplyPhysicalDimensions<Lhs, Rhs>;

    /// Alias of the dimension-type resulting from the multiplication of @tparam LhsPhysicalDimensions and @tparam
    /// Rhs
    using Result = PhysicalDimensions<
        std::ratio_add<typename Lhs::L, typename Rhs::L>,
        std::ratio_add<typename Lhs::M, typename Rhs::M>,
        std::ratio_add<typename Lhs::T, typename Rhs::T>,
        std::ratio_add<typename Lhs::I, typename Rhs::I>,
        std::ratio_add<typename Lhs::K, typename Rhs::K>,
        std::ratio_add<typename Lhs::N, typename Rhs::N>,
        std::ratio_add<typename Lhs::J, typename Rhs::J>>;

    MultiplyPhysicalDimensions() = delete;

    MultiplyPhysicalDimensions(const MultiplyPhysicalDimensions &) = delete;

    MultiplyPhysicalDimensions(MultiplyPhysicalDimensions &&) = delete;

    ~MultiplyPhysicalDimensions() = delete;

    SelfType &operator=(SelfType &) = delete;

    SelfType &operator=(SelfType &&) = delete;
};


/// @brief	Helper class to divide physical dimensions.
/// @tparam	Lhs_	Physical dimensions of the LHS.
/// @tparam	Rhs_	Physical dimensions of the RHS.

template<typename Lhs_, typename Rhs_>
class DividePhysicalDimensions
{
public:
    using Lhs = Lhs_;
    using Rhs = Rhs_;
    using SelfType = DividePhysicalDimensions<Lhs, Rhs>;

    /// Alias of the dimension-type resulting from the division of @tparam LhsPhysicalDimensions
    /// from @tparam RhsPhysicalDimensions
    using Result = PhysicalDimensions<
        std::ratio_subtract<typename Lhs::L, typename Rhs::L>,
        std::ratio_subtract<typename Lhs::M, typename Rhs::M>,
        std::ratio_subtract<typename Lhs::T, typename Rhs::T>,
        std::ratio_subtract<typename Lhs::I, typename Rhs::I>,
        std::ratio_subtract<typename Lhs::K, typename Rhs::K>,
        std::ratio_subtract<typename Lhs::N, typename Rhs::N>,
        std::ratio_subtract<typename Lhs::J, typename Rhs::J>>;

    DividePhysicalDimensions() = delete;

    DividePhysicalDimensions(const DividePhysicalDimensions &other) = delete;

    DividePhysicalDimensions(DividePhysicalDimensions &&other) = delete;

    ~DividePhysicalDimensions() = delete;

    SelfType &operator=(SelfType &other) = delete;

    SelfType &operator=(SelfType &&other) = delete;
};


using Angle = PhysicalDimensions<>;
using Length = PhysicalDimensions<std::ratio<1>>;
using Mass = PhysicalDimensions<std::ratio<0>, std::ratio<1>>;
using Time = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Current = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Temperature = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using Substance = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;
using LuminousIntensity = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;

using AngularSpeed = typename DividePhysicalDimensions<Angle, Time>::Result;
using Speed = typename DividePhysicalDimensions<Length, Time>::Result;
using Area = typename MultiplyPhysicalDimensions<Length, Length>::Result;
using Volume = typename MultiplyPhysicalDimensions<Area, Length>::Result;
using Acceleration = typename DividePhysicalDimensions<Speed, Time>::Result;
using Force = typename MultiplyPhysicalDimensions<Mass, Acceleration>::Result; // May the force be with you :D !!!

} // End of namespace units.