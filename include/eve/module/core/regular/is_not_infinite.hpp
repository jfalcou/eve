//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/regular/is_finite.hpp>
#include <eve/module/core/regular/is_nan.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_infinite_t : elementwise_callable<is_not_infinite_t, Options,  pedantic_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_not_infinite_t, is_not_infinite_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_infinite
//!   @brief `elementwise callable` returning a logical true  if and only if the element is not an infinite value
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
//!      constexpr auto is_not_infinite(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_not_infinite[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_not_infinite[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. The call `is_not_infinite(x)` is semantically  equivalent to `is_finite(x) || is_nan(x)`
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_not_infinite.cpp}
//================================================================================================
 inline constexpr auto is_not_infinite = functor<is_not_infinite_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_infinite_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return true_(as<T>{});
      else
        return eve::is_finite(a) || is_nan(a);
    }
  }
}
