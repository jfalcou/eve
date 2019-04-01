//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> mul_ ( EVE_SUPPORTS(sse4_1_),
                                          wide<T, N, sse_> const &v0,wide<T, N, sse_> const &v1
                                        ) noexcept
  {
    if constexpr(std::is_integral_v<T> && sizeof(T) == 4)
    {
      return _mm_mullo_epi32(v0, v1);
    }
    else
    {
      return mul_(EVE_RETARGET(sse2_), v0, v1);
    }
  }
}

#endif
