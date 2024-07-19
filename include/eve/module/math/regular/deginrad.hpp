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

namespace eve
{
  template<typename Options>
  struct deginrad_t : elementwise_callable<deginrad_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(deginrad_t, deginrad_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var deginrad
//!
//! @brief `elementwise_callable` object computing the product of the input by \f$\pi/180\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto deginrad(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto deginrad[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto deginrad[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating_value](@ref value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. Returns the [elementwise](@ref glossary_elementwise) the degree input converted in radian.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/deginrad.cpp}
//!  @}
//================================================================================================
  inline constexpr auto deginrad = functor<deginrad_t>;

  namespace detail
  {
    template<floating_ordered_value T, callable_options O>
    EVE_FORCEINLINE constexpr T
    deginrad_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      auto ridh = ieee_constant<0x1.1de0000p-6f, 0x1.1df46a0000000p-6>(eve::as<T>{});
      auto ridl = ieee_constant<0x1.46a2520p-18f, 0x1.294e9c8ae0ec6p-33>(eve::as<T>{});
      return fma(a, ridl, a * ridh);
    }
  }
}
