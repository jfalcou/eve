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
#include <iostream>
namespace eve
{
  template<typename Options>
  struct modpow_t : strict_tuple_callable<modpow_t, Options>
  {

    template<eve::floating_value T0>
    EVE_FORCEINLINE T0
    constexpr operator()(T0 x0, unsigned int x1, unsigned int p)  const noexcept
    {
      EVE_ASSERT(eve::all(eve::is_flint(x0)), "x0 is not a floating integer");
      return EVE_DISPATCH_CALL(x0, x1, p);
    }

    EVE_CALLABLE_OBJECT(modpow_t, modpow_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var modpow
//!   @brief tuple_callable` computing x^y mod p.
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
//!      // Regular overloads
//!      constexpr auto modpow(auto x0, auto n, auto p) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x0`: flint  argument.
//!     * `n`: unsigned int power positive and less than p
//!     * `p`: unsigned int prime value less than exp2(50)
//!
//!    **Return value**
//!
//!       The value of x0 to the power n, modulo p is returned.
//!        x0 is supposed to be flint postitive and less than p.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/modpow.cpp}
//================================================================================================
  inline constexpr auto modpow = functor<modpow_t>;
//================================================================================================
//! @}
//================================================================================================
}

namespace eve::detail
{
  template<typename T0, callable_options O>
  constexpr auto  modpow_(EVE_REQUIRES(cpu_), O const&, T0 a0, unsigned int a1, unsigned int ip) noexcept
  {
    T0 base(a0);
    int expo = a1;

    auto result = eve::one(as<T0>());
    while( eve::any(is_nez(expo)))
    {
      result = modmul(result, if_else(is_odd(expo), base, one), ip);
      expo = expo/2;
      base = modmul(base, base, ip);
   }
    return result;
  }
}
