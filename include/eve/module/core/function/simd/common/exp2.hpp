//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_EXP2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_EXP2_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_shl.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/maxlog2.hpp>
#include <eve/constant/minlog2.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto exp2_(EVE_SUPPORTS(cpu_)
                            , const T &xx) noexcept
  requires(T, vectorized<T>)
  {
   using t_abi = abi_type_t<T>;
   if constexpr(is_emulated_v<t_abi> ) return map(eve::exp2, xx); 
   else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::exp2, xx);
   else
   {
     using vt_t =  value_type_t<T>; 
     if constexpr(std::is_floating_point_v<vt_t>)
     {
       T k = nearest(xx);
       T x = xx-k;
       if constexpr(std::is_same_v<vt_t, float>)
       {
         // Remez polynom of degree 4 on [-0.5, 0.5] for (exp2(x)-1-x*log(2))/sqr(x)  tested in range: [-127 127]
         // 2247884800 values computed.
         // 2224606419 values (98.96%)  within 0.0 ULPs
         // 23278381 values (1.04%)   within 0.5 ULPs
         // 3.5 cycles/value  (SSE4.2 g++-4.8)
         T y = horn<T,
           0x3e75fdf1,  //    2.4022652e-01
           0x3d6356eb,  //    5.5502813e-02
           0x3c1d9422,  //    9.6178371e-03
           0x3ab01218,  //    1.3433127e-03
           0x3922c8c4   //    1.5524315e-04
           >(x);
         x = inc(fma(y, sqr(x), x*Log_2<T>()));
       }
       else
       {
         x*= Log_2<T>();
         T t =  sqr(x);
         T c = fnma(t,
                    horn<T
                   , 0x3fc555555555553eull
                   , 0xbf66c16c16bebd93ull
                   , 0x3f11566aaf25de2cull
                   , 0xbebbbd41c5d26bf1ull
                   , 0x3e66376972bea4d0ull
                    > (t), x); //x-h*t
          x = oneminus(((-(x*c)/(T(2)-c))-x));     
        }
        auto c = ldexp(x, k);
        c = if_else(is_less_equal(xx, Minlog2<T>()), eve::zero_, c);
        return if_else(is_greater_equal(xx, Maxlog2<T>()), Inf<T>(), c);
      }
      else
      {
        return if_else(is_ltz(xx), eve::zero_, bit_shl(T(1), xx));
      }
    }
  }

  template<typename T>
  EVE_FORCEINLINE auto exp2_(EVE_SUPPORTS(cpu_)
                            ,pedantic_type const & 
                            , const T &xx) noexcept
  requires(T, vectorized<T>)
  {
   using t_abi = abi_type_t<T>;
   if constexpr(is_emulated_v<t_abi> ) return map(eve::exp2, xx); 
   else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::exp2, xx);
   else
   {
     using vt_t =  value_type_t<T>; 
     if constexpr(std::is_floating_point_v<vt_t>)
     {
       T k = nearest(xx);
       T x = xx-k;
       if constexpr(std::is_same_v<vt_t, float>)
       {
         // Remez polynom of degree 4 on [-0.5, 0.5] for (exp2(x)-1-x*log(2))/sqr(x)  tested in range: [-127 127]
         // 2247884800 values computed.
         // 2224606419 values (98.96%)  within 0.0 ULPs
         // 23278381 values (1.04%)   within 0.5 ULPs
         // 3.5 cycles/value  (SSE4.2 g++-4.8)
         T y = horn<T,
           0x3e75fdf1,  //    2.4022652e-01
           0x3d6356eb,  //    5.5502813e-02
           0x3c1d9422,  //    9.6178371e-03
           0x3ab01218,  //    1.3433127e-03
           0x3922c8c4   //    1.5524315e-04
           >(x);
         x = inc(fma(y, sqr(x), x*Log_2<T>()));
       }
       else
       {
         x*= Log_2<T>();
         T t =  sqr(x);
         T c = fnma(t,
                    horn<T
                   , 0x3fc555555555553eull
                   , 0xbf66c16c16bebd93ull
                   , 0x3f11566aaf25de2cull
                   , 0xbebbbd41c5d26bf1ull
                   , 0x3e66376972bea4d0ull
                    > (t), x); //x-h*t
          x = oneminus(((-(x*c)/(T(2)-c))-x));     
        }
        auto c = pedantic_(ldexp)(x, k);
        c = if_else(is_less(xx, Minlog2<T>()), eve::zero_, c);
        return if_else(is_greater_equal(xx, Maxlog2<T>()), Inf<T>(), c);
      }
      else
      {
        return if_else(is_ltz(xx), eve::zero_, bit_shl(T(1), xx));
      }
    }
  }  
}

#endif
