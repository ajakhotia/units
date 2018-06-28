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