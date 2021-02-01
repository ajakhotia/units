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

#include "physicalDimensions.hpp"

namespace units
{


/// @brief  Template class to represent a physical unit. A physical unit consists of physical dimensions and
///         a scale factor. In this implementation, we use the S.I. standard as the basis for determining scale.
///
///         EG: For the physical unit representing a meter, the physical dimension is of type Length and scale is
///             of type std::ratio<1, 1>.
///
///             For the physical unit representing an inch, the physical dimension is of type Length and scale is
///             of type std::ratio<254, 10000>. Meter is the SI unit for Length and 1 inch is 0.0254 meters.
///
/// @tparam	PhysicalDimensions_     The physical dimensions of the unit of measurement.
///
/// @tparam	Scale_                  Scale of the physical unit w.r.t. it's S.I. counterpart.

template<typename PhysicalDimensions_, typename Scale_>
class PhysicalUnits
{
public:
    using PhysicalDimensions = PhysicalDimensions_;
    using Scale = Scale_;
    using SelfType = PhysicalUnits<PhysicalDimensions, Scale>;

    PhysicalUnits() = delete;

    PhysicalUnits(const PhysicalUnits &) = delete;

    PhysicalUnits(PhysicalUnits &&) = delete;

    ~PhysicalUnits() = delete;

    SelfType &operator=(const SelfType &) = delete;

    SelfType &operator=(SelfType &&) = delete;
};


/// @brief  Statically computes a std::ratio and the corresponding float which converts a value with RHS physical units
///         to the appropriate value in LHS' scale.
///
/// @tparam	Lhs_	LHS / Destination physical units type.
///
/// @tparam	Rhs_	RHS / Source physical units type.
///
/// @tparam	FloatType_  Floating point representation to be used for representing the
///                     resulting conversion ratio.

template<typename Lhs_, typename Rhs_, typename FloatType_>
class PhysicalUnitsScale
{
public:
    using Lhs = Lhs_;
    using Rhs = Rhs_;
    using FloatType = FloatType_;
    using SelfType = PhysicalUnitsScale<Lhs, Rhs, FloatType>;

    // Assert same physical dimensions for operand physical units.
    static_assert(
        std::is_same<typename Lhs::PhysicalDimensions, typename Rhs::PhysicalDimensions>::value,
        "Requested scale computation for physical units of different physical dimensions.");

    using Result = std::ratio_divide<typename Rhs::Scale, typename Lhs::Scale>;

    static constexpr const FloatType kScale{FloatType(Result::num) / FloatType(Result::den)};

    PhysicalUnitsScale() = delete;

    PhysicalUnitsScale(const PhysicalUnitsScale &) = delete;

    PhysicalUnitsScale(PhysicalUnitsScale &&) = delete;

    ~PhysicalUnitsScale() = delete;

    SelfType &operator=(const SelfType &) = delete;

    SelfType &operator=(SelfType &&) = delete;
};


/// @brief  Statically computes the physical units of the result of the product of operand physical units.
/// @tparam Lhs_
/// @tparam Rhs_
template<typename Lhs_, typename Rhs_>
class MultiplyPhysicalUnits
{
public:
    using Lhs = Lhs_;
    using Rhs = Rhs_;
    using SelfType = MultiplyPhysicalUnits<Lhs, Rhs>;

    /// Resulting physical units that is a multiplication of LHS and RHS.
    using Result = PhysicalUnits<
        typename MultiplyPhysicalDimensions<typename Lhs::PhysicalDimensions, typename Rhs::PhysicalDimensions>::Result,
        typename std::ratio_multiply<typename Lhs::Scale, typename Rhs::Scale>>;

    MultiplyPhysicalUnits() = delete;

    MultiplyPhysicalUnits(const MultiplyPhysicalUnits &) = delete;

    MultiplyPhysicalUnits(MultiplyPhysicalUnits &&) = delete;

    ~MultiplyPhysicalUnits() = delete;

    SelfType &operator=(const SelfType &) = delete;

    SelfType &operator=(SelfType &&) = delete;
};


/// @brief  Statically computes the physical units of the result of the division of operand physical units.
/// @tparam Lhs_
/// @tparam Rhs_
template<typename Lhs_, typename Rhs_>
class DividePhysicalUnits
{
public:
    using Lhs = Lhs_;
    using Rhs = Rhs_;
    using SelfType = DividePhysicalUnits<Lhs, Rhs>;

    /// Resulting physical units that is a multiplication of LHS and RHS.
    using Result = PhysicalUnits<
        typename DividePhysicalDimensions<typename Lhs::PhysicalDimensions, typename Rhs::PhysicalDimensions>::Result,
        typename std::ratio_divide<typename Lhs::Scale, typename Rhs::Scale>>;

    DividePhysicalUnits() = delete;

    DividePhysicalUnits(const DividePhysicalUnits &) = delete;

    DividePhysicalUnits(DividePhysicalUnits &&) = delete;

    ~DividePhysicalUnits() = delete;

    SelfType &operator=(const SelfType &) = delete;

    SelfType &operator=(SelfType &&) = delete;
};


} // End of namespace units.