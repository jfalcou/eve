//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_IS_GREATER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_IS_GREATER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/is_greater.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // avx2
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_greater_(EVE_SUPPORTS(avx2_), wide<T, N, avx_> const &v0, wide<T, N, avx_> const &v1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>)
        return as_logical_t<t_t>(_mm256_cmp_ps(v0, v1, _CMP_GT_OQ));
      if constexpr(std::is_same_v<T, double>)
        return as_logical_t<t_t>(_mm256_cmp_pd(v0, v1, _CMP_GT_OQ));
    }
    else
    {
      if constexpr(std::is_signed_v<T>)
      {
        if constexpr(sizeof(T) == 1) return as_logical_t<t_t>(_mm256_cmpgt_epi8(v0, v1));
        if constexpr(sizeof(T) == 2) return as_logical_t<t_t>(_mm256_cmpgt_epi16(v0, v1));
        if constexpr(sizeof(T) == 4) return as_logical_t<t_t>(_mm256_cmpgt_epi32(v0, v1));
        if constexpr(sizeof(T) == 8) return as_logical_t<t_t>(_mm256_cmpgt_epi64(v0, v1));
      }
      if constexpr(std::is_unsigned_v<T>)
      {
        using s_t    = eve::wide<eve::detail::as_integer_t<T, signed>, N, avx_>;
        using l_t    = eve::as_logical_t<t_t>;
        s_t const sm = Signmask<s_t>();
        return bitwise_cast<l_t>(
            eve::is_greater(bitwise_cast<s_t>(v0) - sm, bitwise_cast<s_t>(v1) - sm));
      }
    }
  }
}

#endif
