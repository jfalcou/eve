//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqpz.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_pinf.hpp>
#include <eve/module/core/regular/is_positive.hpp>
#include <eve/module/core/regular/is_negative.hpp>
#include <eve/module/core/regular/is_normal.hpp>
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve
{
  template<typename Options>
  struct nextint_t : strict_elementwise_callable<nextint_t, Options, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(nextint_t, nextint_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var nextint
//!   @brief Computes the next representable integer.
//!
//!   **Defined in Header**
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
//!      // Regular overloads
//!      constexpr auto nextint(value auto x)                                              noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto nextint[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
//!      constexpr auto nextint[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto nextint[raw](value auto x)                                         noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!       1. the smallest representable integer value greater than `x` is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional)
//!       3. works only if inputs are normal numbers (this excludes floating zeroes, denormals or not finite).
//!          the option has no influence on the two parameters calls
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/nextint.cpp}
//================================================================================================
  inline constexpr auto nextint = functor<nextint_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {
    template<callable_options O, typename... Ts>
    EVE_FORCEINLINE constexpr auto nextint_(EVE_REQUIRES(emulated_), O const& o, Ts... ts) noexcept
      requires (_::fp16_should_apply<common_value_t<Ts...>>)
    {
      return nextint_(EVE_TARGETS(cpu_), o, ts...);
    }

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T nextint_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
    {
      if constexpr (eve::floating_value<T>)
      {
        auto ni = ceil(next[opts](v));
        if (!O::contains(raw)) ni = if_else(is_nan(v), nan(as(v)), ni);
        return ni;
      }
      else                                  return next[opts](v);
    }
  }
}
