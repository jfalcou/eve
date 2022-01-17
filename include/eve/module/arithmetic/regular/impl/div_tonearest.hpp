//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/horizontal.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/saturated/div.hpp>
#include <eve/function/saturated/convert.hpp>
#include <eve/function/is_odd.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE T div_(EVE_SUPPORTS(cpu_),
                         to_nearest_type const &,
                         T a,
                         T b) noexcept requires has_native_abi_v<T>
  {
    if constexpr(integral_value<T> )
    {
      EVE_ASSERT(eve::all((b!= 0)), "[eve] - nearest(div)(a, 0) is undefined");
    }
    if constexpr( floating_real_value<T> )
    {
      return nearest(div(a, b));
    }
    else if constexpr( integral_real_value<T> )
    {
      using v_t = element_type_t<T>;
      if constexpr( sizeof(v_t)== 8)
      {
        if constexpr( unsigned_value<T> )
        {
          auto q =  div(a, b);
          auto r1 = fnma(b, q, a);
          auto r2 = b-r1;
          return inc[(r1 > r2)||((r1 == r2)&&is_odd(q))](q);
        }
        else
        {
          auto ltza = is_ltz(a);
          a = minus[ltza](a); // ensure a >= 0
          b = minus[ltza](b);
          auto ltzb = is_ltz(b);
          auto q =  div(a, b);
          auto r1 = fnma(b, q, a);
          auto r2 = minus[ltzb](b)-r1;
          auto cond = (r1 > r2)||((r1 == r2)&&is_odd(q));
          return if_else(is_ltz(b), dec[cond](q), inc[cond](q));
        }
      }
      else
      {
        return saturated(convert)(nearest(float64(a) / float64(b)), as<v_t>());
      }
    }
  }
}
