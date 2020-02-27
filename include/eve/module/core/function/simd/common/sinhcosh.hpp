//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_SINHCOSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_SINHCOSH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/div.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE  auto sinhcosh_(EVE_SUPPORTS(cpu_)
                                     , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::sinhcosh, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::sinhcosh, a0);
    else
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) is less than 1 sinh is computed using a polynomial(float)
      // respectively rational(double) approx from cephes.
      // else according x < Threshold e =  exp(x) or exp(x/2) is respectively
      // computed
      // *  in the first case sinh is (e-rec(e))/2 and cosh (e+rec(e))/2
      // *  in the second     sinh and cosh are (e/2)*e (avoiding undue overflow)
      // Threshold is Maxlog - Log_2 defined in Maxshlog
      //////////////////////////////////////////////////////////////////////////////
      T x = eve::abs(a0);
      auto lt1= is_less(x, One<T>());
      T bts = bitofsign(a0);
      T s = Zero<T>();
      if( bs::any(lt1))
      {
        s = detail::sinh_kernel<T>::compute(x, sqr(x));
      }
      auto test1 = is_greater(x, Maxlog<T>()-Log_2<T>());
      T fac = if_else(test1, Half<T>(), One<T>());
      T tmp = exp(x*fac);
      T tmp1 = Half<T>()*tmp;
      T rtmp = rec(tmp);
      T r = if_else(test1, tmp1*tmp, tmp1-Half<T>()*rtmp);
      return { bitwise_xor(if_else(lt1, s, r), bts), if_else(test1, r, bs::average(tmp, rtmp))};    
    }
  }
}

  
#endif
