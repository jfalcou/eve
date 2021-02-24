//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_lessgreater_(EVE_SUPPORTS(avx_),
                                       wide<T, N, x86_256_> const &v0,
                                       wide<T, N, x86_256_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_256_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)
      return l_t(_mm256_cmp_ps(v0, v1, _CMP_NEQ_OQ));
    else if constexpr(std::is_same_v<T, double>)
      return l_t(_mm256_cmp_pd(v0, v1, _CMP_NEQ_OQ));
    else if constexpr(std::is_integral_v<T>)
      return aggregate(eve::is_lessgreater, v0, v1);
  }
}

