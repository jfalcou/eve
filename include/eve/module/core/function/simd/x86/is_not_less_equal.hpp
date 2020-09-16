//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_not_less_equal_(EVE_SUPPORTS(sse2_),
                                          wide<T, N, sse_> const &v0,
                                          wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;
         if constexpr(std::is_same_v<T, float>)  return l_t(_mm_cmpnle_ps(v0, v1));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmpnle_pd(v0, v1));
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_not_less_equal_(EVE_SUPPORTS(avx_),
                                          wide<T, N, avx_> const &v0,
                                          wide<T, N, avx_> const &v1) noexcept
  {
    using l_t = as_logical_t<wide<T, N, avx_>>;
         if constexpr(std::is_same_v<T, float>)  return l_t(_mm256_cmp_ps(v0, v1, _CMP_NLE_UQ));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_NLE_UQ));
  }
}

