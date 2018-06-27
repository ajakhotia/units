/*  Copyright 2017. All rights reserved by the author.
 *  Author: Anurag Jakhotia <anuragjakhotia@gmail.com>
 */

#include "buildInformation/buildInformation.h"

namespace cppYard
{
namespace buildInformation
{

std::ostream& operator<<(std::ostream& stream, const BuildType& buildType)
{
	switch(buildType)
	{
		case BuildType::Debug:
			stream << "Debug";
			return stream;
		case BuildType::Release:
			stream << "Release";
			return stream;
		case BuildType::RelWithDebInfo:
			stream << "RelWithDebInfo";
			return stream;
		case BuildType::MinSizeRel:
			stream << "MinSizeRel";
			return stream;
		default:
			throw std::invalid_argument("Invalid value provided for enumeration BuildType");
	}
}

} // End of namespace buildInformation.
} // End of namespace cppYard.