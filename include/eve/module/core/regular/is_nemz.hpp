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
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_positive.hpp>

namespace eve
{
  template<typename Options>
  struct is_nemz_t : elementwise_callable<is_nemz_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((as<as_logical_t<T>>{}), t);
    }

    EVE_CALLABLE_OBJECT(is_nemz_t, is_nemz_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_nemz
//!   @brief `elementwise callable` returning a logical true  if and only if a "negative" zero.
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
//!      constexpr auto is_nemz(floating_value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_nemz[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto is_nemz[logical_value auto m](floating_value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. `is_nemz(x)` is semantically equivalent to bitwise equality to `mzero(as(x))`.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_nemz.cpp}
//================================================================================================
  inline constexpr auto is_nemz = functor<is_nemz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_nemz_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr(integral_value<T>)
        return false_(as<T>());
      else
        return logical_or(is_positive(a), is_ltz(a));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_nemz.hpp>
#endif
