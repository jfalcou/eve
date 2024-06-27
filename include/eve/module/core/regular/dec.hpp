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
#include <eve/module/core/constant/one.hpp>

namespace eve
{
  template<typename Options>
  struct dec_t : elementwise_callable<dec_t, Options, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(dec_t, dec_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dec
//!   @brief `elementwise_callable` object returning the input decremented by 1.
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
//!      constexpr auto dec(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto dec[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto dec[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto dec[saturated](value auto x)               noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [SIMD or scalar value](@ref value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of `x - 1` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The saturated decrementation of `x`. More specifically, for signed
//!         integral, `abs[saturated](valmin(as<T>{}))` returns `eve:valmin(as<T>{}))`
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/dec.cpp}
//! @}
//================================================================================================
  inline constexpr auto dec = functor<dec_t>;

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T dec_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr(integral_value<T> && O::contains(saturated2))
        return dec[a != valmin(eve::as(a))](a);
      else
        return a - one(eve::as(a));
    }
  }
}
