//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SINH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SINH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/div.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sinh_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires(T, floating_point<T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::sinh, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::sinh, a0);
    else
    {
      if(is_eqz(a0) || is_infinite(a0)) return a0; 
      auto x = eve::abs(a0);
      auto h = copysign(Half<T>(), a0); 
      auto t = expm1(x);
      auto u = t/(t+1);
      auto z = is_less(x, Maxlog<T>()) ? fnma(t, u, t) : u;
      return h*(t+z); 
    }; 
  }
}

#endif
