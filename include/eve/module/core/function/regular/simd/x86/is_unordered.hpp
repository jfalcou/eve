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
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/constant/false.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_unordered_(EVE_SUPPORTS(sse2_),
                                     wide<T, N, x86_128_> const &v0,
                                     wide<T, N, x86_128_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_128_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>) return l_t(_mm_cmpunord_ps(v0, v1));
    if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmpunord_pd(v0, v1));
    if constexpr(std::is_integral_v<T>) return false_(eve::as<l_t>());
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_unordered_(EVE_SUPPORTS(avx_), wide<T, N, x86_256_> const &v0, wide<T, N, x86_256_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_256_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>) return l_t(_mm256_cmp_ps(v0, v1, _CMP_UNORD_Q));
    if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_UNORD_Q));
    if constexpr(std::is_integral_v<T>) return false_(eve::as<l_t>());
  }
}
