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
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_normal_t : elementwise_callable<is_normal_t, Options>
  {
    template<value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
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
//!      // Regular overloads
//!      constexpr auto is_normal(floating_value auto x) noexcept;                 // 1
//!      constexpr auto is_normal(integral_value auto x) noexcept;                 // 2
//!
//!      // Lanes masking
//!      constexpr auto is_normal[conditional_expr auto c](value auto x) noexcept; // 3
//!      constexpr auto is_normal[logical_value auto m](value auto x) noexcept;    // 3
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
//!     1. returns true if and only if `x` is [normal](https://mathworld.wolfram.com/Floating-PointNormalNumber.html)
//!     2. returns `x != 0`.
//!     3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_normal.cpp}
//================================================================================================
  inline constexpr auto is_normal = functor<is_normal_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T> is_normal_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr (integral_value<T>)
        return is_nez(a);
      else
        return is_finite(a) && (eve::abs(a) >= smallestposval(eve::as{a}));
    }
  }
}
