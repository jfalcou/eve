//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_IF_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE wide<U, N, sse_> if_else_(EVE_SUPPORTS(sse4_1_)
                                           , wide<T, N, sse_> const &v0
                                           , wide<U, N, sse_> const &v1
                                           , wide<U, N, sse_> const &v2) noexcept
  {
    using u_t = wide<U, N, sse_>;

    if constexpr(std::is_same_v<U, float>)   return _mm_blendv_ps(v2, v1, bitwise_cast<u_t>(bitwise_mask(v0)));
    if constexpr(std::is_same_v<U, double>)  return _mm_blendv_pd(v2, v1, bitwise_cast<u_t>(bitwise_mask(v0)));
    if constexpr(std::is_integral_v<U>)      return _mm_blendv_epi8(v2, v1, bitwise_cast<u_t>(bitwise_mask(v0)));
  }
}

#endif
