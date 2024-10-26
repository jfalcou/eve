//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/is_eqz.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_nan_t : elementwise_callable<is_not_nan_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_not_nan_t, is_not_nan_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_nan
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is not NaN
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
//!      constexpr auto is_not_nan(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_not_nan[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_not_nan[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. `is_not_nan(x)`  is semantically  equivalent to:
//!        `is_equal(x, x)` in particular this is always true for integral types.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_not_nan.cpp}
//================================================================================================
  inline constexpr auto is_not_nan = functor<is_not_nan_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_nan_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr(integral_value<T>) return true_(eve::as(a));
      else                            return a == a;
    }
  }
}
