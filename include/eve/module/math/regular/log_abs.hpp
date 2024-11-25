//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct log_abs_t : elementwise_callable<log_abs_t, Options>
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(log_abs_t, log_abs_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var log_abs
//!
//! @brief Callable object computing the natural logarithm of the absolute value of the input.
//!
//!   **Defined in Header**
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
//!      constexpr auto log_abs(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto log_abs[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto log[logical_value auto m](floating_value auto x)        noexcept; // 2
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
//!    1. Returns [elementwise](@ref glossary_elementwise) the natural logarithm  of
//!       the absolute value of the input.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/log_abs.cpp}
//================================================================================================
  inline constexpr auto log_abs = functor<log_abs_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
      log_abs_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      return eve::log(eve::abs(x));
    }
  }
}
