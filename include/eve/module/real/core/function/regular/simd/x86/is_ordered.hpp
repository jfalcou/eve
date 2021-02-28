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
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/constant/true.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_ordered_(EVE_SUPPORTS(sse2_), wide<T, N, x86_128_> const &v0, wide<T, N, x86_128_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_128_>;
    using l_t = as_logical_t<t_t>;

    if constexpr( current_api >= eve::avx512 )
    {
           if constexpr ( std::is_same_v<T, float> )  return l_t(_mm_cmp_ps_mask(v0, v1, _CMP_ORD_Q));
      else if constexpr ( std::is_same_v<T, double> ) return l_t(_mm_cmp_pd_mask(v0, v1, _CMP_ORD_Q));
      else                                            return true_(eve::as<l_t>());
    }
    else if constexpr(std::is_same_v<T, float>) return l_t(_mm_cmpord_ps(v0, v1));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmpord_pd(v0, v1));
    else if constexpr(std::is_integral_v<T>) return true_(eve::as<l_t>());
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_ordered_(EVE_SUPPORTS(avx_), wide<T, N, x86_256_> const &v0, wide<T, N, x86_256_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_256_>;
    using l_t = as_logical_t<t_t>;

    if constexpr( current_api >= eve::avx512 )
    {
           if constexpr ( std::is_same_v<T, float> )  return l_t(_mm256_cmp_ps_mask(v0, v1, _CMP_ORD_Q));
      else if constexpr ( std::is_same_v<T, double> ) return l_t(_mm256_cmp_pd_mask(v0, v1, _CMP_ORD_Q));
      else                                            return true_(eve::as<l_t>());
    }
    else if constexpr(std::is_same_v<T, float>) return l_t(_mm256_cmp_ps(v0, v1, _CMP_ORD_Q));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_ORD_Q));
    else if constexpr(std::is_integral_v<T>) return true_(eve::as<l_t>());
  }

  // -----------------------------------------------------------------------------------------------
  // 512 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_ordered_(EVE_SUPPORTS(avx512_), wide<T, N, x86_512_> const &v0, wide<T, N, x86_512_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_512_>;
    using l_t = as_logical_t<t_t>;

         if constexpr ( std::is_same_v<T, float> )  return l_t(_mm512_cmp_ps_mask(v0, v1, _CMP_ORD_Q));
    else if constexpr ( std::is_same_v<T, double> ) return l_t(_mm512_cmp_pd_mask(v0, v1, _CMP_ORD_Q));
    else                                            return true_(eve::as<l_t>());
  }
}
