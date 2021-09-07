//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/bit_cast.hpp>

namespace eve::detail
{

  template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N> slide_right_2_ ( EVE_SUPPORTS(sse2_)
                                           , wide<T, N> _x
                                           , wide<T, N> _y
                                           , index_t<Shift>
                                           )
    requires ( 0 < Shift && Shift < N::value ) &&
             native_simd_for_abi<wide<T, N>, x86_128_>
  {
    constexpr int bytes_shift = Shift * sizeof(T);

    using i_t = as_integer_t<wide<T,N>, unsigned>;

    if constexpr ( std::same_as<abi_t<T, N>, x86_128_> )
    {
      __m128i x = bit_cast(_x, as<i_t>{});
      __m128i y = bit_cast(_y, as<i_t>{});

      if constexpr ( current_api >= ssse3 ) return bit_cast(_mm_alignr_epi8(y, x, 16 - bytes_shift), as(_x));
      else
      {
        // [aa bb]  [cc dd] => [abbc]
        // [ abb0 ] | [0 0 c]
        x = _mm_bsrli_si128(x, 16 - bytes_shift);
        y = _mm_bslli_si128(y, bytes_shift);
        return bit_cast(_mm_or_si128(x, y), as(_x));
      }
    }
  }
}
