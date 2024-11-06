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
#include <eve/module/math/regular/sinpi.hpp>

namespace eve
{
  template<typename Options>
  struct sind_t : elementwise_callable<sind_t, Options, quarter_circle_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sind_t, sind_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sind
//!
//! @brief `elementwise_callable` object computing the sine from an input in degrees.
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
//!      constexpr auto sind(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sind[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sind[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sind[quarter_circle](floating_value auto x)          noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) sine of the input expressed in degrees.
//!       In particular:
//!        * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, Nan is returned.
//!        * If the element is a `NaN`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. Assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Sine.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sind.cpp}
//================================================================================================
  inline constexpr auto sind = functor<sind_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sind_(EVE_REQUIRES(cpu_), O const& , T const& a0)
    {
      auto x = eve::abs(a0);
      if constexpr(O::contains(quarter_circle))
      {
        return  sinpi[eve::quarter_circle](div_180(a0));
      }
      else
      {
        if( eve::all(eve::abs(x) <= T(45)) )  return sind[quarter_circle](a0);
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return nan(eve::as<T>());
         x                  = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
        auto [fn, xr, dxr] = rem180(x);
        return sin_finalize(bitofsign(a0), fn, xr, dxr);
      }
    }
  }
}
