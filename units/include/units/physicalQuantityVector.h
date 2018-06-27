/*  Copyright 2016. All rights reserved by the author.
 *  Author: Anurag Jakhotia <anuragjakhotia@gmail.com>
 */
#pragma once

#include "physicalUnits.h"
#include <ostream>

namespace cppYard
{
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
	constexpr PhysicalQuantityVector() noexcept(true) : mValue(0) {};

	/// Construction from an arbitrary scalar.
	explicit constexpr PhysicalQuantityVector(const FloatType input) noexcept(true): mValue(input) {};

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
	template<typename  RhsFloatType>
	constexpr SelfType& operator/=(const RhsFloatType rhs) noexcept(true)
	{
		mValue /= rhs;
		return *this;
	}

	/// Pre-increment operator.
	constexpr SelfType& operator++() noexcept(true)
	{
		++mValue;
		return  *this;
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
		return  *this;
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

/*

/// Operator to add physical quantities of same physical units but possibly different float
/// representation. The static_cast is a compile time operation that has no run-time cost. So, there is
/// no value in defining an overload of the operator with same floating point arguments.
template<typename PhysicalUnitsType, typename LhsFloatType, typename RhsFloatType>
PhysicalQuantityVector<PhysicalUnitsType, LhsFloatType> operator+(
		const PhysicalQuantityVector<PhysicalUnitsType, LhsFloatType> lhs,
		const PhysicalQuantityVector<PhysicalUnitsType, RhsFloatType> rhs) noexcept (true)
{
	return PhysicalQuantityVector<PhysicalUnitsType, LhsFloatType>(lhs.mValue + static_cast<LhsFloatType>(rhs.mValue));
};

/// Operator to add physical quantities of same physical dimensions but different scale and float representation.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
LhsPhysicalQuantityVector operator+(const LhsPhysicalQuantityVector lhs,
									const RhsPhysicalQuantityVector rhs) noexcept(true)
{
	return lhs + LhsPhysicalQuantityVector(rhs);
};

/// Operator to subtract physical quantities of same physical units but possibly different float
/// representation. The static_cast is a compile time operation that has no run-time cost. So, there is
/// no value in defining an overload of the operator with same floating point arguments.
template<typename PhysicalUnitsType, typename LhsFloatType, typename RhsFloatType>
PhysicalQuantityVector<PhysicalUnitsType, LhsFloatType> operator-(
		const PhysicalQuantityVector<PhysicalUnitsType, LhsFloatType> lhs,
		const PhysicalQuantityVector<PhysicalUnitsType, RhsFloatType> rhs) noexcept (true)
{
	return PhysicalQuantityVector<PhysicalUnitsType, LhsFloatType>(lhs.mValue - static_cast<LhsFloatType>(rhs.mValue));
};

/// Operator to subtract physical quantities of same physical dimensions but different scale and float representation.
template<typename LhsPhysicalQuantityVector, typename RhsPhysicalQuantityVector>
LhsPhysicalQuantityVector operator-(const LhsPhysicalQuantityVector lhs,
									const RhsPhysicalQuantityVector rhs) noexcept(true)
{
	return lhs - LhsPhysicalQuantityVector(rhs);
};
*/
/// Multiplication operator

/// Pre scalar multiplication operator

/// Post scalar multiplication operator

/// Division operator

/// Pre scalar division operator

/// Post scalar division operator

/// Equality

/// Non-equality

/// Lesser than inequality

/// Lesser than or equal-to inequality

/// Greater than inequality

/// Greater than or equal-to inequality


} // End of namespace units.
} // End of namespace cppYard.