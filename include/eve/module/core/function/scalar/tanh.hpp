//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_TANH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_TANH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/rec.hpp>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto tanh_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires(T, floating_point<T>)
  {
    auto x = eve::abs(a0+a0);
    auto test =  x > 0.5493*2;
    auto t = expm1(x);
    auto rt2 = rec(t+T(2)); 
    auto z1 = fnma(T(2), rt2, T(1));
    auto z2 = t*rt2;
    auto r = test ? z1 : z2; 
    return is_negative(a0) ? -r : r; 
  }
}

#endif
