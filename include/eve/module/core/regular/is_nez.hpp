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

namespace eve
{
  template<typename Options>
  struct is_nez_t : elementwise_callable<is_nez_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_nez_t, is_nez_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_nez
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is not zero.
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
//!      constexpr auto is_nez(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_nez[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_nez[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. `is_nez(x)` is semantically equivalent `x != 0`.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_nez.cpp}
//================================================================================================
  inline constexpr auto is_nez = functor<is_nez_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_nez_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      return detail::to_logical(a);
    }
  }
}
