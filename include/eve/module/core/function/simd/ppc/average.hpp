//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_AVERAGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_AVERAGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/mul.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  average_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0, wide<T, N, ppc_> const &v1) noexcept
  {
    if constexpr(std::is_integral_v<T> && sizeof(T) < 8)
    { return vec_avg(v0.storage(), v1.storage()); }
    else if constexpr(std::is_floating_point_v<T>)
    {
      auto h = Half(as(v0));
      return fma(v0, h, v1 * h);
    }
    else
    {
      return map(average, v0, v1);
    }
  }
}

#endif
