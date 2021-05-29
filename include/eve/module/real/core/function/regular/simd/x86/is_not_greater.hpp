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
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_not_greater_(EVE_SUPPORTS(sse2_),
                                       wide<T, N> const &v0,
                                       wide<T, N> const &v1) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    using t_t = wide<T, N>;
    using l_t = as_logical_t<t_t>;

         if constexpr( !x86_128_::is_wide_logical ) return is_not_greater_(EVE_RETARGET(cpu_), v0, v1);
    else if constexpr(std::is_same_v<T, float>)  return l_t(_mm_cmpngt_ps(v0, v1));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmpngt_pd(v0, v1));
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_not_greater_(EVE_SUPPORTS(avx_),
                                       wide<T, N> const &v0,
                                       wide<T, N> const &v1) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    using t_t = wide<T, N>;
    using l_t = as_logical_t<t_t>;

         if constexpr( !x86_256_::is_wide_logical ) return is_not_greater_(EVE_RETARGET(cpu_), v0, v1);
    else if constexpr(std::is_same_v<T, float>)  return l_t(_mm256_cmp_ps(v0, v1, _CMP_NGT_UQ));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_NGT_UQ));
  }
}
