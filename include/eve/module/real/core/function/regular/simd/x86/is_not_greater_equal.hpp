//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_not_greater_equal_(EVE_SUPPORTS(sse2_),
                                             wide<T, N, x86_128_> const &v0,
                                             wide<T, N, x86_128_> const &v1) noexcept
  {
    using l_t = as_logical_t<wide<T, N, x86_128_>>;
         if constexpr( !x86_128_::is_wide_logical ) return is_not_greater_equal_(EVE_RETARGET(cpu_), v0, v1);
    else if constexpr(std::is_same_v<T, float>)  return l_t(_mm_cmpnge_ps(v0, v1));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmpnge_pd(v0, v1));
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_not_greater_equal_(EVE_SUPPORTS(avx_),
                                             wide<T, N, x86_256_> const &v0,
                                             wide<T, N, x86_256_> const &v1) noexcept
  {
    using l_t = as_logical_t<wide<T, N, x86_256_>>;
         if constexpr( !x86_256_::is_wide_logical ) return is_not_greater_equal_(EVE_RETARGET(cpu_), v0, v1);
    else if constexpr(std::is_same_v<T, float>)  return l_t(_mm256_cmp_ps(v0, v1, _CMP_NGE_UQ));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_NGE_UQ));
  }
}
