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
                                           , wide<T, N> x
                                           , wide<T, N> y
                                           , index_t<Shift>
                                           )
    requires ( 0 < Shift && Shift < N::value ) &&
             native_simd_for_abi<wide<T, N>, x86_128_, x86_256_, x86_512_>
  {
    constexpr auto shifted_bytes = sizeof(T)* Shift;

    if constexpr ( std::same_as<abi_t<T, N>, x86_128_> )
    {
      using i_t = as_integer_t<wide<T,N>, unsigned>;

      i_t ab = bit_cast(x, as<i_t>{});
      i_t cd = bit_cast(y, as<i_t>{});

      i_t res;

      if constexpr ( current_api >= ssse3 ) res = _mm_alignr_epi8(cd, ab, 16 - shifted_bytes);
      else
      {
        // [aa bb]  [cc dd] => [abbc]
        // [ abb0 ] | [0 0 c]
        ab = _mm_bsrli_si128(ab, 16 - shifted_bytes);
        cd = _mm_bslli_si128(cd, shifted_bytes);
        res = _mm_or_si128(ab, cd);
      }

      return bit_cast(res, as(x));
    }
    else if constexpr( std::same_as<abi_t<T, N>, x86_256_> )
    {
      if constexpr ( current_api >= avx512 && (shifted_bytes % 4) == 0)
      {
        using i_t = as_integer_t<wide<T,N>, unsigned>;

        i_t ab = bit_cast(x, as<i_t>{});
        i_t cd = bit_cast(y, as<i_t>{});
        i_t res = _mm256_alignr_epi32(cd, ab, 8 - shifted_bytes / 4);

        return bit_cast(res, as(x));
      }
      else if constexpr ( current_api >= avx2 )
      {
        using i_t = as_integer_t<wide<T,N>, unsigned>;

        i_t ab = bit_cast(x, as<i_t>{});
        i_t cd = bit_cast(y, as<i_t>{});
        i_t bc = _mm256_permute2x128_si256(cd, ab, 0x03);

        i_t res;

             if constexpr ( shifted_bytes == 16 ) res = bc;
        else if constexpr ( shifted_bytes <  16 ) res = _mm256_alignr_epi8(cd, bc, 16 - shifted_bytes);
        else                                      res = _mm256_alignr_epi8(bc, ab, 32 - shifted_bytes);

        return bit_cast(res, as(x));
      }
      else if constexpr ( shifted_bytes % 8 == 0 )
      {
        using f_t = typename wide<T,N>::template rebind<float>;
        f_t ab = bit_cast(x, as<f_t>{});
        f_t cd = bit_cast(y, as<f_t>{});
        f_t bc = _mm256_permute2f128_ps(cd, ab, 0x03);

        f_t res;

             if constexpr ( shifted_bytes == 4 * 2 ) res = _mm256_shuffle_pd(bc, cd, 0b0101);
        else if constexpr ( shifted_bytes == 4 * 4 ) res = bc;
        else if constexpr ( shifted_bytes == 4 * 6 ) res = _mm256_shuffle_pd(ab, bc, 0b0101);

        return bit_cast(res, as(x));
      }
      // I can't come up with a 4 byte implementation
      else if constexpr ( shifted_bytes < 16 )
      {
        auto s = index<Shift>;
        auto xh = x.slice(upper_);
        auto [yl, yh] = y.slice();
        return eve::combine(slide_right_2(xh, yl, s), slide_right_2(yl, yh, s));
      }
      else
      {
        auto s = index<Shift - N{}() / 2>;
        auto [xl, xh] = x.slice();
        auto yl       = y.slice(lower_);
        return eve::combine(slide_right_2(xl, xh, s), slide_right_2(xh, yl, s));
      }
    }
    else if constexpr( std::same_as<abi_t<T, N>, x86_512_> )
    {
      using i_t = as_integer_t<wide<T,N>, signed>;

      i_t ab = bit_cast(x, as<i_t>{});
      i_t cd = bit_cast(y, as<i_t>{});

      if constexpr ( (shifted_bytes % 4) == 0 )
      {
        i_t res = _mm512_alignr_epi32(cd, ab, 16 - shifted_bytes / 4);

        return bit_cast(res, as(x));
      }
      else if constexpr ( shifted_bytes < 16 )
      {
        i_t lhs = _mm512_alignr_epi32(cd, ab, 12);
        i_t rhs = cd;
        i_t res = _mm512_alignr_epi8(rhs, lhs, 16 - shifted_bytes);

        return bit_cast(res, as(x));
      }
      else if constexpr ( shifted_bytes < 32 )
      {
        i_t lhs = _mm512_alignr_epi32(cd, ab, 8);
        i_t rhs = _mm512_alignr_epi32(cd, ab, 12);
        i_t res = _mm512_alignr_epi8(rhs, lhs , 32 - shifted_bytes);

        return bit_cast(res, as(x));
      }
      else if constexpr ( shifted_bytes < 48 )
      {
        i_t lhs = _mm512_alignr_epi32(cd, ab, 4);
        i_t rhs = _mm512_alignr_epi32(cd, ab, 8);
        i_t res = _mm512_alignr_epi8(rhs, lhs , 48 - shifted_bytes);

        return bit_cast(res, as(x));
      }
      else
      {
        i_t lhs = ab;
        i_t rhs = _mm512_alignr_epi32(cd, ab, 4);
        i_t res = _mm512_alignr_epi8(rhs, lhs, 64 - shifted_bytes);

        return bit_cast(res, as(x));
      }
    }
  }
}
