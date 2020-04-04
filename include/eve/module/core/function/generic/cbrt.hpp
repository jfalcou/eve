//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_CBRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_CBRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/add.hpp>    
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/gather.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_ltz.hpp>  
#include <eve/function/is_not_finite.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/minus.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp> 
#include <eve/function/sqr.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cbrt_(EVE_SUPPORTS(cpu_)
                                      , T x) noexcept
  {
    if constexpr(native<T>)
    {
      using vt_t =  element_type_t<T>;
      auto test0 = is_eqz(x) || is_not_finite(x); 
      if constexpr(scalar_value<T>) if(test0) return x;
      constexpr vt_t factor[5] = {0.6299605249474365823836, 0.793700525984099737376, 1.0
                                , 1.2599210498948731647672, 1.587401051968199474751};
      auto ax = eve::abs (x);
      auto test = is_less(eve::abs(x), T(100)*Smallestposval<T>());
      ax = if_else(test, ldexp(ax, 54), ax); 
      /* Reduce x.  xm now is an range  [0.5, 1.0].  */
      auto [xm, xe] = raw_(ifrexp)(ax);
      T u; 
      if constexpr(std::is_same_v<vt_t, double>)
      {
        u = horn<T, 0x3fd6b69cba168ff2ll, 0x3ff8218dde9028b4ll, 0xc000eb8277cd8d5dll, 0x40039350adad51ecll, 
                    0xbffd5ae6cfa20f0cll, 0x3fe91e2a6fe7e984ll, 0xbfc29801e893366dll  >(xm); 
      }
      else if constexpr(std::is_same_v<vt_t, float>)
      {
        u = horn <T, 0x3efc3de2, 0x3f3293fa, 0xbe441925>(xm); 
      }
      auto t2 = sqr(u) * u;
      u *= fma(xm, T(2), t2) / fma(T(2), t2, xm); 
      
      if constexpr(scalar_value<T>) u *= factor[2 + xe % 3];
      else                          u *= gather(&factor[0], 2 + xe-(xe/3)*3);
      u = minus[is_ltz(x)](u);
      if constexpr(scalar_value<T>)   xe = add[test](int(xe)/3, -18);
      else                            xe = add[test](xe/3, -18);
      auto z = ldexp(u, xe); 
      if constexpr(scalar_value<T>) return z;
      else                          return if_else(test0, x, z); 
    }
    else return apply_over(cbrt, x); 
  }
}

#endif
