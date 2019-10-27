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

#endif
