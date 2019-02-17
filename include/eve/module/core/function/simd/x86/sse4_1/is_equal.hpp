//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE4_1_IS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE4_1_IS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // sse4_1
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_equal_(EVE_SUPPORTS(sse4_1_), wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>) return as_logical_t<t_t>(_mm_cmpeq_ps(v0, v1));
      if constexpr(std::is_same_v<T, double>) return as_logical_t<t_t>(_mm_cmpeq_pd(v0, v1));
    }
    else
    {
      if constexpr(sizeof(T) == 1) return as_logical_t<t_t>(_mm_cmpeq_epi8(v0, v1));
      if constexpr(sizeof(T) == 2) return as_logical_t<t_t>(_mm_cmpeq_epi16(v0, v1));
      if constexpr(sizeof(T) == 4) return as_logical_t<t_t>(_mm_cmpeq_epi32(v0, v1));
      if constexpr(sizeof(T) == 8) return as_logical_t<t_t>(_mm_cmpeq_epi64(v0, v1));
    }
  }
}

#endif
