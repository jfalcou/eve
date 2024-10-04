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
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/next.hpp>

namespace eve
{
  template<typename Options>
  struct epsilon_t : elementwise_callable<epsilon_t, Options, upward_option, downward_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((T), a);
    }

    EVE_CALLABLE_OBJECT(epsilon_t, epsilon_);
  };

//================================================================================================
//! @addtogroup core_fma_internal
//! @{
//!   @var epsilon
//!   @brief `elementwise_callable` object computing the distance of the absolute value of the parameter
//!    to the next representable element of its type.
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
//!      constexpr auto epsilon(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto epsilon[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto epsilon[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto abs[downward](value auto x)                    noexcept; // 1
//!      constexpr auto abs[upward](value auto x)                      noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. The distance of abs(x) to the next representable element in the type of `x`. (Kahan-Harrisson definition)
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The distance of abs(x) to the previous representable element in the type of `x`. (Goldberg definition)
//!
//!  @groupheader{External references}
//!   *  [wikipedia](//!https://en.wikipedia.org/wiki/Unit_in_the_last_place)
//!   *  [HAL: On the definition of ulp(x)](https://hal.science/inria-00070503)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/epsilon.cpp}
//================================================================================================
  inline constexpr auto epsilon = functor<epsilon_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto epsilon_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(integral_value<T>)
        return T(1);
      else
      {
        auto aa = eve::abs(a0);
        if constexpr(O::contains(downward))
          return dist[is_finite(aa)](aa, prev(aa));
        else // upward is the default
          return dist[is_finite(aa)](aa, next(aa));
      }
    }
  }
}
