//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <cfenv>
#include <eve/concept/value.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bit_mask.hpp>
#include <eve/module/core/regular/two_add.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/regular/fnma.hpp>

namespace eve::detail
{

  template<callable_options O, typename T0, typename T1>
  EVE_FORCEINLINE constexpr auto add_(EVE_REQUIRES(cpu_), O const& o, T0 a0, T1 b0) noexcept
  {
    using r_t =  eve::common_value_t<T0, T1>;
    auto a = r_t(a0);
    auto b = r_t(b0);
    if constexpr(O::contains(mod))
    {
      auto p = o[mod].value(r_t());
      auto s = a+b;
      return eve::if_else(s >= p, s-p, p);
    }
    else if constexpr(O::contains(widen))
    {
      return add[o.drop(widen)](upgrade(a), upgrade(b));
    }
    else if constexpr(floating_value<r_t> && (O::contains(to_nearest_odd)))
    {
      auto d = eve::add[lower](a, b);
      auto u = eve::add[upper](a, b);
      auto e = u+d;
      constexpr auto hf = eve::half(eve::as<eve::element_type_t<r_t>>());
      return eve::fnma(e, hf, u)+d;
    }
    else if constexpr(floating_value<r_t> && (O::contains(lower) || O::contains(upper) ))
    {
      if constexpr(O::contains(strict))
      {
        auto r = add[o.drop(lower, upper, strict)](a, b);
        if constexpr(O::contains(lower))
          return prev(r);
        else
          return next(r);
      }
      else
      {
        auto [r, e] = eve::two_add(a, b);
        if constexpr(O::contains(lower))
          return eve::prev[eve::is_ltz(e)](r);
        else
          return eve::next[eve::is_gtz(e)](r);
      }
    }
    else if constexpr(O::contains(saturated) && integral_value<r_t>)
    {
      if constexpr( signed_integral_value<r_t> )
      {
        auto test = is_ltz(b);
        auto pos  = min(sub(valmax(as(a)), b), a);
        auto neg  = max(sub(valmin(as(a)), b), a);
        return add(b, if_else(test, neg, pos));
      }
      else
      {
        // Triggers conditional MOV that directly read the flag register
        r_t r = add(a, b);
        return bit_or(r, bit_mask(is_less(r, a)));
      }
    }
    else
    {
      // The only way to get there is when :
      //  - a + b is done in scalar
      //  - emulation occurs and again, a + b is done in scalar
      //  - a product_type with custom operator+ is used
      if constexpr(signed_integral_scalar_value<r_t>)
      {
        using u_t = as_integer_t<r_t, unsigned>;
        return r_t(u_t(a)+u_t(b));
      }
      else
      {
        return r_t(a+b);
      }
    }
  }

  template<callable_options O, typename T0>
  EVE_FORCEINLINE constexpr auto add_(EVE_REQUIRES(cpu_), O const&, T0 a) noexcept
  {
    if constexpr(O::contains(widen))
      return upgrade(a);
    else
      return a;
  }

  template<typename T0, typename T1, typename ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto add_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
  requires(sizeof...(Ts) != 0)
  {
    using r_t = eve::common_value_t<T0, T1, Ts...>;
    //TODO: both GCC and Clang can fail to properly reorder the op chain to reduce dependencies
    //      we might want to do this manually
    if constexpr(O::contains(widen))
      return add[o.drop(widen)](upgrade(r0), upgrade(r1), upgrade(rs)...);
    else
    {
      if constexpr(scalar_value<r_t> && (sizeof...(Ts)+2 >= eve::expected_cardinal_v<r_t>) && !O::contains(saturated))
      {
        auto head = eve::as_wides(eve::zero(eve::as<r_t>()), r0, r1, rs...);
        auto s = eve::add[o](head);
//         if constexpr(O::size() == 1 && O::contains(ignore_none))
//           return sum(s);
//         else
          return butterfly_reduction(s, eve::add[o]).get(0);
      }
      else if constexpr(O::contains(kahan))
      {
        // kahan being precursor, but this is S. M. Rump, T. Ogita, and S. Oishi algorithm
        // Accurate floating-point summation part I: Faithful rounding.
        // SIAM Journal on Scientific Computing, 31(1):189-224, 2008.
        auto get_fn= [](){
          if constexpr(O::contains(raw)) return two_add[raw];
          else return two_add;
        };
        auto pair_add = [fn = get_fn()](auto pair0, auto ri){
          auto [a0, e0] = pair0;
          auto [s, e1] = fn(a0, ri);
          return zip(s, e0+e1);
        };
        auto p0   = two_add(r_t(r0),r_t(r1));
        ((p0 = pair_add(p0,r_t(rs))),...);
        auto [r, e] = p0;
        return r+e;
      }
      else
      {
        auto p0   = add[o](r_t(r0),r_t(r1));
        ((p0 = add[o](p0,r_t(rs))),...);
        return p0;
      }
    }
  }
}
