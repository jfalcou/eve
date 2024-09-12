//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bit_mask.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/detail/roundings.hpp>

namespace eve::detail
{
  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr T add_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
  {
    if constexpr(O::contains(downward))
    {
      std::fesetround(FE_DOWNWARD);
//       auto volatile aa = a;
//       auto volatile bb = b;
      auto r = add(a, b);
      std::fesetround(FE_TONEAREST);
      return r;
    }
    else if constexpr(O::contains(downward))
    {
      std::fesetround(FE_UPWARD);
//        auto volatile aa = a;
//       auto volatile bb = b;
     auto r = add(a, b);
      std::fesetround(FE_TONEAREST);
      return r;
    }
    else if constexpr(O::contains(saturated2) && integral_value<T>)
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
        return a+b;
      }
    }
  }

  template<typename T, std::same_as<T>... Ts, callable_options O>
  EVE_FORCEINLINE constexpr T add_(EVE_REQUIRES(cpu_), O const & o, T r0, T r1, Ts... rs) noexcept
  {
    //TODO: both GCC and Clang can fail to properly reorder the op chain to reduce dependencies
    //      we might want to do this manually
    if constexpr(O::contains(downward))
    {
      std::fesetround(round_down);
      auto tmp1 =  rbr::drop(downward, o);
      auto oo = options<decltype(tmp1)>{tmp1};
      auto r = add[oo](r0, rs...);
      std::fesetround(round_to_nearest);
      return r;
    }
    else if constexpr(O::contains(upward))
    {
      std::fesetround(round_up);
      auto tmp1 =  rbr::drop(upward, o);
      auto oo = options<decltype(tmp1)>{tmp1};
      auto r = add[oo](r0, rs...);
      std::fesetround(round_to_nearest);
      return r;
    }
    else
    {
      r0   = add[o](r0,r1);
      ((r0 = add[o](r0,rs)),...);
      return r0;
    }
  }
}
