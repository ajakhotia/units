![units workflow name](https://github.com/ajakhotia/units/workflows/Master%20Unit%20Tests/badge.svg)

# Units
A type-safe representation of physical units with zero run-time overhead. The type safety is achieved by statically keeping track of the physical dimensions and the scale for the each type. The dimensions and scales are tracked using std::ratio, hence, the system is capable of representing non-integer powers of physical dimensions. Multiplicative operators are designed to handle type conversions correctly. Additive operators are defined only for physical quantities that have matching physical dimensions. The scale conversions are handled implicitly by the system.

## Examples

```
using namespace units;

const Metres m1(5.0);     // Has dimensions of (L^(1,0), M^(0,0), T^(0,0), I^(0,0), K^(0,0), N^(0,0), J^(0,0)) and scale (1/1)
const Inches i1(2.0);     // Has dimensions of (L^(1,0), M^(0,0), T^(0,0), I^(0,0), K^(0,0), N^(0,0), J^(0,0)) and scale (127/5000)

const auto l1 = m1 + i1;  // Has dimensions of (L^(1,0), M^(0,0), T^(0,0), I^(0,0), K^(0,0), N^(0,0), J^(0,0)) and scale (1/1)
                          // Inches will be appropriately converted into Metres.

const auto l2 = i1 + m1;  // Has dimensions of (L^(1,0), M^(0,0), T^(0,0), I^(0,0), K^(0,0), N^(0,0), J^(0,0)) and scale (127/5000)
                          // Metres will be appropriately converted into Inches.

const auto a1 = m1 * m1;  // Has dimensions of (L^(2,0), M^(0,0), T^(0,0), I^(0,0), K^(0,0), N^(0,0), J^(0,0)) and scale (1/1)
const auto a2 = m1 * i1;  // Has dimensions of (L^(2,0), M^(0,0), T^(0,0), I^(0,0), K^(0,0), N^(0,0), J^(0,0)) and scale (127/5000)
const auto a3 = i1 * i1;  // Has dimensions of (L^(2,0), M^(0,0), T^(0,0), I^(0,0), K^(0,0), N^(0,0), J^(0,0)) and scale (16129/25000000)

//m1 + a1;                // Illeagal operation. Won't compile. Cannot add length to area.
a2 + a3;                  // Legal operation. Both quantities have have same physical dimensions. Appropriate conversions will be done automatically.
a2 * i1                   // Has dimensions of (L^(3,0), M^(0,0), T^(0,0), I^(0,0), K^(0,0), N^(0,0), J^(0,0)) and scale (16129/25000000)

```

Note: The above examples show uses only for lengths, but the same concept is valid across all combinations of the 7 physical quantities. In short, all units can be multiplies or divided. Only the units that have same physical dimensions can be added, subtracted or be logically compared(==, !=, <, <=, >, >=).
