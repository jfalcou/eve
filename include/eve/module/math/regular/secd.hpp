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
  struct secd_t : elementwise_callable<secd_t, Options, quarter_circle_option, half_circle_option,
                                       full_circle_option, medium_option, big_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(secd_t, secd_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var secd
//!
//! @brief `elementwise_callable` object computing the secant from an input in degree.
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
//!      constexpr auto secd(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto secd[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto secd[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto secd[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto secd[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto secd[full_circle](floating_value auto x)             noexcept; // 3.c
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) secant of the input in degree.
//!       (the inverse of the sine). In particular:
//!        * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, Nan is returned.
//!        * If the element is a `NaN`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Secant.html)
//!
//!   @groupheader{Example}
//!  @groupheader{Example}
//================================================================================================
  inline constexpr auto secd = functor<secd_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T secd_(EVE_REQUIRES(cpu_), O const& o, T const& a0) noexcept
    {
      if constexpr( O::contains(quarter_circle2) )
        return eve::rec[pedantic2](eve::cosd[o](a0));
      else
      {
        auto a0_180 = div_180(a0);
        auto test   = is_not_flint(a0_180) && is_flint(a0_180 + mhalf(eve::as(a0_180)));
        if constexpr( scalar_value<T> ) // early return for nans in scalar case
        {
          if( test ) return nan(eve::as<T>());
        }
        return if_else(test, eve::allbits, rec[pedantic2](cosd[o](a0)));
      }
    }
  }
}
