[![docker-image](https://github.com/ajakhotia/units/actions/workflows/docker-image.yaml/badge.svg)](https://github.com/ajakhotia/units/actions/workflows/docker-image.yaml)

# 📐 Units

> 🛰️ In 1999, the Mars Climate Orbiter crashed because someone mixed metres and feet.
> `units` would have converted it for you.

`units` lets you attach physical units to numbers in C++ and have the compiler stop you from
mixing them up:

```cpp
Metres(5.0) + Feet(2.0)       // ✅ a length (conversion handled automatically)
Metres(5.0) + Kilograms(2.0)  // ❌ build error, not a silent bug at run time
```

The generated machine code is the same as if you had used plain `double`s, so the safety is free.

Under the hood, every physical quantity that has ever been measured can be expressed as a
combination of seven fundamental dimensions:

| Symbol | Dimension               |
|--------|-------------------------|
| 📏     | **Length**              |
| ⚖️     | **Mass**                |
| ⏱️     | **Time**                |
| ⚡      | **Electric current**    |
| 🌡️    | **Temperature**         |
| 🧪     | **Amount of substance** |
| 💡     | **Luminous intensity**  |

`units` encodes those seven exponents directly in the C++ type of each quantity and only permits
operations between dimensionally compatible types. Multiplications and divisions compose the
exponents in the result type, so `Metres * Metres` is an area, `Metres / Seconds`
is a speed, and so on — no annotations needed.

All the bookkeeping is done at compile time via `std::ratio`, so the generated code is
indistinguishable from hand-written arithmetic on `double`.

## ✨ Features

- **Dimensions in the type system.** The seven SI base exponents are template parameters of every
  quantity; mismatched dimensions are a build failure, not a runtime crash.
- **Implicit scale conversion.** Mixing metres and inches, or kilograms and pounds, just works.
- **Derived dimensions for free.** `Metres * Seconds`, `Kilograms / Metres`, etc. produce
  correctly-dimensioned types automatically.
- **Non-integer exponents.** Dimensions are tracked with `std::ratio`, so fractional powers
  (e.g. `sqrt(area)`) round-trip through the type system.
- **Zero runtime overhead.** Operations compile down to the underlying scalar arithmetic.
- **C++14 and up.** Header-only; no link dependencies.
- **Predefined units.** SI base units (`Metres`, `Kilograms`, `Seconds`, `Amperes`,
  `KelvinTemperatureDifference`, `Moles`, `Candela`, `Radians`) and a small Imperial set
  (`Inches`, `Feet`, `Pounds`). Custom units are a one-line `using` declaration.

## 💡 Example

```cpp
#include <units/si.hpp>
#include <units/imperial.hpp>

using namespace units;

const auto m1 = Metres(5.0);    // type(m1): Metres (a length, expressed in metres)
const auto i1 = Inches(2.0);    // type(i1): Inches (a length, expressed in inches)

const auto l1 = m1 + i1;        // type(l1): Metres   — i1 is converted to metres before the add
const auto l2 = i1 + m1;        // type(l2): Inches   — m1 is converted to inches before the add

const auto a1 = m1 * m1;        // type(a1): area, expressed in metres²
const auto a2 = m1 * i1;        // type(a2): area, expressed in metre·inch (still a length², just a different scale)

const auto a3 = a2 + a1;        // type(a3): same as type(a2) (area in metre·inch) — a1 is converted into a2's scale
// const auto bad = m1 + a1;    // compile error: cannot add a length to an area

const auto v1 = a2 * i1;        // type(v1): volume (length³), expressed in metre·inch²
```

The same rules apply across all dimensions — multiplication and division compose freely; addition,
subtraction, and comparison (`==`, `!=`, `<`, `<=`, `>`, `>=`) require matching physical dimensions.

## 🛠️ Requirements

- A C++14 (or newer) compiler.
- CMake 3.27 or newer if you build/install the project; consumers who pull in headers directly need
  only their own build system.

## 🚀 Using units in your project

There are two supported integration paths.

### 📦 Option 1: install with CMake, then `find_package`

Build and install once on your system:

```bash
git clone --recurse-submodules https://github.com/ajakhotia/units.git
cd units
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build   build
cmake --install build
```

`-DCMAKE_INSTALL_PREFIX=<path>` at configure time picks an install location other than the default.
The install drops `unitsConfig.cmake` and `unitsTargets.cmake` under
`<install-prefix>/lib/cmake/units/`. Then in your project:

```cmake
find_package(units REQUIRED)

target_link_libraries(<your-target> PRIVATE Units::units)
```

If you installed to a non-standard prefix, point CMake at it via `-DCMAKE_PREFIX_PATH=<prefix>`
when configuring your project.

### 🧩 Option 2: vendor as a git submodule

Add both `units` and `infraCommons` as submodules of your project. `infraCommons` is required
because `units` uses the `add_exported_library` helper from it to declare its target.

```bash
git submodule add https://github.com/ajakhotia/infraCommons.git external/infraCommons
git submodule add https://github.com/ajakhotia/units.git        external/units
git submodule update --init --recursive
```

In your top-level `CMakeLists.txt`, include `exportedTargets.cmake` under a
`PROJECT_IS_TOP_LEVEL` guard before pulling in `units`:

```cmake
cmake_minimum_required(VERSION 3.27)
project(myProject LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(external/infraCommons/cmake/utilities/exportedTargets.cmake)
endif()

add_subdirectory(external/units)

target_link_libraries(<your-target> PRIVATE Units::units)
```

This mirrors the pattern used in `units`' own `CMakeLists.txt`. The
`if(PROJECT_IS_TOP_LEVEL)` guard means each repository takes ownership of its own project-level
tooling only when it is built standalone; when it is consumed as a submodule, the parent project
owns those concerns.

## 📜 License

See [`LICENSE`](LICENSE).
