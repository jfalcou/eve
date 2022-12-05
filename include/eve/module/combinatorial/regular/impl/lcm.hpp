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

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<integral_value T, integral_value U>
EVE_FORCEINLINE auto
lcm_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
->common_value_t<T, U>
{
  return arithmetic_call(lcm, a, b);
}

template<ordered_value T>
T
lcm_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
{
  if constexpr( has_native_abi_v<T> )
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
// decorated case

template<value T>
auto
lcm_(EVE_SUPPORTS(cpu_), upgrade_converter const&, T a, T b) noexcept
{
  using up_t   = upgrade_t<T>;
  using fup_t  = upgrade_t<as_floating_point_t<T>>;
  using efup_t = element_type_t<fup_t>;
  if constexpr( std::is_same_v<efup_t, float> )
  {
    auto r = lcm(to_<fup_t>(a), to_<fup_t>(b));
    return convert(r, as<element_type_t<up_t>>());
  }
  else // double element
  {
    auto r = lcm(to_<fup_t>(a), to_<fup_t>(b));
    return convert(r, as<element_type_t<up_t>>());
  }
}
}
