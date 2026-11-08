# MAZ Mathematical Standard Library Specification (`maz.math`)
**Status:** Living Standard Library Specification  
**Version:** 1.0  
**Language:** MAZ (MZ)

---

## 1. Overview & Architecture

The MAZ Mathematical Standard Library provides a comprehensive, high-performance computational toolkit inspired by C++'s `<cmath>`, `<numeric>`, and `<numbers>` alongside Python's `math` module.

### Core Architectural Principles:
1. **Zero-Overhead Native Implementation:** High-performance algorithms implemented in C++20 standard library routines with clean MAZ bindings.
2. **Modular Organization:** Exposed through the modular `maz.math` namespace (with submodules `maz.math.trig`, `maz.math.nt`, `maz.math.comb`, `maz.math.stats`, `maz.math.geo`, `maz.math.random`, `maz.math.complex`, `maz.math.numerical`).
3. **Type Strictness:** Integer functions (`gcd`, `lcm`, `factorial`, `popcount`) return `int` (64-bit). Floating-point functions (`sqrt`, `sin`, `exp`) return `float` (IEEE-754 double precision).
4. **Defined Domain Behavior:** Errors like `sqrt(-1)` or `log(0)` throw informative MAZ runtime exceptions or return IEEE `NaN` / `INF` based on configuration, never silently corrupting state.

---

## 2. The 15 Standard Categories

### Category 1: Basic Mathematical Functions
| Function | Signature | Description |
|---|---|---|
| `abs(x)` | `abs(x: num) -> num` | Computes the absolute value of integer or float. |
| `min(a, b)` | `min(a: num, b: num) -> num` | Returns the minimum of two values. |
| `max(a, b)` | `max(a: num, b: num) -> num` | Returns the maximum of two values. |
| `pow(x, y)` | `pow(x: num, y: num) -> float` | Computes $x^y$. |
| `sqrt(x)` | `sqrt(x: num) -> float` | Square root; throws domain error for negative values. |
| `cbrt(x)` | `cbrt(x: num) -> float` | Cube root of $x$. |
| `hypot(x, y)` | `hypot(x: num, y: num) -> float` | Computes $\sqrt{x^2 + y^2}$ avoiding intermediate overflow. |
| `sign(x)` | `sign(x: num) -> int` | Returns `-1` for negative, `0` for zero, `1` for positive. |
| `square(x)` | `square(x: num) -> num` | Computes $x \times x$. |
| `clamp(x, min, max)` | `clamp(x: num, min: num, max: num) -> num` | Restricts value between bounds. |
| `fma(a, b, c)` | `fma(a: num, b: num, c: num) -> float` | Fused multiply-add ($a \times b + c$) with single rounding step. |

### Category 2: Rounding & Conversion
| Function | Signature | Description |
|---|---|---|
| `round(x)` | `round(x: float) -> int` | Round to nearest integer (halfway cases away from zero). |
| `floor(x)` | `floor(x: float) -> int` | Largest integer not greater than $x$. |
| `ceil(x)` | `ceil(x: float) -> int` | Smallest integer not less than $x$. |
| `trunc(x)` | `trunc(x: float) -> int` | Truncates decimal fractional part towards zero. |
| `round_to(x, n)` | `round_to(x: float, n: int) -> float` | Rounds $x$ to $n$ decimal places. |
| `frac(x)` | `frac(x: float) -> float` | Returns fractional part $x - \mathrm{trunc}(x)$. |
| `mod(x, y)` | `mod(x: float, y: float) -> float` | Floating-point remainder equivalent to IEEE remainder. |
| `is_integer(x)` | `is_integer(x: float) -> bool` | Returns `true` if $x$ has no fractional component. |

### Category 3: Trigonometry & Hyperbolics
*Default angle unit: Radians.*
| Function | Signature | Description |
|---|---|---|
| `sin(x)` / `cos(x)` / `tan(x)` | `(x: float) -> float` | Standard trigonometric operations. |
| `asin(x)` / `acos(x)` / `atan(x)` | `(x: float) -> float` | Inverse trigonometric operations. |
| `atan2(y, x)` | `(y: float, x: float) -> float` | Quadrant-correct two-argument arctangent. |
| `sinh(x)` / `cosh(x)` / `tanh(x)` | `(x: float) -> float` | Hyperbolic functions. |
| `asinh(x)` / `acosh(x)` / `atanh(x)` | `(x: float) -> float` | Inverse hyperbolic functions. |
| `radians(deg)` | `(deg: float) -> float` | Degrees to radians conversion. |
| `degrees(rad)` | `(rad: float) -> float` | Radians to degrees conversion. |

### Category 4: Exponential & Logarithmic
| Function | Signature | Description |
|---|---|---|
| `exp(x)` | `exp(x: float) -> float` | $e^x$. |
| `exp2(x)` | `exp2(x: float) -> float` | $2^x$. |
| `expm1(x)` | `expm1(x: float) -> float` | $e^x - 1$ accurate for values near 0. |
| `log(x)` | `log(x: float) -> float` | Natural logarithm ($\ln x$). |
| `log10(x)` | `log10(x: float) -> float` | Base-10 logarithm ($\log_{10} x$). |
| `log2(x)` | `log2(x: float) -> float` | Base-2 logarithm ($\log_2 x$). |
| `log1p(x)` | `log1p(x: float) -> float` | $\ln(1 + x)$ accurate for values near 0. |
| `log_base(x, b)` | `log_base(x: float, b: float) -> float` | Arbitrary base logarithm $\frac{\ln x}{\ln b}$. |

### Category 5: Number Theory & Integer Math (Competitive Programming)
| Function | Signature | Description |
|---|---|---|
| `gcd(a, b)` | `gcd(a: int, b: int) -> int` | Greatest common divisor using Euclidean algorithm. |
| `lcm(a, b)` | `lcm(a: int, b: int) -> int` | Least common multiple. |
| `factorial(n)` | `factorial(n: int) -> int` | Factorial $n!$. |
| `is_prime(n)` | `is_prime(n: int) -> bool` | Primality test ($O(\sqrt{n})$ or deterministic Miller-Rabin). |
| `next_prime(n)` | `next_prime(n: int) -> int` | First prime strictly greater than $n$. |
| `prev_prime(n)` | `prev_prime(n: int) -> int` | Greatest prime strictly less than $n$. |
| `is_even(n)` / `is_odd(n)` | `(n: int) -> bool` | Parity checks. |
| `is_power_of_two(n)` | `(n: int) -> bool` | Bit-level power of two check. |
| `is_perfect_square(n)` | `(n: int) -> bool` | Exact integer square check. |
| `coprime(a, b)` | `coprime(a: int, b: int) -> bool` | Returns `true` if $\gcd(a, b) == 1$. |
| `mod_pow(a, b, m)` | `mod_pow(a: int, b: int, m: int) -> int` | Modular exponentiation ($a^b \pmod m$) in $O(\log b)$. |
| `mod_inverse(a, m)` | `mod_inverse(a: int, m: int) -> int` | Modular multiplicative inverse using extended Euclidean algorithm. |

### Category 6: Combinatorics
| Function | Signature | Description |
|---|---|---|
| `nCr(n, r)` | `nCr(n: int, r: int) -> int` | Combinations $\binom{n}{r}$. |
| `nPr(n, r)` | `nPr(n: int, r: int) -> int` | Permutations $\frac{n!}{(n-r)!}$. |
| `fibonacci(n)` | `fibonacci(n: int) -> int` | $n$-th Fibonacci number ($O(n)$ or $O(\log n)$ matrix exponentiation). |
| `catalan(n)` | `catalan(n: int) -> int` | $n$-th Catalan number $C_n = \frac{1}{n+1} \binom{2n}{n}$. |
| `derangements(n)` | `derangements(n: int) -> int` | Subfactorial $!n$. |

### Category 7: Floating-Point Utilities
| Function | Signature | Description |
|---|---|---|
| `is_nan(x)` | `(x: float) -> bool` | Detects IEEE NaN. |
| `is_inf(x)` | `(x: float) -> bool` | Detects positive/negative infinity. |
| `is_finite(x)` | `(x: float) -> bool` | Detects finite numeric value. |
| `copysign(x, y)` | `(x: float, y: float) -> float` | Magniture of $x$ with sign of $y$. |
| `fmod(x, y)` | `(x: float, y: float) -> float` | Floating-point modulus. |

### Category 8: Statistical Functions
| Function | Signature | Description |
|---|---|---|
| `sum(arr)` | `(arr: list) -> num` | Sum of numeric collection. |
| `mean(arr)` | `(arr: list) -> float` | Arithmetic mean. |
| `median(arr)` | `(arr: list) -> float` | Middle value of sorted collection. |
| `variance(arr)` | `(arr: list) -> float` | Sample variance. |
| `stddev(arr)` | `(arr: list) -> float` | Standard deviation. |

### Category 9: Geometry Functions
| Function | Signature | Description |
|---|---|---|
| `distance(x1, y1, x2, y2)` | `(float, float, float, float) -> float` | 2D Euclidean distance. |
| `distance3(x1, y1, z1, x2, y2, z2)` | `6 floats -> float` | 3D Euclidean distance. |
| `area_circle(r)` | `(r: float) -> float` | $\pi r^2$. |
| `circumference(r)` | `(r: float) -> float` | $2\pi r$. |
| `area_triangle(b, h)` | `(b: float, h: float) -> float` | $0.5 \times b \times h$. |
| `volume_sphere(r)` | `(r: float) -> float` | $\frac{4}{3} \pi r^3$. |
| `lerp(a, b, t)` | `(a: float, b: float, t: float) -> float` | Linear interpolation $(1-t)a + tb$. |

### Category 10: Random Mathematics
| Function | Signature | Description |
|---|---|---|
| `random()` | `() -> float` | Uniform random float in $[0.0, 1.0)$. |
| `randint(a, b)` | `(a: int, b: int) -> int` | Random integer in inclusive range $[a, b]$. |
| `seed(n)` | `(n: int) -> void` | Initializes pseudo-random seed. |

### Category 11: Bitwise Mathematics
| Function | Signature | Description |
|---|---|---|
| `popcount(n)` | `(n: int) -> int` | Number of set 1-bits (Hamming weight). |
| `countl_zero(n)` | `(n: int) -> int` | Count leading zero bits (64-bit integer). |
| `countr_zero(n)` | `(n: int) -> int` | Count trailing zero bits. |
| `bit_length(n)` | `(n: int) -> int` | Minimum bit length required to represent $n$. |
| `rotate_left(n, k)` | `(n: int, k: int) -> int` | Circular bitwise left rotation. |
| `rotate_right(n, k)` | `(n: int, k: int) -> int` | Circular bitwise right rotation. |

### Category 12: Complex Numbers
*Representation: Value with real and imaginary parts.*
- `complex(re, im)`
- `real(z)`, `imag(z)`, `abs(z)`, `conjugate(z)`, `arg(z)`

### Category 13: Mathematical Constants
| Constant | Value | Description |
|---|---|---|
| `PI` | `3.14159265358979323846` | Archimedes' constant $\pi$. |
| `TAU` | `6.28318530717958647692` | Turn constant $2\pi$. |
| `E` | `2.71828182845904523536` | Euler's number $e$. |
| `SQRT2` | `1.41421356237309504880` | $\sqrt{2}$. |
| `SQRT3` | `1.73205080756887729352` | $\sqrt{3}$. |
| `LN2` | `0.69314718055994530941` | $\ln 2$. |
| `LN10` | `2.30258509299404568401` | $\ln 10$. |
| `INF` | `std::numeric_limits<double>::infinity()` | Positive infinity. |
| `NAN` | `std::numeric_limits<double>::quiet_NaN()` | Not-a-Number. |

### Category 14: Numerical Algorithms
- `solve_quadratic(a, b, c)`: Real roots of $ax^2 + bx + c = 0$.
- `bisection(f, a, b)`: Root finding via bisection.
- `integrate(f, a, b)`: Numerical quadrature (Simpson's 1/3 rule).

### Category 15: Units & Conversions
- `to_radians(x)`, `to_degrees(x)`
- `celsius_to_fahrenheit(c)`, `fahrenheit_to_celsius(f)`
- `km_to_miles(km)`, `miles_to_km(mi)`

---

## 3. Phased Implementation Roadmap

- **Phase 1 (Essential Foundation):** Categories 1, 2, 3, 4, 13 (Basics, Rounding, Trig, Logs, Constants, GCD/LCM).
- **Phase 2 (Competitive Programming):** Categories 5, 6, 11 (Prime checks, modular arithmetic, combinatorics, Fibonacci, bitwise).
- **Phase 3 (Scientific & Stats):** Categories 7, 8, 10 (Float inspection, statistics, random).
- **Phase 4 (Geometry & Engineering):** Categories 9, 15 (Distance, areas, angles, unit conversions).
- **Phase 5 (Advanced Analysis):** Categories 12, 14 (Complex numbers, numerical solvers).

