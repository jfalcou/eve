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
#include <eve/module/math/regular/sind.hpp>

namespace eve
{
  template<typename Options>
  struct cscd_t : elementwise_callable<cscd_t, Options, quarter_circle_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cscd_t, cscd_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cscd
//! @brief `elementwise_callable` object computing the cosecant from an input in degree.
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
//!      constexpr auto cscd(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cscd[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cscd[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cscd[quarter_circle](floating_value auto x)          noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: [floating value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) cosecant of the input
//!       expressed in degree (the inverse of the sine). In particular:
//!        * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, Nan is returned.
//!        * If the element is a `NaN`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. Assumes that the inputs elements  belong to \f$[-45,45]\f$ and return NaN outside.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/cscd.cpp}
//================================================================================================
  inline constexpr auto cscd = functor<cscd_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cscd_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
        return eve::rec[pedantic](eve::sind[o](a0));
      else
      {
        auto a0_180 = div_180(a0);
        auto test   = is_nez(a0_180) && is_flint(a0_180);
        if constexpr( scalar_value<T> ) // early return for nans in scalar case
        {
          if( test ) return nan(eve::as<T>());
        }
        return if_else(test, eve::allbits, rec[pedantic](sind[o](a0)));
      }
    }
  }
}
