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
#include <eve/function/combine.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/div.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE  auto sinhcosh_(EVE_SUPPORTS(cpu_)
                                     , const T &a0) noexcept
  requires(std::tuple<T, T>, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::sinhcosh, a0); 
    else if constexpr(is_aggregated_v<t_abi> )
    {
      auto  [lo, hi] = a0.slice();
      auto  [xhi, ehi]   = sinhcosh(hi);
      auto  [xlo, elo]   = sinhcosh(lo);
      return std::make_tuple(eve::combine( xlo, xhi), eve::combine( elo, ehi)); 
    }
    else
    {
      T ovflimit =  Ieee_constant<T,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
      auto h = if_else( is_positive(a0), One<T>(), Mone<T>());   
      auto x = eve::abs(a0);
      auto t = expm1(x);
      auto inct = inc(t); 
      auto u = t/inct;
      auto z =  fnma(t, u, t);
      auto s = Half<T>()*h*(z+t);
      auto invt = if_else(x > T(22.0f), eve::zero_, rec(inct)); 
      auto c = average(inct, invt); 
      auto test = x <  ovflimit; 
      if (eve::all(test)) return std::make_tuple(s, c);
      
      auto w = exp(x*Half<T>());
      t = Half<T>()*w;
      t *= w;
      
      s = if_else(test, s, t*h);
      c = if_else(test, c, t);
      return std::make_tuple(s, c);
    }
  }
}

  
#endif
