//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/special/regular/factorial.hpp>
#include <eve/module/special/regular/tgamma.hpp>

namespace eve
{
  template<typename Options>
  struct double_factorial_t : elementwise_callable<double_factorial_t, Options>
  {
    template<eve::unsigned_value T>
    EVE_FORCEINLINE constexpr
    as_wide_as_t<double, T >
    operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(double_factorial_t, double_factorial_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var double_factorial
//!   @brief elementwise_callable` object computing the double factorial of `n`
//!
//!   THe double factorial is defined as \f$\displaystyle (2n)!! =
//!   \prod_{i=1}^n (2i)\f$ and \f$\displaystyle (2n+1)!! = \prod_{i=0}^n (2i+1)\f$
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      template <unsigned_value T> constexpr as_wide_as_t<double,T> double_factorial(T x) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto double_factorial[conditional_expr auto c](unsigned_value auto x)    noexcept; // 2
//!      constexpr auto double_factorial[logical_value auto m](unsigned_value auto x)       noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: unsigned argument.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. The value of the double factorial of `n` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/DoubleFactorial.html)
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/double_factorial.cpp}
//================================================================================================
  inline constexpr auto double_factorial = functor<double_factorial_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE
    as_wide_as_t<double, T>
    double_factorial_(EVE_REQUIRES(cpu_), O const&, T i0) noexcept
    {
      auto odd = [](auto i){
        auto n    = i >> 1;
        auto r    = (factorial(i) / ldexp(factorial(n), n));
        auto test = i <= 171;
        if( eve::all(test) ) return r;
        else
        {
          constexpr double invsqrtpi = 0.564189583547756286948079451560772585844050629329;
          auto             r1        = tgamma(fma(convert(i, as<double>()), 0.5, 1.0)) * invsqrtpi;
          return if_else(test, r, ldexp(r1, inc(i) >> 1));
        }
      };

      auto even = [](auto i){
        auto n = i >> 1;
        auto r = factorial(n);
        return ldexp(r, n);
      };
      auto i       =  convert(i0, as<uint64_t>());
      auto r       = inf(as<decltype(factorial(i))>()); // perhaps 0 should be fine
      auto notdone = i <= 300;
      notdone      = next_interval(odd, notdone, is_odd(i), r, i);
      if( eve::any(notdone) ) { last_interval(even, notdone, r, i); }
      return r;
    }
  }
}
