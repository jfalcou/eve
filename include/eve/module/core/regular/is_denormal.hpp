/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/bit_value.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_denormal_t : elementwise_callable<is_denormal_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_denormal_t, is_denormal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_denormal
//!   @brief `elementwise callable` returning a logical true if and only if the element value is denormal.
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
//!      constexpr auto is_denormal(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_denormal[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_denormal[logical_value auto m](value auto x) noexcept;    // 2
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
//!      1. The call `is_denormal(x)` is semantically  equivalent to:
//!         @code
//!         if constexpr(floating_value<T>)
//!           return (eve::abs(x) < eve::smallestposval(as(x))) && is_nez(x);
//!         else if constexpr(integral_value<T>)
//!           return eve::false_(as(x));
//!         @endcode
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_denormal.cpp}
//! @}
//================================================================================================
  inline constexpr auto is_denormal = functor<is_denormal_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_denormal_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( !floating_value<T> || !eve::platform::supports_denormals )
        return false_(eve::as<T>());
      else
        return is_nez(a) && (eve::abs(a) < smallestposval(eve::as<T>()));
    }
  }
}
