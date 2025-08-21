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
#include <iostream>

namespace eve::detail
{

  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr auto add_(EVE_REQUIRES(cpu_), O const& o, T a, T b) noexcept
  requires(!O::contains(mod))
  {
    if constexpr(O::contains(widen))
    {
      return add[o.drop(widen)](upgrade(a), upgrade(b));
    }
    else if constexpr(floating_value<T> && (O::contains(to_nearest_odd)))
    {
      auto d = eve::add[lower](a, b);
      auto u = eve::add[upper](a, b);
      auto e = u+d;
      constexpr auto hf = eve::half(eve::as<eve::element_type_t<T>>());
      return eve::fnma(e, hf, u)+d;
    }
    else if constexpr(floating_value<T> && (O::contains(lower) || O::contains(upper) ))
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
    else if constexpr(O::contains(saturated) && integral_value<T>)
    {
      if constexpr( signed_integral_value<T> )
      {
        auto test = is_ltz(b);
        auto pos  = min(sub(valmax(as(a)), b), a);
        auto neg  = max(sub(valmin(as(a)), b), a);
        return add(b, if_else(test, neg, pos));
      }
      else
      {
        // Triggers conditional MOV that directly read the flag register
        T r = add(a, b);
        return bit_or(r, bit_mask(is_less(r, a)));
      }
    }
    else
    {
      // The only way to get there is when :
      //  - a + b is done in scalar
      //  - emulation occurs and again, a + b is done in scalar
      //  - a product_type with custom operator+ is used
      if constexpr(signed_integral_scalar_value<T>)
      {
        using u_t = as_integer_t<T, unsigned>;
        return T(u_t(a)+u_t(b));
      }
      else
      {
        return T(a+b);
      }
    }
  }

  template<callable_options O, typename T0, typename T1>
  EVE_FORCEINLINE constexpr auto add_(EVE_REQUIRES(cpu_), O const& o, T0 x, T1 y ) noexcept
  requires(O::contains(mod))
  {
    using r_t =  eve::common_value_t<T0, T1>;
    auto p = o[mod].value(r_t());
    auto s = x+y;
    return eve::sub[s >= p](s, p);
  }

  template<typename T, std::same_as<T>... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto add_(EVE_REQUIRES(cpu_), O const & o, T r0, T r1, Ts... rs) noexcept
  requires(sizeof...(Ts) != 0)
  {
    //TODO: both GCC and Clang can fail to properly reorder the op chain to reduce dependencies
    //      we might want to do this manually
    if constexpr(O::contains(widen))
      return add[o.drop(widen)](upgrade(r0), upgrade(r1), upgrade(rs)...);
    else
    {
      r0   = add[o](r0,r1);
      ((r0 = add[o](r0,rs)),...);
      return r0;
    }
  }
}
