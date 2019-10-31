//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_COTH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_COTH_HPP_INCLUDED
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
  EVE_FORCEINLINE  auto coth_(EVE_SUPPORTS(cpu_)
                                     , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::coth, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::coth, a0);
    else
    {
      auto x = eve::abs(a0+a0);
      auto t = rec(expm1(x));
      auto r = fma(T(2), t, T(1)); 
      return copysign(r, a0); 
    }
  }
}

#endif
