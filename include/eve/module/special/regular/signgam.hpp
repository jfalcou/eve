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
  struct signgam_t : elementwise_callable<signgam_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(signgam_t, signgam_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var signgam
//!   @brief
//! @brief `elementwise_callable` object computing the sign of the \f$\Gamma\f$ function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto signgam(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto signgam[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto signgam[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: [floating value](@ref floating_value).
//!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of `eve::sign(eve::tgamma(x))` is returned (without computing `eve::tgamma(x)`);
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/regular/signgam.cpp}
//================================================================================================
  inline constexpr auto signgam = functor<signgam_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T
    signgam_(EVE_REQUIRES(cpu_), O const &, T a0)
    {
      auto isleza0 = is_ngtz(a0);
      auto a       = if_else(is_flint(a0) || is_infinite(a0),
                             eve::allbits,
                             oneminus(one[is_odd(floor(a0))](as(a0)) * T(2)));
      a            = if_else(is_eqz(a0), bit_or(one(as(a0)), bitofsign(a0)), a);
      return if_else(is_nan(a0), a0, if_else(isleza0, a, eve::one));

    }
  }
}
