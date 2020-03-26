//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_EXPM1_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_EXPM1_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/toint.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/logeps.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto expm1_(EVE_SUPPORTS(cpu_)
                                       , T xx) noexcept
  requires std::floating_point<T>
  {
    using i_t = as_integer_t<T>;
    if (is_eqz(xx)) return xx; 
    if (is_greater_equal(xx, Maxlog<T>())) return Inf<T>();
    if (is_less_equal(xx, Logeps<T>())) return Mone<T>();
    const T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
    const T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
    const T Invlog_2 =  Ieee_constant<T, 0x3fb8aa3bU, 0x3ff71547652b82feULL>();
    T k  = nearest(Invlog_2*xx);
    if constexpr(std::is_same_v<T, float>)
    {
      T x = fnma(k, Log_2hi, xx);
      x =  fnma(k, Log_2lo, x);
      T hx  = x*Half<T>();
      T hxs = x*hx;
      T r1 = horn<T,
        0X3F800000U, // 1
        0XBD08887FU, // -3.3333298E-02
        0X3ACF6DB4U  // 1.5825541E-03
        > (hxs);
      T t  = fnma(r1, hx, T(3));
      T e  = hxs*((r1-t)/(T(6) - x*t));
      e  = fms(x, e, hxs);
      i_t ik =  toint(k);
      T two2mk = bit_cast(shl(Maxexponent<T>()-ik,Nbmantissabits<T>()), as<T>());
      T y = oneminus(two2mk)-(e-x);
      return ldexp(y, ik);    
    }
    else
    {
      T hi = fnma(k, Log_2hi, xx);
      T lo = k*Log_2lo;
      T x  = hi-lo;
      T hxs = sqr(x)*Half<T>();
      T r1 = horn<T,
        0X3FF0000000000000ULL,
        0XBFA11111111110F4ULL,
        0X3F5A01A019FE5585ULL,
        0XBF14CE199EAADBB7ULL,
        0X3ED0CFCA86E65239ULL,
        0XBE8AFDB76E09C32DULL
        > (hxs);
      T t  = T(3)-r1*Half<T>()*x;
      T e  = hxs*((r1-t)/(T(6) - x*t));
      T c = (hi-x)-lo;
      e  = (x*(e-c)-c)-hxs;
      i_t ik =  toint(k);
      T two2mk = bit_cast(shl(Maxexponent<T>()-ik,Nbmantissabits<T>()), as<T>());
      T ct1= oneminus(two2mk)-(e-x);
      T ct2= inc((x-(e+two2mk)));
      T y = if_else((k < T(20)),ct1,ct2);
      return ldexp(y, ik);
    } 
  }
}

#endif
