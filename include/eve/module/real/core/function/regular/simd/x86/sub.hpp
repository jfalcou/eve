//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/saturated.hpp>

#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> sub_(EVE_SUPPORTS(sse2_), wide<T, N> v0, wide<T, N> v1) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    return v0 -= v1;
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N>
  sub_(EVE_SUPPORTS(sse2_), saturated_type st, wide<T, N> v0, wide<T, N> v1) noexcept
    requires x86_abi<abi_t<T, N>>
  {
      constexpr auto c = categorize<wide<T, N>>();

         if constexpr ( std::is_floating_point_v<T>                     ) return sub(v0, v1);
    else if constexpr ( c == category::int16x32                         ) return _mm512_subs_epi16(v0, v1);
    else if constexpr ( c == category::uint16x32                        ) return _mm512_subs_epu16(v0, v1);
    else if constexpr ( c == category::int8x64                          ) return _mm512_subs_epi8 (v0, v1);
    else if constexpr ( c == category::uint8x64                         ) return _mm512_subs_epu8 (v0, v1);
    else if constexpr ( current_api >= avx2 && c == category::int16x16  ) return _mm256_subs_epi16(v0, v1);
    else if constexpr ( current_api >= avx2 && c == category::uint16x16 ) return _mm256_subs_epu16(v0, v1);
    else if constexpr ( current_api >= avx2 && c == category::int8x32   ) return _mm256_subs_epi8 (v0, v1);
    else if constexpr ( current_api >= avx2 && c == category::uint8x32  ) return _mm256_subs_epu8 (v0, v1);
    else if constexpr ( c == category::int16x8                          ) return _mm_subs_epi16   (v0, v1);
    else if constexpr ( c == category::uint16x8                         ) return _mm_subs_epu16   (v0, v1);
    else if constexpr ( c == category::int8x16                          ) return _mm_subs_epi8    (v0, v1);
    else if constexpr ( c == category::uint8x16                         ) return _mm_subs_epu8    (v0, v1);
    else                                                                  return sub_(EVE_RETARGET(cpu_), st, v0, v1);
  }
}
