/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_finite.hpp>
#include <eve/module/core/regular/is_greater_equal.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_normal_t : elementwise_callable<is_normal_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_normal_t, is_normal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_normal
//!   @brief `elementwise callable` returning a logical true if and only if the element value is normal.
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
//!      constexpr auto is_normal(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_normal[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_normal[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The call `is_normal(x)` is semantically  equivalent to:
//!       @code
//!       if   constexpr(floating_value<T>) return (abs(x) >= smallestposval(as(x))) && is_finite(x);
//!       else constexpr(integral_value<T>) return false_(as(x));
//!       @endcode
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_normal.cpp}
//! @}
//================================================================================================
  inline constexpr auto is_normal = functor<is_normal_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_normal_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return is_nez(a);
      else
        return is_finite(a) && is_greater_equal(eve::abs(a), smallestposval(eve::as(a)));
    }
  }
}
