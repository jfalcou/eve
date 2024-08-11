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

namespace eve
{
 template<typename Options>
  struct ulp_t : elementwise_callable<ulp_t, Options, downward_option, upward_option>
  {
    template<value T>
    EVE_FORCEINLINE constexpr T operator()(T a) const noexcept
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(ulp_t, ulp_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var ulp
//!   @brief Computes the unit in the last place of its argument,  that is the distance to the nearest representable value
//!   not equal to the argument
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto ulp(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ulp[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto ulp[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto abs[downward](value auto x)                noexcept; // 1
//!      constexpr auto abs[upward](value auto x)                  noexcept; // 3
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. Computes [elementwise](@ref glossary_elementwise) the 'unit in the last place'
//!         between `x` and `next(x)`. (Kahan-Harrisson definitionn)
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3  Computes [elementwise](@ref glossary_elementwise) the 'unit in the last place'
//!         between `x` and `pred(x)`. (Goldberg definition)
//!
//!  @note the `upward` and `downward` only differ if x is a power of 2.
//!
//!  @groupheader{External references}
//!   *  [wikipedia](//!https://en.wikipedia.org/wiki/Unit_in_the_last_place)
//!   *  [Inria](https://hal.science/inria-00070503)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/ulp.cpp}
//================================================================================================
  inline constexpr auto ulp = functor<ulp_t>;
//================================================================================================
//! @}
//================================================================================================


  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T ulp_(EVE_REQUIRES(cpu_), O const&, T x)
    {
      if constexpr( integral_value<T> )
      {
        return one(as(x));
      }
      else
      {
        auto s = ieee_constant<0x1.000002p-24f, 0x1.0000000000001p-53>(as(x));
        if constexpr(O::contains(downward2))
          return eve::abs(fms(s, x, x)+x);
        else
          return eve::abs(fma(s, x, x)-x);
      }
    }
  }
}
