//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SINCOSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SINCOSH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <utility>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto sincosh_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires(std::pair<T, T>, floating_point<T>)
  {
    T x = eve::abs(a0);
    auto h = copysign(Half<T>(), a0);
    if (x > Maxlog<T>()+Log_2<T>())
    {
      return { h*Inf<T>(), Inf<T>()}; 
    }
    else if (x > Maxlog<T>())
    {
      auto sh = exp(x*Half<T>());
      sh = ((h*sh)*sh);
      auto ch = abs(sh); 
      return { sh, ch };
    }
    else
    {
      auto t = expm1(x);
      auto u = t/(t+1);
      auto sh = fnma(t, u, t);
      sh = h*(t+sh);
      auto ch = fma(Half<T>()*t, u, One<T>());
      return { sh, ch };
    }
  }
}

#endif
