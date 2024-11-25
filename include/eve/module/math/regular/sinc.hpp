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
#include <eve/module/math/regular/sin.hpp>

namespace eve
{
  template<typename Options>
  struct sinc_t : elementwise_callable<sinc_t, Options, quarter_circle_option, half_circle_option, full_circle_option, medium_option, big_option>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sinc_t, sinc_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sinc
//!
//! @brief `elementwise_callable` object computing the sine cardinal.
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
//!      constexpr auto sinc(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sinc[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sinc[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) sine of the input divided by the input.
//!       In particular:
//!       * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, 0 is returned.
//!       * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://fr.wikipedia.org/wiki/Sinus_cardinal)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/SineCardinalFunction.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sinc.cpp}
//================================================================================================
 inline constexpr auto sinc = functor<sinc_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sinc_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return one(eve::as(a0));
        if constexpr( eve::platform::supports_infinites )
          if( is_infinite(a0) ) return zero(eve::as<T>());
        if constexpr( eve::platform::supports_denormals )
          return eve::abs(a0) < eps(eve::as<T>()) ? one(eve::as<T>()) : sin(a0) / a0;
        else return sin[o](a0) / a0;
      }
      else
      {
        auto r1 = sin[o](a0) / a0;
        if constexpr( eve::platform::supports_denormals )
        {
          r1 = if_else(eve::abs(a0) < eps(as<T>()), one(eve::as<T>()), r1);
        }
        else r1 = if_else(is_eqz(a0), one(eve::as<T>()), r1);
        if constexpr( eve::platform::supports_infinites )
          r1 = if_else(is_infinite(a0), eve::zero, r1);
        return r1;
      }
    }
  }
}
