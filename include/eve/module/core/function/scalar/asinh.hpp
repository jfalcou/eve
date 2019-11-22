//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ASINH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ASINH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/oneosqrteps.hpp>
#include <eve/constant/sqrteps.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto asinh_(EVE_SUPPORTS(cpu_)
                                       , T a0) noexcept
  requires(T, floating_point<T>)
  {
    T x = eve::abs(a0);
    if constexpr(std::is_same_v<T, float>)
    {
      if  (x < eve::Sqrteps<T>())
      {
        return x;
      }
      else
      {
        T z;
        if (x < 0.5)
        {
          T invx = eve::rec(x);
          z = eve::log1p(x + x/(invx + eve::sqrt(fma(invx, invx, eve::One<T>()))));
        }
        else if (x > Oneosqrteps<T>())
        {
          z = log(x)+Log_2<T>();
        }
        else
        {
          z =  log(x+hypot(One<T>(), x));
        }
        return bitwise_xor(z, bitofsign(a0));
      }
    }
    else // if constexpr(std::is_same_v<T, float>)
    {
      // Exhaustive test for: boost::dispatch::functor<eve::tag::asinh_, boost::simd::tag::sse4_2_>
      //              versus:  float(boost::math::asinh(double)
      //              With T: float
      //            in range: [-3.40282e+38, 3.40282e+38]
      // 4278190078 values computed.
      // 3628470338 values (84.81%)  within 0.0 ULPs
      //  649693884 values (15.19%)  within 0.5 ULPs
      //      25856 values ( 0.00%)  within 1.0 ULPs
      T x2 = eve::sqr(x);
      T z = Zero<T>();
      
      if( x < 0.5f)
      {
        z = horn<T
          , 0x3f800000
          , 0xbe2aa9ad
          , 0x3d9949b1
          , 0xbd2ee581
          , 0x3ca4d6e6
          > (x2)*x;
      }
      else if (x > Oneosqrteps<T>())
      {
        z = log(x)+Log_2<T>();
      }
      else
      {
        z =  log(x+hypot(One<T>(), x));
      }
      return bitwise_xor(z, bitofsign(a0));
    }
  }
}

#endif
