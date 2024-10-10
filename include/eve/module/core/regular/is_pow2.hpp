/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_pow2_t : elementwise_callable<is_pow2_t, Options>
  {
    template<integral_value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_pow2_t, is_pow2_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_pow2
//!   @brief `elementwise callable` returning a logical true if and only if the element value is a power of 2.
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
//!      constexpr auto is_pow2(integral_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto is_pow2[conditional_expr auto c](integral_value auto x) noexcept; // 2
//!      constexpr auto is_pow2[logical_value auto m](integral_value auto x)    noexcept; // 2
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
//!     1. returns  `true` if and only if `x` is an integral power of two.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_pow2.cpp}
//================================================================================================
  inline constexpr auto is_pow2 = functor<is_pow2_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_pow2_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      return is_gtz(a) && is_eqz(a & dec(a));
    }
  }
}
