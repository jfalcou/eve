//==================================================================================================
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
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_lez_t : elementwise_callable<is_lez_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_lez_t, is_lez_);
  };
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_lez
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is less or equal to 0.
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
//!      constexpr auto is_lez(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_lez[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_lez[logical_value auto m](value auto x) noexcept;    // 2
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
//!     1. Returns [elementwise](@ref glossary_elementwise) `x <=  0`.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_lez.cpp}
//================================================================================================
  inline constexpr auto is_lez = functor<is_lez_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_lez_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( unsigned_value<T> )
        return is_eqz(a);
      else
        return a <= zero(eve::as(a));
    }
  }
}
