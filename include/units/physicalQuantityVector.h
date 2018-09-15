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

/**
 * @brief	Class to represent quantities with units in a type-safe manner. This class' runtime complexity is
 * 			identical to using raw scalars.So don't be naive and use this class.
 *
 * @tparam 	PhysicalUnits_	Physical units of the vector quantity.
 *
 * @tparam 	FloatType_		Float representation to be used for the underlying value.
 */
template<typename PhysicalUnits_, typename FloatType_>
class PhysicalQuantityVector
{
public:
    /// Alias of the underlying physical units.
    using PhysicalUnits = PhysicalUnits_;

    /// Alias of the underlying float representation.
    using FloatType = FloatType_;

    /// Alias of the self type for convenience.
    using SelfType = PhysicalQuantityVector<PhysicalUnits, FloatType>;

    /// Default construction to zero or additive identity.
    constexpr PhysicalQuantityVector() noexcept(true) :
            mValue(0)
    {
    };

    /// Construction from an arbitrary scalar.
    explicit constexpr PhysicalQuantityVector(const FloatType input) noexcept(true):
            mValue(input)
    {
    };

    /// Default copy constructor. NOTE: Quite can't figure out why making this explicit doesn't work.
    constexpr PhysicalQuantityVector(const PhysicalQuantityVector& rhs) noexcept(true) = default;

    /// Default move constructor.
    constexpr PhysicalQuantityVector(PhysicalQuantityVector&& rhs) noexcept(true) = default;

    /// Constructor to initialize self from another compatible physical quantity vector.
    template<typename RhsPhysicalUnits>
    explicit constexpr PhysicalQuantityVector(
            const PhysicalQuantityVector<RhsPhysicalUnits, FloatType> rhs) noexcept(true):
            mValue(rhs.scalar() *
                   PhysicalUnitsConversionHelper<PhysicalUnits, RhsPhysicalUnits, FloatType>::kFloatRatio)
    {
    }

    /// Defaulted destructor.
    ~PhysicalQuantityVector() = default;

    /// Default copy-assignment operator.
    constexpr SelfType& operator=(const SelfType&) noexcept(true) = default;

    /// Default move-assignment.
    constexpr SelfType& operator=(SelfType&&) noexcept(true) = default;

    /// Addition assignment.
    constexpr SelfType& operator+=(const SelfType& rhs) noexcept(true)
    {
        mValue += rhs.mValue;
        return *this;
    }

    /// Heterogeneous addition assignment.
    template<typename RhsPhysicalUnits>
    constexpr SelfType& operator+=(const PhysicalQuantityVector<RhsPhysicalUnits, FloatType> rhs) noexcept(true)
    {
        *this += SelfType(rhs);
        return *this;
    }

    /// Subtraction assignment.
    constexpr SelfType& operator-=(const SelfType& rhs) noexcept(true)
    {
        mValue -= rhs.mValue;
        return *this;
    }

    /// Heterogeneous subtraction assignment.
    template<typename RhsPhysicalUnits>
    constexpr SelfType& operator-=(const PhysicalQuantityVector<RhsPhysicalUnits, FloatType> rhs) noexcept(true)
    {
        *this -= SelfType(rhs);
        return *this;
    }

    /// Scalar multiplication assignment.
    template<typename RhsFloatType>
    constexpr SelfType& operator*=(const RhsFloatType rhsFloat) noexcept(true)
    {
        mValue *= static_cast<FloatType>(rhsFloat);
        return *this;
    }

    /// Scalar division assignment.
    template<typename RhsFloatType>
    constexpr SelfType& operator/=(const RhsFloatType rhs) noexcept(true)
    {
        mValue /= rhs;
        return *this;
    }

    /// Pre-increment operator.
    constexpr SelfType& operator++() noexcept(true)
    {
        ++mValue;
        return *this;
    }

    /// Post-increment operator.
    constexpr SelfType operator++(int) noexcept(true)
    {
        SelfType cache = *this;
        ++mValue;

        return cache;
    }

    /// Pre-decrement operator.
    constexpr SelfType& operator--() noexcept(true)
    {
        --mValue;
        return *this;
    }

    /// Post-decrement operator.
    constexpr SelfType operator--(int) noexcept(true)
    {
        SelfType cache = *this;
        --mValue;

        return cache;
    }

    /// Cast the the float representation to the provided floating type.
    template<typename ReturnFloatType>
    constexpr PhysicalQuantityVector<PhysicalUnits, ReturnFloatType> cast() const noexcept(true)
    {
        return PhysicalQuantityVector<PhysicalUnits, ReturnFloatType>(static_cast<ReturnFloatType>(mValue));
    };

    /// Scalar value getter.
    constexpr FloatType scalar() const noexcept(true)
    {
        return mValue;
    }

private:
    FloatType mValue;
};


/**
 * @brief   Helper class to compute the type of the result when multiplying two @class PhysicalQuantityVectors.
 *
 * @tparam  LhsPhysicalQuantityVector_  LHS physical quantity vector type.
 *
 * @tparam  RhsPhysicalQuantityVector_  RHS physical quantity vector type.
 */
template<typename LhsPhysicalQuantityVector_, typename RhsPhysicalQuantityVector_>
class MultiplyPhysicalQuantityVector
{
public:
    /// Alias of the LHS physical quantity vector.
    using LhsPhysicalQuantityVector = LhsPhysicalQuantityVector_;

    /// Alias of the RHS physical quantity vector.
    using RhsPhysicalQuantityVector = RhsPhysicalQuantityVector_;

    // Assert same floating point representation underlying the LHS and RHS physical quantity types.
    static_assert(std::is_same<typename LhsPhysicalQuantityVector::FloatType,
                          typename RhsPhysicalQuantityVector::FloatType>::value,
                  "You mixed different floating point representations. Use cast<> to change floating point"
                  " representation of operands before performing the operations.");

    /// Alias of self-type.
    using SelfType = MultiplyPhysicalQuantityVector<LhsPhysicalQuantityVector, RhsPhysicalQuantityVector>;

    /// Resulting type after multiplication of LHS and RHS quantity vectors.
    using Result = PhysicalQuantityVector<
            typename MultiplyPhysicalUnits<
                    typename LhsPhysicalQuantityVector::PhysicalUnits,
                    typename RhsPhysicalQuantityVector::PhysicalUnits>::Result,
            typename LhsPhysicalQuantityVector::FloatType>;

    /// Deleted constructor and destructors.
    MultiplyPhysicalQuantityVector() = delete;

    MultiplyPhysicalQuantityVector(const MultiplyPhysicalQuantityVector&) = delete;

    MultiplyPhysicalQuantityVector(MultiplyPhysicalQuantityVector&&) = delete;

    ~MultiplyPhysicalQuantityVector() = delete;

    /// Deleted assignment operators.
    SelfType& operator=(const SelfType&) = delete;

    SelfType& operator=(SelfType&&) = delete;
};

/**
 * @brief   Helper class to compute the type of the result when dividing two @class PhysicalQuantityVectors.
 *
 * @tparam  LhsPhysicalQuantityVector_  LHS physical quantity vector type.
 *
 * @tparam  RhsPhysicalQuantityVector_  RHS physical quantity vector type.
 */
template<typename LhsPhysicalQuantityVector_, typename RhsPhysicalQuantityVector_>
class DividePhysicalQuantityVector
{
public:
    /// Alias of the LHS physical quantity vector.
    using LhsPhysicalQuantityVector = LhsPhysicalQuantityVector_;

    /// Alias of the RHS physical quantity vector.
    using RhsPhysicalQuantityVector = RhsPhysicalQuantityVector_;

    // Assert same floating point representation underlying the LHS and RHS physical quantity types.
    static_assert(std::is_same<typename LhsPhysicalQuantityVector::FloatType,
                          typename RhsPhysicalQuantityVector::FloatType>::value,
                  "You mixed different floating point representations. Use cast<> to change floating point"
                  " representation of operands before performing the operations.");

    /// Alias of self-type.
    using SelfType = DividePhysicalQuantityVector<LhsPhysicalQuantityVector, RhsPhysicalQuantityVector>;

    /// Resulting type after multiplication of LHS and RHS quantity vectors.
    using Result = PhysicalQuantityVector<
            typename DividePhysicalUnits<
                    typename LhsPhysicalQuantityVector::PhysicalUnits,
                    typename RhsPhysicalQuantityVector::PhysicalUnits>::Result,
            typename LhsPhysicalQuantityVector::FloatType>;

    /// Deleted constructor and destructors.
    DividePhysicalQuantityVector() = delete;

    DividePhysicalQuantityVector(const DividePhysicalQuantityVector&) = delete;

    DividePhysicalQuantityVector(DividePhysicalQuantityVector&&) = delete;

    ~DividePhysicalQuantityVector() = delete;

    /// Deleted assignment operators.
    SelfType& operator=(const SelfType&) = delete;

    SelfType& operator=(SelfType&&) = delete;
};

/// Addition operator
template<typename PhysicalQuantityVectorType>
constexpr PhysicalQuantityVectorType operator+(const PhysicalQuantityVectorType lhs,
                                               const PhysicalQuantityVectorType rhs) noexcept(true)
{
    return PhysicalQuantityVectorType(lhs.scalar() + rhs.scalar());
};

/// Heterogeneous Addition operator.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr LhsPhysicalQuantityVector operator+(const LhsPhysicalQuantityVector lhs,
                                              const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    return lhs + LhsPhysicalQuantityVector(rhs);
};

/// Subtraction operator.
template<typename PhysicalQuantityVectorType>
constexpr PhysicalQuantityVectorType operator-(const PhysicalQuantityVectorType lhs,
                                               const PhysicalQuantityVectorType rhs) noexcept(true)
{
    return PhysicalQuantityVectorType(lhs.scalar() - rhs.scalar());
};

/// Heterogeneous subtraction operator.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr LhsPhysicalQuantityVector operator-(const LhsPhysicalQuantityVector lhs,
                                              const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    return lhs - LhsPhysicalQuantityVector(rhs);
};


/// Multiplication operator
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr typename MultiplyPhysicalQuantityVector<LhsPhysicalQuantityVector, RhsPhysicalQuantityVector>::Result
operator*(const LhsPhysicalQuantityVector lhs, const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    using ResultType = typename MultiplyPhysicalQuantityVector<
            LhsPhysicalQuantityVector, RhsPhysicalQuantityVector>::Result;

    return ResultType(lhs.scalar() * rhs.scalar());
};

/// Division operator
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr typename DividePhysicalQuantityVector<LhsPhysicalQuantityVector, RhsPhysicalQuantityVector>::Result
operator/(const LhsPhysicalQuantityVector lhs, const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    using ResultType = typename DividePhysicalQuantityVector<
            LhsPhysicalQuantityVector, RhsPhysicalQuantityVector>::Result;

    return ResultType(lhs.scalar() / rhs.scalar());
};

/// Equality operator.
template<typename PhysicalQuantityVectorType>
constexpr bool operator==(const PhysicalQuantityVectorType lhs, const PhysicalQuantityVectorType rhs) noexcept(true)
{
    return lhs.scalar() == rhs.scalar();
};

/// Heterogeneous equality operator.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr bool operator==(const LhsPhysicalQuantityVector lhs, const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    return lhs == LhsPhysicalQuantityVector(rhs);
};


/// Inequality operator.
template<typename PhysicalQuantityVectorType>
constexpr bool operator!=(const PhysicalQuantityVectorType lhs, const PhysicalQuantityVectorType rhs) noexcept(true)
{
    return lhs.scalar() != rhs.scalar();
};

/// Heterogeneous inequality operator.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr bool operator!=(const LhsPhysicalQuantityVector lhs, const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    return lhs != LhsPhysicalQuantityVector(rhs);
};


/// Lesser than inequality operator.
template<typename PhysicalQuantityVectorType>
constexpr bool operator<(const PhysicalQuantityVectorType lhs, const PhysicalQuantityVectorType rhs) noexcept(true)
{
    return lhs.scalar() < rhs.scalar();
};

/// Heterogeneous lesser than equality operator.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr bool operator<(const LhsPhysicalQuantityVector lhs, const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    return lhs < LhsPhysicalQuantityVector(rhs);
};


/// Lesser than or equal-to inequality operator.
template<typename PhysicalQuantityVectorType>
constexpr bool operator<=(const PhysicalQuantityVectorType lhs, const PhysicalQuantityVectorType rhs) noexcept(true)
{
    return lhs.scalar() <= rhs.scalar();
};

/// Heterogeneous lesser than or equal-to equality operator.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr bool operator<=(const LhsPhysicalQuantityVector lhs, const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    return lhs <= LhsPhysicalQuantityVector(rhs);
};

/// Greater than inequality operator.
template<typename PhysicalQuantityVectorType>
constexpr bool operator>(const PhysicalQuantityVectorType lhs, const PhysicalQuantityVectorType rhs) noexcept(true)
{
    return lhs.scalar() > rhs.scalar();
};

/// Heterogeneous Greater than equality operator.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr bool operator>(const LhsPhysicalQuantityVector lhs, const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    return lhs > LhsPhysicalQuantityVector(rhs);
};


/// Greater than or equal-to inequality operator.
template<typename PhysicalQuantityVectorType>
constexpr bool operator>=(const PhysicalQuantityVectorType lhs, const PhysicalQuantityVectorType rhs) noexcept(true)
{
    return lhs.scalar() >= rhs.scalar();
};

/// Heterogeneous Greater than or equal-to equality operator.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
constexpr bool operator>=(const LhsPhysicalQuantityVector lhs, const RhsPhysicalQuantityVector rhs) noexcept(true)
{
    return lhs >= LhsPhysicalQuantityVector(rhs);
};


} // End of namespace units.