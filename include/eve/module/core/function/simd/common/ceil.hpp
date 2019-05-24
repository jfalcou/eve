//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CEIL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CEIL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/trunc.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <cassert>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto ceil_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &a0) noexcept
  requires(wide<T, N, ABI>, Arithmetic<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto z =  trunc(a0);
      return inc[z < a0](z);
    }
    else return a0;
  }
}

#endif
