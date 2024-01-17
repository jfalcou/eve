//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/combinatorial/regular/gcd.hpp>
#include <eve/module/core.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/as_element.hpp>

namespace eve::detail
{

  template<typename T, typename U, callable_options O>
  common_value_t<T, U>
  lcm_(EVE_REQUIRES(cpu_), O const& o, T a, U b) noexcept
  {
    if constexpr(!std::same_as<T, U>)
    {
      using c_t =  common_value_t<T, U>;
      return lcm_(EVE_TARGETS(cpu_), o, c_t(a), c_t(b)); ;
    }
    else if constexpr( has_native_abi_v<T> )
    {
      EVE_ASSERT(eve::all(is_flint(a) && is_flint(b)), "lcm: some entries are not flint");
      a = abs(a);
      b = abs(b);
      if constexpr( scalar_value<T> )
      {
        if( !b || !a ) return T(0);
        return b / gcd(a, b) * a;
      }
      else { return a * (b / gcd(a, if_else(b, b, eve::one))); }
    }
    else return apply_over(lcm, a, b);
  }
}
