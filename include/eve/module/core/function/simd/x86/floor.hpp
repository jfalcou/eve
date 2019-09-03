//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_FLOOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_FLOOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE wide<T, N, sse_> floor_(EVE_SUPPORTS(sse4_1_),
                                          wide<T, N, sse_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>) return _mm_floor_pd(a0);
    if constexpr(std::is_same_v<T, float>)
      return _mm_floor_ps(a0);
    else
      return a0;
  }

  //-----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE wide<T, N, avx_> floor_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
      return _mm256_round_pd(a0, _MM_FROUND_FLOOR);
    else if constexpr(std::is_same_v<T, float>)
      return _mm256_round_ps(a0, _MM_FROUND_FLOOR);
    else
      return a0;
  }
}

#endif
