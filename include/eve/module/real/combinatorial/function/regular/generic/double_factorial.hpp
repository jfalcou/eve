//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/all.hpp>
#include <eve/function/average.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/factorial.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/converter.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/min.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>

#include <type_traits>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<unsigned_value T>
  EVE_FORCEINLINE auto double_factorial_(EVE_SUPPORTS(cpu_), T i0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto odd = [](auto i)
        {
          auto n = i >> 1;
          auto r =  (factorial(i) / ldexp(factorial(n), n));
          auto test =  i <= 171;
          if (eve::all(test)) return r;
          else
          {
            constexpr double invsqrtpi = 0.564189583547756286948079451560772585844050629329;
            auto r1 = tgamma(fma(float64(i), 0.5, 1.0))* invsqrtpi;
            return if_else(test,  r, ldexp(r1, inc(i) >> 1));
          }
        };

      auto even = [](auto i){
        auto n = i >> 1;
        auto r =  factorial(n);
        return ldexp(r, n);
      };
      auto i = uint64(i0);
      auto r = inf(as<decltype(factorial(i))>()); //perhaps 0 should be fine
      auto notdone =  i <= 300;
      notdone = next_interval(odd, notdone, is_odd(i), r, i);
      if(eve::any(notdone))
      {
        last_interval(even, notdone, r, i);
      }
      return r;
    }
    else
      return apply_over(double_factorial, i0);
  }
}
