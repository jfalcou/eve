//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/special/regular/factorial.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE auto
lfactorial_(EVE_SUPPORTS(cpu_), T n) noexcept
{
  EVE_ASSERT(eve::all(is_flint(n)), "lfactorial : some entry elements are not flint");
  EVE_ASSERT(eve::all(is_gez(n)), "lfactorial : some entry elements are not positive");
  if constexpr( has_native_abi_v<T> )
  {
    constexpr auto max = std::same_as<element_type_t<T>, double> ? 171 : 35;
    auto           r   = eve::log(factorial(n));

    if( eve::all(n < max) ) return r;
    else
    {
      auto np = [](auto x)
      {
        if constexpr(integral_value<T>) return float64(inc(x));
        else                            return inc(x);
      }(n);

      return if_else(n < max, r, log_abs_gamma(np));

    }
  }
  else return apply_over(lfactorial, n);
}
}
