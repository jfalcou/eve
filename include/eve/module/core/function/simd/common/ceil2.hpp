//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CEIL2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CEIL2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/max.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto ceil2_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>) { return aggregate(eve::ceil2, v); }
    else if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::ceil2, v);
    }
    else if constexpr(is_native_v<ABI>)
    {
      if constexpr(std::is_floating_point_v<value_type_t<T>>)
      {
        return exp2(ceil(v));
      }
      else 
      {
        T a0 = v; 
        T count = Zero(as(a0)); ; 
        if (a0 && !(a0 & (a0 - 1))) return a0;  
        
        while( any(is_nez(a0)))
        {  
          a0 >>= 1;
          inc[is_nez(a0)](count); 
        }  
        
        return if_else(v && !(v & (v - 1)), v, One(as(a0)) << count);
      }
    }
  }
}

#endif
