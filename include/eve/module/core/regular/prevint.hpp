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
  struct prevint_t : strict_elementwise_callable<prevint_t, Options, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(prevint_t, prevint_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var prevint
//!   @brief Computes the previous representable integer.
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
//!      constexpr auto prevint(value auto x)                                              noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto prevint[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
//!      constexpr auto prevint[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto prevint[raw](value auto x)                                         noexcept; // 3
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
//!       1. The greatest representable integer value less than `x` is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional)
//!       3. works only if inputs are normal numbers (this excludes floating zeroes, denormals or not finite).
//!          the option has no influence on the two parameters calls
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/prevint.cpp}
//================================================================================================
  inline constexpr auto prevint = functor<prevint_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {
    template<callable_options O, typename... Ts>
    EVE_FORCEINLINE constexpr auto prevint_(EVE_REQUIRES(emulated_), O const& o, Ts... ts) noexcept
      requires (_::fp16_should_apply<common_value_t<Ts...>>)
    {
      return prevint_(EVE_TARGETS(cpu_), o, ts...);
    }

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T prevint_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
    {
      if constexpr (eve::floating_value<T>)
      {
        auto ni = floor(prev[opts](v));
        if (!O::contains(raw)) ni = if_else(is_nan(v), nan(as(v)), ni);
        return ni;
      }
      else                                  return prev[opts](v);
    }
  }
}
