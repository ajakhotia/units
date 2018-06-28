/*  Copyright 2018. All rights reserved by the author.
 *  Author: Anurag Jakhotia <anuragjakhotia@gmail.com>
 */
#pragma once

#include "physicalDimensions.h"

namespace cppYard
{
namespace units
{

/**
 * @brief	Template class to represent a physical units.
 *
 * @tparam	PhysicalDimensions_	The physical dimensions of the unit of measurement.
 *
 * @tparam	Scale_				The ratio which when multiplied with physical unit the unit converts it to
 *                              its SI counterpart.
 * 								TIP: Read it as ScaleToSI.
 */
template<typename PhysicalDimensions_, typename Scale_>
class PhysicalUnits
{
public:
	/// Alias of the physical dimensions of the represented unit.
	using PhysicalDimensions = PhysicalDimensions_;

	/// Alias of the scale to SI of the represented unit. PhysicalUnit * Scale = SI-equivalent unit.
	using Scale = Scale_;

	/// Alias of self type.
	using SelfType = PhysicalUnits<PhysicalDimensions, Scale>;

	/// Deleted constructors and destructors.
	PhysicalUnits() = delete;

	PhysicalUnits(const PhysicalUnits&) = delete;

	PhysicalUnits(PhysicalUnits&&) = delete;

	~PhysicalUnits() = delete;

	/// Deleted assignment operators.
	SelfType& operator=(const SelfType&) = delete;

	SelfType& operator=(SelfType&&) = delete;
};

/**
 * @brief	Statically computes a std::ratio and the corresponding float that converts RHS physical unit
 *          to the appropriate value in LHS' scale.
 *
 * @tparam	LhsPhysicalUnits_	LHS / Destination physical units type.
 *
 * @tparam	RhsPhysicalUnits_	RHS / Source physical units type.
 *
 * @tparam	FloatType_			Floating point representation to be used for representing the
 *                              resulting conversion ratio.
 *
 */
template<typename LhsPhysicalUnits_, typename RhsPhysicalUnits_, typename FloatType_>
class PhysicalUnitsConversionHelper
{
public:
	/// Alias of the LHS physical unit.
	using LhsPhysicalUnits = LhsPhysicalUnits_;

	/// Alias of the RHS physical unit.
	using RhsPhysicalUnits = RhsPhysicalUnits_;

	/// Alias of the Float type to represent the ratio.
	using FloatType = FloatType_;

	// Assert same physical dimensions for operand physical units.
	static_assert(std::is_same<typename LhsPhysicalUnits::PhysicalDimensions,
				  				typename RhsPhysicalUnits::PhysicalDimensions>::value,
				"Requested scale computation for physical units of different physical dimensions.");

	/// Alias of self-type.
	using SelfType = PhysicalUnitsConversionHelper<LhsPhysicalUnits, RhsPhysicalUnits, FloatType>;

	/// Scaling factor as a std::ratio to convert RHS physical unit type to LHS physical units type.
	using Result = std::ratio_divide<typename RhsPhysicalUnits::Scale, typename LhsPhysicalUnits::Scale>;

	static constexpr const FloatType kFloatRatio{
		static_cast<FloatType>(Result::num) / static_cast<FloatType>(Result::den)};


	/// Deleted constructor and destructors.
	PhysicalUnitsConversionHelper() = delete;

	PhysicalUnitsConversionHelper(const PhysicalUnitsConversionHelper&) = delete;

	PhysicalUnitsConversionHelper(PhysicalUnitsConversionHelper&&) = delete;

	~PhysicalUnitsConversionHelper() = delete;

	/// Deleted assignment operators.
	SelfType& operator=(const SelfType&) = delete;

	SelfType& operator=(SelfType&&) = delete;
};

template<typename LhsPhysicalUnits_, typename RhsPhysicalUnits_>
class MultiplyPhysicalUnits
{
public:
	/// Alias of LHS physical units.
	using LhsPhysicalUnits = LhsPhysicalUnits_;

	/// Alias of the RHS physical units.
	using RhsPhysicalUnits = RhsPhysicalUnits_;

	/// Alias of self type for convenience.
	using SelfType = MultiplyPhysicalUnits<LhsPhysicalUnits, RhsPhysicalUnits>;

	/// Resulting physical units that is a multiplication of LHS and RHS.
	using Result = PhysicalUnits<
			typename MultiplyPhysicalDimensions<typename LhsPhysicalUnits::PhysicalDimensions,
					                            typename RhsPhysicalUnits::PhysicalDimensions>::Result,
			typename std::ratio_multiply<typename LhsPhysicalUnits::Scale, typename RhsPhysicalUnits::Scale>>;

	/// Deleted constructor and destructors.
	MultiplyPhysicalUnits() = delete;

	MultiplyPhysicalUnits(const MultiplyPhysicalUnits&) = delete;

	MultiplyPhysicalUnits(MultiplyPhysicalUnits&&) = delete;

	~MultiplyPhysicalUnits() = delete;

	/// Deleted assignment operators.
	SelfType& operator=(const SelfType&) = delete;

	SelfType& operator=(SelfType&&) = delete;
};

template<typename LhsPhysicalUnits_, typename RhsPhysicalUnits_>
class DividePhysicalUnits
{
public:
	/// Alias of LHS physical units.
	using LhsPhysicalUnits = LhsPhysicalUnits_;

	/// Alias of the RHS physical units.
	using RhsPhysicalUnits = RhsPhysicalUnits_;

	/// Alias of self type for convenience.
	using SelfType = DividePhysicalUnits<LhsPhysicalUnits, RhsPhysicalUnits>;

	/// Resulting physical units that is a multiplication of LHS and RHS.
	using Result = PhysicalUnits<
			typename DividePhysicalDimensions<typename LhsPhysicalUnits::PhysicalDimensions,
					                         typename RhsPhysicalUnits::PhysicalDimensions>::Result,
			typename std::ratio_divide<typename LhsPhysicalUnits::Scale, typename RhsPhysicalUnits::Scale>>;

	/// Deleted constructor and destructors.
	DividePhysicalUnits() = delete;

	DividePhysicalUnits(const DividePhysicalUnits&) = delete;

	DividePhysicalUnits(DividePhysicalUnits&&) = delete;

	~DividePhysicalUnits() = delete;

	/// Deleted assignment operators.
	SelfType& operator=(const SelfType&) = delete;

	SelfType& operator=(SelfType&&) = delete;
};


} // End of namespace units.
} // End of namespace cppYard.