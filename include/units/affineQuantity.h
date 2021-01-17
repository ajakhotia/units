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

#include "physicalUnits.h"
#include <ostream>

namespace units
{


/// @brief  Template class to represent affine quantities of a certain physical units with the given representation.
///
/// @tparam 	PhysicalUnits_	Physical units of the affine quantity.
///
/// @tparam 	FloatType_		Floating point representation to store the magnitude of the quantity.

template<typename PhysicalUnits_, typename FloatType_>
class AffineQuantity
{
public:
    using PhysicalUnits = PhysicalUnits_;
    using FloatType = FloatType_;
    using SelfType = AffineQuantity<PhysicalUnits, FloatType>;

    /// @brief  Default constructor with 0 initialization.
    constexpr AffineQuantity() noexcept(true): mValue(0) {};


    /// @brief  Construction with initialization using the passed value.
    /// @param  input
    explicit constexpr AffineQuantity(const FloatType input) noexcept(true): mValue(input) {};

    constexpr AffineQuantity(const AffineQuantity&) noexcept(true) = default;

    constexpr AffineQuantity(AffineQuantity&& rhs) noexcept(true) = default;


    /// @brief  Implicit conversion between compatible physical units. Compatibility is defined and controlled by
    ///         @class PhysicalUnitScale. A physical unit can be converted to any other physical unit of the same
    ///         physical dimensions.
    ///
    ///         Eg: meter <-> inch
    ///             Both meter and inch physical units have the physical dimensions of length but different scales.
    ///             Hence, they can be implicitly converted to each other's type after accounting for the scale.
    ///
    /// @tparam RhsPhysicalUnits
    /// @param  rhs
    template<typename RhsPhysicalUnits>
    constexpr AffineQuantity(const AffineQuantity<RhsPhysicalUnits, FloatType> rhs) noexcept(true):                     // NOLINT(google-explicit-constructor)
        mValue(rhs.scalar() * PhysicalUnitsScale<PhysicalUnits, RhsPhysicalUnits, FloatType>::kScale)
    {
    }

    ~AffineQuantity() = default;

    constexpr AffineQuantity& operator=(const AffineQuantity&) noexcept(true) = default;

    constexpr AffineQuantity& operator=(AffineQuantity&&) noexcept(true) = default;


    /// @brief  Addition assignment operator.
    /// @param  rhs
    /// @return
    constexpr SelfType& operator+=(const SelfType rhs) noexcept(true)
    {
        mValue += rhs.mValue;
        return *this;
    }


    /// @brief  Subtraction assignment operator.
    /// @param  rhs
    /// @return
    constexpr SelfType& operator-=(const SelfType rhs) noexcept(true)
    {
        mValue -= rhs.mValue;
        return *this;
    }


    /// @brief  Multiplication assignment operator with a scalar.
    /// @tparam RhsFloatType
    /// @param  rhsFloat
    /// @return
    template<typename RhsFloatType>
    constexpr SelfType& operator*=(const RhsFloatType rhsFloat) noexcept(true)
    {
        mValue *= static_cast<FloatType>(rhsFloat);
        return *this;
    }


    /// @brief  Division assignment operator with a scalar
    /// @tparam RhsFloatType
    /// @param  rhs
    /// @return
    template<typename RhsFloatType>
    constexpr SelfType& operator/=(const RhsFloatType rhs) noexcept(true)
    {
        mValue /= rhs;
        return *this;
    }


    /// @brief  Pre-increment operator.
    /// @return
    constexpr SelfType& operator++() noexcept(true)
    {
        ++mValue;
        return *this;
    }


    /// @brief  Pre-decrement operator.
    /// @return
    constexpr SelfType& operator--() noexcept(true)
    {
        --mValue;
        return *this;
    }


    /// @brief  Post-increment operator.
    /// @return
    constexpr SelfType operator++(int) noexcept(true)                                                                   // NOLINT
    {
        const auto cache = *this;
        ++mValue;

        return cache;
    }


    /// @brief  Post-decrement operator.
    /// @return
    constexpr SelfType operator--(int) noexcept(true)                                                                   // NOLINT
    {
        const auto cache = *this;
        --mValue;

        return cache;
    }


    /// @brief  Method to change the underlying representation of the magnitude.
    /// @tparam ReturnFloatType
    /// @return
    template<typename ReturnFloatType>
    constexpr AffineQuantity<PhysicalUnits, ReturnFloatType> cast() const noexcept(true)
    {
        return AffineQuantity<PhysicalUnits, ReturnFloatType>(static_cast<ReturnFloatType>(mValue));
    }


    /// @brief  Method to access the magnitude of affine quantity.
    /// @return
    constexpr FloatType scalar() const noexcept(true)
    {
        return mValue;
    }

private:
    FloatType mValue;
};


/// @brief
/// @tparam PhysicalQuantityVectorType
/// @param lhs
/// @param rhs
/// @return
template<typename AffineQuantity>
constexpr AffineQuantity operator+(const AffineQuantity lhs, const AffineQuantity rhs) noexcept(true)
{
    return AffineQuantity(lhs.scalar() + rhs.scalar());
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr LhsAffineQuantity operator+(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    return lhs + LhsAffineQuantity(rhs);
}


/// @brief
/// @tparam AffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename AffineQuantity>
constexpr AffineQuantity operator-(const AffineQuantity lhs, const AffineQuantity rhs) noexcept(true)
{
    return AffineQuantity(lhs.scalar() - rhs.scalar());
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr LhsAffineQuantity operator-(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    return lhs - LhsAffineQuantity(rhs);
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr decltype(auto) operator*(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    static_assert(std::is_same<typename LhsAffineQuantity::FloatType, typename RhsAffineQuantity::FloatType>::value,
        "Invalid request to multiply affine quantities of different underlying representation. Use cast<> to change "
        "the underlying representation of one of the operands to be the same as the other.");

    using ResultType = AffineQuantity<
        typename MultiplyPhysicalUnits<
            typename LhsAffineQuantity::PhysicalUnits,
            typename RhsAffineQuantity::PhysicalUnits>::Result,
        typename LhsAffineQuantity::FloatType>;


    return ResultType(lhs.scalar() * rhs.scalar());
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr decltype(auto) operator/(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    static_assert(std::is_same<typename LhsAffineQuantity::FloatType, typename RhsAffineQuantity::FloatType>::value,
          "Invalid request to divide affine quantities of different underlying representation. Use cast<> to change "
          "the underlying representation of one of the operands to be the same as the other.");

    using ResultType = AffineQuantity<
        typename DividePhysicalUnits<
            typename LhsAffineQuantity::PhysicalUnits,
            typename RhsAffineQuantity::PhysicalUnits>::Result,
        typename LhsAffineQuantity::FloatType>;


    return ResultType(lhs.scalar() / rhs.scalar());
}


/// @brief
/// @tparam AffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename AffineQuantity>
constexpr bool operator==(const AffineQuantity lhs, const AffineQuantity rhs) noexcept(true)
{
    return lhs.scalar() == rhs.scalar();
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr bool operator==(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    return lhs == LhsAffineQuantity(rhs);
}


/// @brief
/// @tparam AffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename AffineQuantity>
constexpr bool operator!=(const AffineQuantity lhs, const AffineQuantity rhs) noexcept(true)
{
    return not(lhs == rhs);
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr bool operator!=(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    return not(lhs == rhs);
}


/// @brief
/// @tparam AffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename AffineQuantity>
constexpr bool operator<(const AffineQuantity lhs, const AffineQuantity rhs) noexcept(true)
{
    return lhs.scalar() < rhs.scalar();
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr bool operator<(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    return lhs < LhsAffineQuantity(rhs);
}


/// @brief
/// @tparam AffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename AffineQuantity>
constexpr bool operator<=(const AffineQuantity lhs, const AffineQuantity rhs) noexcept(true)
{
    return lhs.scalar() <= rhs.scalar();
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr bool operator<=(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    return lhs <= LhsAffineQuantity(rhs);
}


/// @brief
/// @tparam AffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename AffineQuantity>
constexpr bool operator>(const AffineQuantity lhs, const AffineQuantity rhs) noexcept(true)
{
    return lhs.scalar() > rhs.scalar();
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr bool operator>(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    return lhs > LhsAffineQuantity(rhs);
}


/// @brief
/// @tparam AffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename AffineQuantity>
constexpr bool operator>=(const AffineQuantity lhs, const AffineQuantity rhs) noexcept(true)
{
    return lhs.scalar() >= rhs.scalar();
}


/// @brief
/// @tparam LhsAffineQuantity
/// @tparam RhsAffineQuantity
/// @param lhs
/// @param rhs
/// @return
template<typename LhsAffineQuantity, typename RhsAffineQuantity>
constexpr bool operator>=(const LhsAffineQuantity lhs, const RhsAffineQuantity rhs) noexcept(true)
{
    return lhs >= LhsAffineQuantity(rhs);
}


} // End of namespace units.