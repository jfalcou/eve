//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/constant/maxflint.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/frac.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_flint_t : elementwise_callable<is_not_flint_t, Options,  pedantic_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_not_flint_t, is_not_flint_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_flint
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is a floating value
//!   not representing an integer
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
//!      constexpr auto is_not_flint(floating_value auto x) ;               noexcept  // 1
//!      constexpr auto is_not_flint(integer_value auto x)                  noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto is_not_flint[conditional_expr auto c](value auto x) noexcept; // 3
//!      constexpr auto is_not_flint[logical_value auto m](value auto x)    noexcept; // 3
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
//!      1. The call `is_not_flint(x)` is semantically  equivalent to: `is_nez(frac (x))`;
//!         This means that x  does not represent an integer (flint is a shorcut for 'floating integer').
//!      2. Always returns `false`.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_not_flint.cpp}
//================================================================================================
  inline constexpr auto is_not_flint = functor<is_not_flint_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_flint_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return false_(eve::as<T>());
      else if (O::contains(pedantic))
        return is_nez(frac[raw](a)) || (a > eve::maxflint(eve::as<T>()));
      else
        return is_nez(frac[raw](a));
    }
  }
}
