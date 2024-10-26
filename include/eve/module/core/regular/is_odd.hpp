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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/is_even.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_odd_t : elementwise_callable<is_odd_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_odd_t, is_odd_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_odd
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is odd.
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
//!      constexpr auto is_odd(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_odd[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_odd[logical_value auto m](value auto x) noexcept;    // 2
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
//!     1. returns `true`  if and only is `x` is an odd integer.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_odd.cpp}
//================================================================================================
  inline constexpr auto is_odd = functor<is_odd_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_odd_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        auto da = dec(a);
        return (a != da) && is_even(da);
      }
      else if constexpr( scalar_value<T> )
        return (a & one(eve::as(a)));
      else return
        is_nez((a & one(eve::as(a))));
    }
  }
}
