//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_IS_NOT_GREATER_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_IS_NOT_GREATER_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_less.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_not_greater_equal_(EVE_SUPPORTS(sse2_),
                                             wide<T, N, sse_> const &v0,
                                             wide<T, N, sse_> const &v1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using t_t = wide<T, N, sse_>;
      if constexpr(std::is_same_v<T, float>) return as_logical_t<t_t>(_mm_cmpnge_ps(v0, v1));
      if constexpr(std::is_same_v<T, double>) return as_logical_t<t_t>(_mm_cmpnge_pd(v0, v1));
    }
    else
    {
      return is_less(v0, v1);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto is_not_greater_equal_(EVE_SUPPORTS(avx_),
                                             wide<T, N, avx_> const &v0,
                                             wide<T, N, avx_> const &v1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using l_t = as_logical_t<wide<T, N, avx_>>;
      if constexpr(std::is_same_v<T, float>) return l_t(_mm256_cmp_ps(v0, v1, _CMP_NGE_UQ));
      if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_NGE_UQ));
    }
    else
    {
      return is_less(v0, v1);
    }
  }
}

#endif
