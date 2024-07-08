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
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/regular/ceil.hpp>
#include <eve/module/core/regular/floor.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/trunc.hpp>

namespace eve
{
  template<typename Options>
  struct round_t : elementwise_callable<round_t, Options, upward_option, downward_option,
                                        to_nearest_option, toward_zero_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T x) const noexcept
    { return EVE_DISPATCH_CALL(x); }

    EVE_CALLABLE_OBJECT(round_t, round_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var round
//!   @brief Computes the integer nearest to the input.
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
//!      constexpr auto round(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto round[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto round[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto round[upward](floating_value auto x)         noexcept; // 3
//!      constexpr auto round[downward](floating_value auto x)       noexcept; // 4
//!      constexpr auto round[to_nearest](floating_value auto x)     noexcept; // 5
//!      constexpr auto round[toward_zero](floating_value auto x)    noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [real](@ref eve::value) argument.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
///!
//!    **Return value**
//!
//!     1. The integer nearest to `x`.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. equivalent to `ceil(x)`.
//!     4. equivalent to `floor(x)`.
//!     5. equivalent to `nearest(x)`.
//!     6. equivalent to `trunc(x)`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/round.cpp}
//! @}
//================================================================================================
  inline constexpr auto round = functor<round_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    round_(EVE_REQUIRES(cpu_), O const &, T const& x) noexcept
    {
      if constexpr(integral_value<T>)
        return x;
      else if constexpr(O::contains(downward2 ))
        return eve::floor(x);
      else if constexpr(O::contains(upward2)  )
        return eve::ceil(x);
      else if constexpr(O::contains(toward_zero2 ))
        return eve::trunc(x);
      else
        return nearest(x);
    }
  }
}
