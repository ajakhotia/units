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
 * @tparam 	FloatType_		Float representation of the magnitude.
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

	/// Default construction to zero or additive identity. This is needed in cases involving use of
	/// containers and other higher level collections like matrices.
	constexpr PhysicalQuantityVector() noexcept(true) : mValue(0) {};

	/// Construction from an arbitrary scalar.
	explicit constexpr PhysicalQuantityVector(const FloatType input) noexcept(true): mValue(input) {};

	/// Default copy constructor. Its is important to use the class name instead of the SelfType alias
	/// as the compiler will fail to pick it as the copy constructor. NOTE: The copy constructor is
	/// not declared explicit as it breaks the working of copy assignment.
	constexpr PhysicalQuantityVector(const PhysicalQuantityVector& rhs) noexcept(true) = default;

	/// Default move constructor. Its is important to use the class name instead of the SelfType alias
	/// as the compiler will fail to pick it as the move constructor.
	constexpr PhysicalQuantityVector(PhysicalQuantityVector&& rhs) noexcept(true) = default;


	/// Constructor to inter-convert physical quantity vector of of same dimensions and float types but different
	/// units scale.
	template<typename RhsPhysicalUnits>
	constexpr PhysicalQuantityVector(const PhysicalQuantityVector<RhsPhysicalUnits, FloatType> rhs) noexcept(true):
			mValue(rhs.mValue * PhysicalUnitsConversionHelper<PhysicalUnits, RhsPhysicalUnits, FloatType>::kFloatRatio)
	{
	}

	/// Defaulted destructor.
	~PhysicalQuantityVector() = default;

	/// Default copy-assignment operator. Technically is not needed as the copy constructor is defaulted and
	/// is not explicit.
	constexpr SelfType& operator=(const SelfType&) noexcept(true) = default;

	/// Default move-assignment. Technically is not needed as the move constructor is defaulted and
	/// is not explicit.
	constexpr SelfType& operator=(SelfType&&) noexcept(true) = default;

	/// Homogeneous self-addition operator.
	SelfType& operator+=(const SelfType& rhs) noexcept(true)
	{
		mValue += rhs.mValue;
		return *this;
	}

	/// Heterogeneous self-addition operator.
	template<typename RhsPhysicalUnits>
	SelfType& operator+=(const PhysicalQuantityVector<RhsPhysicalUnits, FloatType> rhs) noexcept(true)
	{
		*this += SelfType(rhs);
		return *this;
	}

	/// Homogeneous self-subtraction operator.
	SelfType& operator-=(const SelfType& rhs) noexcept(true)
	{
		mValue -= rhs.mValue;
		return *this;
	}

	/// Heterogeneous self-subtraction operator.
	template<typename RhsPhysicalUnits>
	SelfType& operator-=(const PhysicalQuantityVector<RhsPhysicalUnits, FloatType> rhs) noexcept(true)
	{
		*this -= SelfType(rhs);
		return *this;
	}

	/// Pre-increment operator.
	SelfType& operator++(int) noexcept(true)
	{
		++mValue;
		return  *this;
	}

	/// Post-increment operator.
	SelfType operator++() noexcept(true)
	{
		SelfType cache = *this;
		++mValue;

		return cache;
	}

	/// Pre-decrement operator.
	SelfType& operator--(int) noexcept(true)
	{
		--mValue;
		return  *this;
	}

	/// Post-decrement operator.
	SelfType operator--() noexcept(true)
	{
		SelfType cache = *this;
		--mValue;

		return cache;
	}

	/// Self scalar multiplication operator.
	template<typename RhsFloatType>
	SelfType& operator*=(const RhsFloatType rhsFloat) noexcept(true)
	{
		mValue *= static_cast<FloatType>(rhsFloat);
		return *this;
	}

	/// Self scalar division operator.
	template<typename  RhsFloatType>
	SelfType& operator/(const RhsFloatType rhs) noexcept(true)
	{
		mValue /= rhs;
		return *this;
	}

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
	/// Befriend all possible instances of the @class PhysicalQuantityVector so that the member value
	//  is available across all instances.
	template<typename OtherPhysicalUnits, typename OtherFloatType> friend class PhysicalQuantityVector;

	/// Befriend operator to add physical quantities of same physical units but possibly different float
	/// representation.
	template<typename LhsFloatType, typename RhsFloatType>
	friend PhysicalQuantityVector<PhysicalUnits, LhsFloatType> operator+(
			const PhysicalQuantityVector<PhysicalUnits, LhsFloatType> lhs,
			const PhysicalQuantityVector<PhysicalUnits, RhsFloatType> rhs) noexcept (true);

	/// Befriend operator to subtract physical quantities of same physical units but possibly different float
	/// representation.
	template<typename PhysicalUnitsType, typename LhsFloatType, typename RhsFloatType>
	friend PhysicalQuantityVector<PhysicalUnitsType, LhsFloatType> operator-(
			const PhysicalQuantityVector<PhysicalUnitsType, LhsFloatType> lhs,
			const PhysicalQuantityVector<PhysicalUnitsType, RhsFloatType> rhs) noexcept (true);


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