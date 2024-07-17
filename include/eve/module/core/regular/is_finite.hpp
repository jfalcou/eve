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
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_finite_t : elementwise_callable<is_finite_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_finite_t, is_finite_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_finite
//!   @brief `elementwise callable` returning a logical true  if and only if the element is a finite value
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
//!      constexpr auto is_finite(floating_value auto x) noexcept;                 // 1
//!      constexpr auto is_finite(integral_value auto x) noexcept;                 // 2
//!
//!      // Lanes masking
//!      constexpr auto is_finite[conditional_expr auto c](value auto x) noexcept; // 3
//!      constexpr auto is_finite[logical_value auto m](value auto x)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [real argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. `is_finite(x)` is semantically  equivalent to `is_not_nan(x-x)`,
//!      2. Always returns true.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_finite.cpp}
//! @}
//================================================================================================
  inline constexpr auto is_finite = functor<is_finite_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_finite_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( is_logical_v<T> || integral_value<T>)
        return true_(eve::as(a));
      else
        return is_eqz(a - a);
    }
  }
}
