//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/twotonmb.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bitofsign.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/sign.hpp>

namespace eve::detail
{

  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr T
  nearest_(EVE_REQUIRES(cpu_), O const&, T const& a0) noexcept
  {
    if constexpr(integral_value<T>)
      return a0;
    else
    {
      auto s   = bitofsign(a0);
      auto v   = bit_xor(a0, s);
      auto t2n = twotonmb(eve::as{a0});
      auto d0  = v + t2n;
      auto d   = d0 - t2n;
      if constexpr( scalar_value<T> )
        return bit_xor((v < t2n) ? d : v, s);
      else
        return bit_xor(if_else(v < t2n, d, v), s);
    }
  }

  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr auto nearest_(EVE_REQUIRES(cpu_), O const&, T const& a0, as<U>) noexcept
  {
    auto z = nearest(a0);
    if constexpr(unsigned_value<U>)
      return convert(z, uint_from<T>());
    else if constexpr(signed_integral_value<U>)
      return convert(z, int_from<T>());
    else
      return z;
  }
}
