//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_EXP2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_EXP2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
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
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto exp2_(EVE_SUPPORTS(cpu_)
                                       , T x) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using vt_t =  value_type_t<T>;
      if (is_greater_equal(x, Maxlog2<T>())) return Inf<T>();
      if (is_less_equal(x, Minlog2<T>())) return Zero<T>();
      auto k = nearest(x);
      x = x-k;
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
      return  ldexp(x, k);
    }
    else
    {
      return (x < T(0)) ? T(0) : T(1) << x; 
    }
  }

   template<typename T>
  EVE_FORCEINLINE constexpr auto exp2_(EVE_SUPPORTS(cpu_)
                                       , pedantic_type const &
                                       , T x) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using vt_t =  value_type_t<T>;
      if (is_greater_equal(x, Maxlog2<T>())) return Inf<T>();
      if (is_less(x, Minlog2<T>())) return Zero<T>();
      auto k = nearest(x);
      x = x-k;
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
      return  pedantic_(ldexp)(x, k);
    }
    else
    {
        return (x < T(0)) ? T(0) : T(1) << x; 
    }
  } 
}

#endif
