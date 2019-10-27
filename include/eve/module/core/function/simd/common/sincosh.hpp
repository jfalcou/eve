//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_SINCOSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_SINCOSH_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
#include <eve/function/combine.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/fnma.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <utility>
#include <type_traits>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////////////////
  // if x = abs(a0) according x < Threshold e =  exp(x) or exp(x/2) is
  // respectively computed
  // *  in the first case sincosh (e+rec(e))/2
  // *  in the second     sincosh is (e/2)*e (avoiding undue overflow)
  // Threshold is Maxlog
  //////////////////////////////////////////////////////////////////////////////
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE  auto sincosh_(EVE_SUPPORTS(cpu_)
                                     , wide<T, N, ABI> const &a0) noexcept
  requires(std::pair<wide<T, N>, wide<T, N>>, floating_point<T>)
  {

    if constexpr(is_emulated_v<ABI> ) return map(eve::sincosh, a0); 
    else if constexpr(is_aggregated_v<ABI> )
    {
      auto  [lo, hi] = a0.slice();
      auto  [xhi, ehi]   = sincosh(hi);
      auto  [xlo, elo]   = sincosh(lo);
      return {eve::combine( xlo, xhi), eve::combine( elo, ehi)}; 
    }
    else
    {
      auto x = eve::abs(a0);
      auto t = expm1(x);
      auto u = t/(t+1);
      auto z = if_else(is_less(x, One<T>()), fnma(t, u, t), u);
      auto h = copysign(Half<T>(), a0); 
      z = h*(t+z);
      auto sh =  h*if_else(is_eqz(a0)
                      , x
                      , if_else(is_greater(x, Maxlog<T>()), Inf<T>(), z)
                      );
      auto ch = inc(average(u, t)); 
      return { ch, sh }; 
    }
  }
}

#endif
