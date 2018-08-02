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


/** Table of primary physical dimensions. NOTE: Do not change the order of this table. The
 * 	type safety of the units system follows the order below and is for reference as the
 * 	primary source of truth.
 * ---------------------------------------------------------
 *  |   Physical Unit       |   SI units    |   DIMENSION   |
 *  ---------------------------------------------------------
 *  |   Length              |   meter       |   L           |
 *  |   Mass                |   kilogram    |   M           |
 *  |   Time                |   second      |   T           |
 *  |   Electric current    |   Ampere      |   I           |
 *  |   Temperature         |   Kelvin      |   K           |
 *  |   Substance           |   Mole        |   N           |
 *  |   Luminous Intensity  |   candela     |   J           |
 *  ---------------------------------------------------------
 */

/**
 * @brief	Template class to denote physical dimension of a unit.
 * @tparam	L_	Ratio denoting the Length exponent of the physical unit.
 * @tparam	M_	Ratio denoting the Mass exponent of the physical unit.
 * @tparam	T_	Ratio denoting the Time exponent of the physical unit.
 * @tparam	I_	Ratio denoting the Electric Current exponent of the physical unit.
 * @tparam	K_	Ratio denoting the Temperature exponent of the physical unit.
 * @tparam	N_	Ratio denoting the Quantity of substance exponent of the physical unit.
 * @tparam	J_	Ratio denoting the Luminous Intensity exponent of the physical unit.
 */
template<typename L_ = std::ratio<0>, typename M_ = std::ratio<0>, typename T_ = std::ratio<0>,
		typename I_ = std::ratio<0>, typename K_ = std::ratio<0>, typename N_ = std::ratio<0>,
		typename J_ = std::ratio<0>>
class PhysicalDimensions
{
public:
	/// Alias of the Length exponent of the physical dimension.
	using L = L_;

	/// Alias of the Mass exponent of the physical dimension.
	using M = M_;

	/// Alias of the Time exponent of the physical dimension.
	using T = T_;

	/// Alias of the Electric Current exponent of the physical dimension.
	using I = I_;

	/// Alias of the Temperature exponent of the physical dimension.
	using K = K_;

	/// Alias of the Quantity of substance exponent of the physical dimension.
	using N = N_;

	/// Alias of the Luminous Intensity exponent of the physical dimension.
	using J = J_;

	/// Alias of self for convenience.
	using SelfType = PhysicalDimensions<L, M, T, I, K, N, J>;

	/// Deleted constructors and destructors.
	PhysicalDimensions() = delete;

	PhysicalDimensions(const PhysicalDimensions& otherPhysicalDimension) = delete;

	PhysicalDimensions(PhysicalDimensions&& otherPhysicalDimension) = delete;

	~PhysicalDimensions() = delete;

	/// Deleted assignment operators.
	SelfType& operator=(const SelfType& otherPhysicalDimension) = delete;

	SelfType& operator=(SelfType&& otherPhysicalDimension) = delete;
};

/**
 * @brief	Helper class to add physical dimensions.
 * @tparam	LhsPhysicalDimensions_	Physical dimensions of the LHS.
 * @tparam	RhsPhysicalDimensions_	Physical dimensions of the RHS.
 */
template<typename LhsPhysicalDimensions_, typename RhsPhysicalDimensions_>
class MultiplyPhysicalDimensions
{
public:
	/// Alisa LHS physical dimensions.
	using LhsPhysicalDimensions = LhsPhysicalDimensions_;

	/// Alisa RHS physical dimensions.
	using RhsPhysicalDimensions = RhsPhysicalDimensions_;

	/// Alias of self for convenience.
	using SelfType = MultiplyPhysicalDimensions<LhsPhysicalDimensions, RhsPhysicalDimensions>;

	/// Alias of the dimension-type resulting from the addition of @tparam LhsPhysicalDimensions
	/// and @tparam RhsPhysicalDimensions
	using Result = PhysicalDimensions<
			std::ratio_add<typename LhsPhysicalDimensions::L, typename RhsPhysicalDimensions::L>,
			std::ratio_add<typename LhsPhysicalDimensions::M, typename RhsPhysicalDimensions::M>,
			std::ratio_add<typename LhsPhysicalDimensions::T, typename RhsPhysicalDimensions::T>,
			std::ratio_add<typename LhsPhysicalDimensions::I, typename RhsPhysicalDimensions::I>,
			std::ratio_add<typename LhsPhysicalDimensions::K, typename RhsPhysicalDimensions::K>,
			std::ratio_add<typename LhsPhysicalDimensions::N, typename RhsPhysicalDimensions::N>,
			std::ratio_add<typename LhsPhysicalDimensions::J, typename RhsPhysicalDimensions::J>>;

	/// Deleted constructor.
	MultiplyPhysicalDimensions() = delete;

	MultiplyPhysicalDimensions(const MultiplyPhysicalDimensions& other) = delete;

	MultiplyPhysicalDimensions(MultiplyPhysicalDimensions&& other) = delete;

	~MultiplyPhysicalDimensions() = delete;

	/// Deleted assignment operators.
	SelfType& operator=(SelfType& other) = delete;

	SelfType& operator=(SelfType&& other) = delete;
};

/**
 * @brief	Helper class to subtract physical dimensions.
 * @tparam	LhsPhysicalDimensions_	Physical dimensions of the LHS.
 * @tparam	RhsPhysicalDimensions_	Physical dimensions of the RHS.
 */
template<typename LhsPhysicalDimensions_, typename RhsPhysicalDimensions_>
class DividePhysicalDimensions
{
public:
	/// Alisa LHS physical dimensions.
	using LhsPhysicalDimensions = LhsPhysicalDimensions_;

	/// Alisa RHS physical dimensions.
	using RhsPhysicalDimensions = RhsPhysicalDimensions_;

	/// Alias self-type for convenience.
	using SelfType = DividePhysicalDimensions<LhsPhysicalDimensions, RhsPhysicalDimensions>;

	/// Alias of the dimension-type resulting from the subtraction of @tparam LhsPhysicalDimensions
	/// from @tparam RhsPhysicalDimensions
	using Result = PhysicalDimensions<
			std::ratio_subtract<typename LhsPhysicalDimensions::L, typename RhsPhysicalDimensions::L>,
			std::ratio_subtract<typename LhsPhysicalDimensions::M, typename RhsPhysicalDimensions::M>,
			std::ratio_subtract<typename LhsPhysicalDimensions::T, typename RhsPhysicalDimensions::T>,
			std::ratio_subtract<typename LhsPhysicalDimensions::I, typename RhsPhysicalDimensions::I>,
			std::ratio_subtract<typename LhsPhysicalDimensions::K, typename RhsPhysicalDimensions::K>,
			std::ratio_subtract<typename LhsPhysicalDimensions::N, typename RhsPhysicalDimensions::N>,
			std::ratio_subtract<typename LhsPhysicalDimensions::J, typename RhsPhysicalDimensions::J>>;

	/// Deleted constructors and destructors.
	DividePhysicalDimensions() = delete;

	DividePhysicalDimensions(const DividePhysicalDimensions& other) = delete;

	DividePhysicalDimensions(DividePhysicalDimensions&& other) = delete;

	~DividePhysicalDimensions() = delete;

	/// Deleted assignments operators.
	SelfType& operator=(SelfType& other) = delete;

	SelfType& operator=(SelfType&& other) = delete;
};

/// Convenience alias representing the basic/primary dimensions.
using Angle = PhysicalDimensions<>;

using Length = PhysicalDimensions<std::ratio<1>>;

using Mass = PhysicalDimensions<std::ratio<0>, std::ratio<1>>;

using Time = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<1>>;

using Current = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;

using Temperature = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;

using Substance = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>,
		std::ratio<1>>;

using LuminousIntensity = PhysicalDimensions<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>,
		std::ratio<0>, std::ratio<1>>;

/// Convenience alias to represent secondary dimensions.
using AngularSpeed = typename DividePhysicalDimensions<Angle, Time>::Result;

using Speed = typename DividePhysicalDimensions<Length, Time>::Result;

using Area = typename MultiplyPhysicalDimensions<Length, Length>::Result;

/// Convenience aliases of other commonly used physical quantities.
using Volume = typename MultiplyPhysicalDimensions<Area, Length>::Result;

using Acceleration = typename DividePhysicalDimensions<Speed, Time>::Result;

using Force = typename MultiplyPhysicalDimensions<Mass, Acceleration>::Result; // May the force be with you :D !!!

} // End of namespace units.