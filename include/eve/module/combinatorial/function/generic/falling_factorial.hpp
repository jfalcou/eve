//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/lgamma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value N >
  EVE_FORCEINLINE auto falling_factorial_(EVE_SUPPORTS(cpu_), T x, N p) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(falling_factorial, x, p);
  }
  
  template<floating_real_value T>
  EVE_FORCEINLINE auto falling_factorial_(EVE_SUPPORTS(cpu_), T x, T p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto r = nan(as(x));
      auto notdone = is_gez(x)&&is_gez(p)&&is_flint(x)&&is_flint(p);
      if (any(notdone))
      {
        r = if_else( notdone, nearest(exp(lgamma(x+1)-lgamma(x-p+1))), r);
      }
      return r;
    }
    else
      return apply_over(falling_factorial, x, p);
  }

   template<inegral_real_value T,  typename D>
  EVE_FORCEINLINE auto falling_factorial_(EVE_SUPPORTS(cpu_), D const &, T xx, T pp) noexcept
  {
    using elt_t =  element_type_t<T>;
    using up_t = upgrade_t<T>;
    using fup_t = upgrade_t<as_floating_point_t<T>>;
    auto xinc = inc(fup_t(xx));
    auto r = fup_t(pp); 
    auto r = nearest(exp(lgamma(xinc)-lgamma(xinc-p))); 
    return D()(r); 
  }
  
//     auto r = nan(as(x));
//     auto notdone = is_gez(x)&&is_gez(p)&&is_flint(x)&&is_flint(p);
//       if (any(notdone))
//       {
//         r = if_else( notdone, if_else(x >=  p, nearest(exp(lgamma(x+1)-lgamma(x-p+1))), zero), r);
//       }
//       return r;
 
}
