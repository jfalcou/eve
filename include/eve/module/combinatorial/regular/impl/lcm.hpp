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

// -----------------------------------------------------------------------------------------------
// decorated case TO DO LATER the decorator is not supported yet

// template<value T>
// auto
// lcm_(EVE_REQUIRES(cpu_), upgrade_converter const&, T a, T b) noexcept
// {
//   using up_t   = upgrade_t<T>;
//   using fup_t  = upgrade_t<as_floating_point_t<T>>;
//   using efup_t = element_type_t<fup_t>;
//   if constexpr( std::is_same_v<efup_t, float> )
//   {
//     auto r = lcm(to_<fup_t>(a), to_<fup_t>(b));
//     return convert(r, as_element<up_t>());
//   }
//   else // double element
//   {
//     auto r = lcm(to_<fup_t>(a), to_<fup_t>(b));
//     return convert(r, as_element<up_t>());
//   }
// }
}
