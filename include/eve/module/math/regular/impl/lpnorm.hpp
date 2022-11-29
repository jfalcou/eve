//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/hypot.hpp>
#include <eve/module/math/regular/pow_abs.hpp>
#include <eve/module/math/regular/pow.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/traits/underlying_type.hpp>

namespace eve::detail
{

template<real_value P, value T0, value T1, value... Ts>
auto
lpnorm_(EVE_SUPPORTS(cpu_), const P& p, T0 a0, T1 a1, Ts... args) requires(!decorator<P>)
{
  using c_t = common_value_t<T0, T1, Ts...>;
  if constexpr( integral_value<P> )
  {
//    auto fp = floating_(p);
    using e_t =  underlying_type_t<c_t>;
    auto fp =  convert(p, eve::as<e_t>());
    return lpnorm(fp, a0, a1, args...);
  }
  else
  {
    using r_t = decltype(eve::abs(c_t{}));
    if constexpr( has_native_abi_v<r_t> )
    {
      if( eve::all(p == P(2)) ) return hypot(a0, a1, args...);
      else if( eve::all(p == P(1)) ) return manhattan(a0, a1, args...);
      else if( eve::all(p == eve::inf(as(p))) ) return eve::maxabs(a0, a1, args...);
      else
      {
        auto rp = r_t(p);
        r_t that = add(pow_abs(r_t(a0),rp), pow_abs(r_t(a1), rp), pow_abs(r_t(args), rp)...);
        auto r = pow(that, rec(rp));
        auto isinfp = is_infinite(rp);
        if (eve::none(isinfp)) return r;
        else return if_else(is_infinite(rp), eve::maxabs(a0, a1, args...), r);
      }
    }
    else { return apply_over(lpnorm, p, c_t(a0), c_t(a1), c_t(args)...); }
  }
}

//================================================================================================
// tuples
//================================================================================================
template< real_value P,kumi::non_empty_product_type Ts>
auto
lpnorm_(EVE_SUPPORTS(cpu_), P p, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return abs(get<0>(tup));
  else return eve::abs(kumi::apply( [&](auto... m) { return lpnorm(p, m...); }, tup));
}
}
