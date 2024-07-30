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
#include <eve/module/core.hpp>

namespace eve
{

  template<typename Options>
  struct radindeg_t : elementwise_callable<radindeg_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(radindeg_t, radindeg_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var radindeg
//!
//! @brief `elementwise_callable` object multiplying the input by \f$180/\pi\f$.
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
//!      constexpr auto radindeg(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto radindeg[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto radindeg[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the radian input converted in degree.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/radindeg.cpp}
//================================================================================================
  inline constexpr auto radindeg = functor<radindeg_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<floating_value T, callable_options O>
    EVE_FORCEINLINE constexpr T
    radindeg_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto radradindeg  = ieee_constant<0x1.ca5dc20p+5f, 0x1.ca5dc1a63c1f8p+5>(eve::as<T>{});
        auto radradindegr = ieee_constant<0x1.670f800p-21f, 0x1.1e7ab456405f8p-49>(eve::as<T>{});
        return fma(a, radradindegr, a * radradindeg);
      }
      else return apply_over(radindeg, a);
    }
  }
}
