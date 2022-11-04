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

namespace eve::detail
{

template<real_value P, floating_value T0, floating_value T1, floating_value... Ts>
auto
lpnorm_(EVE_SUPPORTS(cpu_), const P& p, T0 a0, T1 a1, Ts... args) requires(!decorator<P>)
{
  if constexpr( integral_value<P> )
  {
    auto fp = floating_(p);
    return lpnorm(fp, a0, a1, args...);
  }
  else
  {
    using r_t = common_compatible_t<T0, T1, Ts...>;
    if constexpr( has_native_abi_v<r_t> )
    {
      if( eve::all(p == P(2)) ) return hypot(r_t(a0), r_t(a1), r_t(args)...);
      else if( eve::all(p == P(1)) ) return manhattan(r_t(a0), r_t(a1), r_t(args)...);
      else if( eve::all(p == eve::inf(as(p))) ) return eve::maxabs(r_t(a0), r_t(a1), r_t(args)...);
      else
      {
        auto rp = r_t(p);
        r_t  that(pow_abs(r_t(a0), rp));
        auto addppow = [rp](auto that, auto next) -> r_t
        {
          that += pow_abs(next, rp);
          return that;
        };
        that = addppow(that, r_t(a1));
        ((that = addppow(that, args)), ...);
        auto isinfp = is_infinite(rp);
        if( eve::any(isinfp) )
        {
          auto r = eve::max(eve::abs(r_t(a0)), eve::abs(r_t(a1)), eve::abs(r_t(args))...);
          if( eve::all(isinfp) ) return r;
          return if_else(isinfp, r, pow_abs(that, rec(rp)));
        }
        return pow_abs(that, rec(rp));
      }
    }
    else { return apply_over(lpnorm, p, a0, a1, args...); }
  }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C,
         real_value       P,
         floating_value   T0,
         floating_value   T1,
         floating_value... Ts>
auto
lpnorm_(EVE_SUPPORTS(cpu_), C const& cond, const P& p, T0 a0, T1 a1, Ts... args) requires(
    !decorator<P>)
{
  return mask_op(cond, eve::lpnorm, p, a0, a1, args...);
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
