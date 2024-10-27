//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct flush_denormal_t : elementwise_callable<flush_denormal_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(flush_denormal_t, flush_denormal_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var flush_denormal
//!   @brief `elementwise_callable` object computing flushing denormal values to 0.
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
//!      constexpr auto flush_denormal(value auto x)                          noexcept; // 1
//!      // Lanes masking
//!      constexpr auto flush_denormal[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto flush_denormal[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!   1. denormal values are flushed to zero.
//!   2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Subnormal_number)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/core/flush_denormal.cpp}
//================================================================================================
  inline constexpr auto flush_denormal = functor<flush_denormal_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    flush_denormal_(EVE_REQUIRES(cpu_), O const &, T const& x) noexcept
    {
      return if_else(is_denormal(x), zero, x);
    }
  }
}
