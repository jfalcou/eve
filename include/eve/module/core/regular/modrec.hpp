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
#include <eve/module/core/regular/modpow.hpp>
#include <eve/module/core/regular/modmul.hpp>
#include <eve/module/core/regular/modsub.hpp>

namespace eve
{
  template<typename Options>
  struct modrec_t : strict_tuple_callable<modrec_t, Options>
  {

    template<eve::floating_value T0>
    requires(eve::same_lanes_or_scalar<T0>)
      EVE_FORCEINLINE T0
    constexpr operator()(T0 x0, unsigned int p)  const noexcept
    {
      EVE_ASSERT(eve::all(eve::is_flint(x0)), "x0 is not a floating positive integer");
      EVE_ASSERT(eve::all(x0 < p)           , "x0 is not less than p");
      return EVE_DISPATCH_CALL(x0, p);
    }

    EVE_CALLABLE_OBJECT(modrec_t, modrec_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var modrec
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
//!      constexpr auto modrec(auto x0, auto p) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: flint  argument.
//!     * `p`: unsigned  prime value
//!
//!    **Return value**
//!
//!      The value of the inverse of the arguments modulo p is returned.
//!         x is supposed to be flint postitive and less than p.
//!
//!  @note if p is not a prime number the modular product of x by the result is the gcd of x and p.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/modrec.cpp}
//================================================================================================
  inline constexpr auto modrec = functor<modrec_t>;
//================================================================================================
//! @}
//================================================================================================
}

namespace eve::detail
{
  template<typename T0, callable_options O>
  constexpr auto  modrec_(EVE_REQUIRES(cpu_), O const&, T0 a, unsigned int ip) noexcept
  {
//     if constexpr(simd_value<T0>)
//       return modpow(a, ip-2, ip);
//     else
    {
      T0 t(0);
      T0 nt(1);
      T0 r(ip);
      T0 nr(a);
      auto neznr = eve::is_nez(nr);
      while (eve::any(neznr))
      {
        auto q =  div[neznr][eve::toward_zero][eve::left](nr, r);
        auto tmp0 = t-q*nt;
        t = if_else(neznr, nt, t);
        nt =if_else(neznr, tmp0, nt);
        auto tmp1 = r-q*nr;
        r = if_else(neznr,nr, r);
        nr = if_else(neznr,tmp1, nr);
        neznr = eve::is_nez(nr);
      }
      return if_else(is_ltz(t), t+ip, t);
    }
  }
}
