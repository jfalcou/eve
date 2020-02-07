//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_EXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_EXP_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/platform.hpp>
#include <eve/function/pedantic.hpp>
#include <type_traits>
#include <tuple>


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto exp_(EVE_SUPPORTS(cpu_)
                                     , const T &xx) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
   using t_abi = abi_type_t<T>;
   if constexpr(is_emulated_v<t_abi> ) return map(eve::exp, xx); 
   else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::exp, xx);
   else
   {
     using vt_t =  value_type_t<T>;
     const T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
     const T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
     const T Invlog_2=  Ieee_constant<T, 0x3fb8aa3bU, 0x3ff71547652b82feULL>();
     auto c = nearest(Invlog_2*xx);
     auto k = c;
     auto x = fnma(c, Log_2hi, xx); //x-c*L
     if constexpr(std::is_same_v<vt_t, float>)
     {
       x = fnma(c, Log_2lo, x);   
       // Remez polynomial of degree 4 on [-0.5 0.5] for (exp(x)-1-x)/sqr(x)
       // tested in range: [-88.3763, 88.3763]
       //2214928753 values (98.98%)  within 0.0 ULPs
       //  22831063 values (1.02%)   within 0.5 ULPs
       //  4.89648 cycles/value (SSE4.2 g++-4.8)
       T y = horn<T,
         0x3f000000, //  5.0000000e-01
         0x3e2aa9a5, //  1.6666277e-01
         0x3d2aa957, //  4.1665401e-02
         0x3c098d8b, //  8.3955629e-03
         0x3ab778cf  //  1.3997796e-03
         >(x);
       c = inc(fma(y, sqr(x), x));
     }
     else
     {
       T hi = x;
       T lo = c*Log_2lo;
       x = hi-lo; 
       T t = sqr(x);
       c = fnma(t, horn<T
               , 0x3fc555555555553eull
               , 0xbf66c16c16bebd93ull
               , 0x3f11566aaf25de2cull
               , 0xbebbbd41c5d26bf1ull
               , 0x3e66376972bea4d0ull
                >(t), x); //x-h*t
        c = oneminus((((lo-(x*c)/(T(2)-c))-hi)));
      }
      x =  eve::ldexp(c, k);
      c = if_else(is_less_equal(xx, Minlog<T>()), eve::zero_, x);
      return if_else(is_greater_equal(xx, Maxlog<T>()), Inf<T>(), c);
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto exp_(EVE_SUPPORTS(cpu_)
                                     , pedantic_type const & 
                                     , const T &xx) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
   using t_abi = abi_type_t<T>;
   if constexpr(is_emulated_v<t_abi> ) return map(eve::exp, xx); 
   else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::exp, xx);
   else
   {
     using vt_t =  value_type_t<T>;
     const T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
     const T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
     const T Invlog_2=  Ieee_constant<T, 0x3fb8aa3bU, 0x3ff71547652b82feULL>();
     auto c = nearest(Invlog_2*xx);
     auto k = c;
     auto x = fnma(c, Log_2hi, xx); //x-c*L
     if constexpr(std::is_same_v<vt_t, float>)
     {
       x = fnma(c, Log_2lo, x);   
       // Remez polynomial of degree 4 on [-0.5 0.5] for (exp(x)-1-x)/sqr(x)
       // tested in range: [-88.3763, 88.3763]
       //2214928753 values (98.98%)  within 0.0 ULPs
       //  22831063 values (1.02%)   within 0.5 ULPs
       //  4.89648 cycles/value (SSE4.2 g++-4.8)
       T y = horn<T,
         0x3f000000, //  5.0000000e-01
         0x3e2aa9a5, //  1.6666277e-01
         0x3d2aa957, //  4.1665401e-02
         0x3c098d8b, //  8.3955629e-03
         0x3ab778cf  //  1.3997796e-03
         >(x);
       c = inc(fma(y, sqr(x), x));
     }
     else
     {
       T hi = x;
       T lo = c*Log_2lo;
       x = hi-lo; 
       T t = sqr(x);
       c = fnma(t, horn<T
               , 0x3fc555555555553eull
               , 0xbf66c16c16bebd93ull
               , 0x3f11566aaf25de2cull
               , 0xbebbbd41c5d26bf1ull
               , 0x3e66376972bea4d0ull
                >(t), x); //x-h*t
        c = oneminus((((lo-(x*c)/(T(2)-c))-hi)));
      }
       x =  eve::pedantic_(eve::ldexp)(c, k);
       c = if_else(is_less_equal(xx, Minlog<T>()), eve::zero_, x);
       return if_else(is_greater_equal(xx, Maxlog<T>()), Inf<T>(), c);
   }
  }  
}

#endif
