//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  div_(EVE_SUPPORTS(vsx_), wide<T, N, ppc_> const &v0, wide<T, N, ppc_> const &v1) noexcept
  {
    if constexpr(std::is_floating_point_v<T> && current_api == eve::vsx)
    { return vec_div(v0.storage(), v1.storage()); }
    else
    {
      return map(eve::div, v0, v1);
    }
  }
}

#endif
