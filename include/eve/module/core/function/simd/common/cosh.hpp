//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_COSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_COSH_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////////////////
  // if x = abs(a0) according x < Threshold e =  exp(x) or exp(x/2) is
  // respectively computed
  // *  in the first case cosh (e+rec(e))/2
  // *  in the second     cosh is (e/2)*e (avoiding undue overflow)
  // Threshold is Maxlog - Log_2
  //////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE  auto cosh_(EVE_SUPPORTS(cpu_)
                                     , const T &a0) noexcept
  Requires(T, Vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::cosh, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::cosh, a0);
    else
    {
     T ovflimit =  Ieee_constant<T,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
      auto x = eve::abs(a0);
      auto t = exp(x);
      auto invt = if_else(x > T(22.0f), eve::zero_, rec(t)); 
      auto c = average(t, invt); 
      auto test = x <  ovflimit-Log_2<T>(); 
      if (eve::all(test)) return c;
      
      auto w = exp(x*Half<T>());
      t = Half<T>()*w;
      t *= w;
      
      c = if_else(test, c, t);
      return c; 
    }
  }
}

#endif
