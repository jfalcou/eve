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
  struct is_nepz_t : elementwise_callable<is_nepz_t, Options>
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_nepz_t, is_nepz_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_nepz
//!   @brief `elementwise callable` returning a logical true  if and only if "positive" zero.
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
//!      constexpr auto is_nepz(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_nepz[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_nepz[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. `is_nepz(x)` is true if and only if all bits of the representation of `x` are zero.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_nepz.cpp}
//================================================================================================
  inline constexpr auto is_nepz = functor<is_nepz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T> is_nepz_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      return !is_eqpz(a);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_nepz.hpp>
#endif
