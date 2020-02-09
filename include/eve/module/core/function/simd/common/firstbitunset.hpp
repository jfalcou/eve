//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FIRSTBITUNSET_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FIRSTBITUNSET_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/constant/one.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto firstbitunset_(EVE_SUPPORTS(cpu_)
                                   , wide<T, N, ABI> const &a0) noexcept
  requires(wide<T, N, ABI>, integral<T>)
  {
    return ~a0 & (a0+One(as(a0)));
  }
}

#endif
