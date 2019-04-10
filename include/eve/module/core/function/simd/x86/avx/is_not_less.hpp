//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_IS_NOT_LESS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_IS_NOT_LESS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // avx
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_not_less_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v0, wide<T, N, avx_> const &v1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>) return as_logical_t<t_t>(_mm256_cmp_ps(v0, v1, _CMP_NLT_UQ));
      if constexpr(std::is_same_v<T, double>) return as_logical_t<t_t>(_mm256_cmp_pd(v0, v1, _CMP_NLT_UQ));
    }
    else
    {
      return v0 >= v1;
    }
  }

  // -----------------------------------------------------------------------------------------------
  // sse
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_not_less_(EVE_SUPPORTS(sse_), wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>) return as_logical_t<t_t>(_mm_cmp_ps(v0, v1, _CMP_NLT_UQ));
      if constexpr(std::is_same_v<T, double>) return as_logical_t<t_t>(_mm_cmp_pd(v0, v1, _CMP_NLT_UQ));
    }
    else
    {
      return v0 >= v1;
    }
  }
}

#endif
