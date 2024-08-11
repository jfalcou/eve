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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/cospi.hpp>

namespace eve
{
  template<typename Options>
  struct secpi_t : elementwise_callable<secpi_t, Options, quarter_circle_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(secpi_t, secpi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var secpi
//!
//! @brief `elementwise_callable` object computing secant from an input in \f$\pi\f$ multiples.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto secpi(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto secpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto secpi[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto secpi[quarter_circle](floating_value auto x)          noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!      * `x`: [floating value](@ref floating_value).
//!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) secant of the input
//!       expressed in \f$\pi\f$ multiples. The call `secpi(x)` is equivalent to \f$\sec(\pi x)\f$.
//!       In particular:
//!         * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!         * If the element is \f$\pm\infty\f$, Nan is returned.
//!         * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. Assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Secant.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/secpi.cpp}
//================================================================================================
  inline constexpr auto secpi = functor<secpi_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T secpi_(EVE_REQUIRES(cpu_), O const& o, T a0) noexcept
    {
      if constexpr(O::contains(quarter_circle2))
      {
        auto x    = abs(a0);
        auto test = is_not_less_equal(x, T(0.25));
        if constexpr( scalar_value<T> )
        {
          if( test ) return nan(eve::as<T>());
        }
        else { a0 = if_else(test, eve::allbits, a0); }

        a0 *= pi(eve::as<T>());
        auto x2 = sqr(a0);
        return rec[pedantic](cos_eval(x2));
      }
      else
      {
        const T x = eve::abs(a0);
        if constexpr( scalar_value<T> )
        {
          if( is_not_finite(x) ) return nan(eve::as<T>());
          if( x > maxflint(eve::as<T>()) ) return T(1);
        }

        T z = cospi[o](x);
        if constexpr( scalar_value<T> ) { return (z) ? rec[pedantic](z) : nan(eve::as<T>()); }
        else { return if_else(is_nez(z) && is_finite(a0), rec[pedantic](z), eve::allbits); }
      }
    }
  }
}
