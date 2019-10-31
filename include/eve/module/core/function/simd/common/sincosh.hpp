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
#include <eve/function/combine.hpp>
#include <eve/function/copysign.hpp>
//#include <eve/function/nbtrue.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/fnma.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <utility>
#include <type_traits>

namespace eve::detail
{
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
      auto h = copysign(Half<T>(), a0);
      auto test = is_greater(x,  Maxlog<T>()); //&&is_less(x,  Maxlog<T>()+Log_2<T>()); 
//      auto nb = nbTrue(test); 
      auto t = expm1(x);
      auto u = t/(t+1);
      auto sh = h*(t+fnma(t, u, t));
      auto ch = fma(Half<T>()*t, u, One<T>());
//      if (nb == 0) return {sh, ch};
      auto z = exp(x*Half<T>());
      z = (h*z)*z; 
      sh = if_else(test, z, sh);
      ch = if_else(test, abs(sh), ch); 
      return { sh, ch };
    }
  }
}

#endif
