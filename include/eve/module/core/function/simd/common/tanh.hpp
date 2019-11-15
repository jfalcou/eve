//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_TANH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_TANH_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/rec.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE  auto tanh_(EVE_SUPPORTS(cpu_)
                                     , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::tanh, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::tanh, a0);
    else
    {
    auto x = eve::abs(a0+a0);
    auto test =  x > 0.5493*2;
    auto t = expm1(x);
    auto rt2 = rec(t+T(2)); 
    auto z1 = fnma(T(2), rt2, T(1));
    auto z2 = t*rt2;
    auto r = if_else(test, z1, z2); 
    return copysign(r, a0); 
    }
  }
}

#endif
