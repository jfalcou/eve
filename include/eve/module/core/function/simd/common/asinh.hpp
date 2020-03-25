//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_ASINH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_ASINH_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/average.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/nbtrue.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <tuple>


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto asinh_(EVE_SUPPORTS(cpu_)
                             , const T &a0) noexcept
  Requires(T, Vectorized<T>, behave_as<floating_point, T>)
  {
    T x =  eve::abs(a0);
    if constexpr(std::is_same_v<value_type_t<T>, double>)
    {
      auto test = is_greater(x,Oneosqrteps<T>());
      T z = if_else(test,dec(x), x+sqr(x)/eve::inc(hypot(One<T>(), x)));
      if constexpr(eve::platform::supports_infinites)
      {
        z = if_else(is_equal(x, Inf<T>()), x, z);
      }
      z =  add[test](eve::log1p(z), Log_2<T>());
      return bit_xor(bitofsign(a0), z);
    }
    else // if constexpr(std::is_same_v<value_type_t<T>, float>)
    {
      // Exhaustive test for: boost::dispatch::functor<eve::tag::asinh_, eve::tag::sse4_2_>
      //              versus: float(boost::math::asinh(double)
      //            in range: [-3.40282e+38, 3.40282e+38]
      // 4278190076 values computed.
      // 3619320676 values (84.60%)  within 0.0 ULPs
      //  658843138 values (15.40%)  within 0.5 ULPs
      //      26262 values ( 0.00%)  within 1.0 ULPs
      eve::as_logical_t<T> lthalf = is_less(x,Half<T>());
      T x2 = eve::sqr(x);
      T z = Zero<T>();
      std::size_t nb = nbtrue(lthalf);
      T bts = bitofsign(a0);
      if(nb > 0)
      {
        z = horn<T
          , 0x3f800000
          , 0xbe2aa9ad
          , 0x3d9949b1
          , 0xbd2ee581
          , 0x3ca4d6e6
          > (x2)*x;
        
        if(nb >= T::static_size) return  bit_xor(z, bts);
      }
      T tmp =  if_else(is_greater(x, Oneosqrteps<T>()),
                        x, average(x, hypot(One<T>(), x)));
#ifndef  BOOST_SIMD_NO_NANS
      return if_else(is_nan(a0), eve::allbits_, bit_xor(if_else(lthalf, z, log(tmp)+Log_2<T>()), bts));
#else
      return bit_xor(if_else(lthalf, z, log(tmp)+Log_2<T>()), bts);
#endif
    }    
  }
}

#endif

