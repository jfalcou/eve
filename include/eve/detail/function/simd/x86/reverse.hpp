//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T,N,ABI> reverse_( EVE_SUPPORTS(sse2_), wide<T,N,ABI> v) noexcept
  {
    const __m128i reverse_8_shorts = _mm_set_epi8(1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14);

         if constexpr ( N() == 1 ) return v;
    else if constexpr ( std::floating_point<T> )
    {
      using int_t = detail::make_integer_t<sizeof(T)>;
      using wide_int = as_wide_t<int_t, N>;

      auto as_ints = eve::bit_cast(v, eve::as_<wide_int>{});
      as_ints = reverse(as_ints);
      return eve::bit_cast(as_ints, eve::as(v));
    }
    else if constexpr( std::same_as<abi_t<T, N>, eve::x86_128_> )
    {
           if constexpr ( sizeof(T) == 8 )            return _mm_shuffle_epi32(v, _MM_SHUFFLE(1, 0, 3, 2));
      else if constexpr ( sizeof(T) == 4 && N() == 2) return _mm_shuffle_epi32(v, _MM_SHUFFLE(3, 2, 0, 1));
      else if constexpr ( sizeof(T) == 4 && N() == 4) return _mm_shuffle_epi32(v, _MM_SHUFFLE(0, 1, 2, 3));
      else if constexpr ( sizeof(T) == 2 )
      {
             if constexpr ( N() == 2 )                     return _mm_shufflelo_epi16(v, _MM_SHUFFLE(3, 2, 0, 1));
        else if constexpr ( N() == 4 )                     return _mm_shufflelo_epi16(v, _MM_SHUFFLE(0, 1, 2, 3));
        else if constexpr ( eve::current_api > eve::sse3 ) return _mm_shuffle_epi8(v, reverse_8_shorts);
        else
        {
          v = _mm_shufflehi_epi16(v, _MM_SHUFFLE(0, 1, 2, 3));
          v = _mm_shufflelo_epi16(v, _MM_SHUFFLE(0, 1, 2, 3));
          v = _mm_shuffle_epi32  (v, _MM_SHUFFLE(1, 0, 3, 2));
          return v;
        }
      }
      else if constexpr ( eve::current_api > eve::sse3 )
      {
        wide<T, N> mask{ [](int i, int) { return i >= N() ? i : N() - 1 - i; } };
        return _mm_shuffle_epi8(v, mask);
      }
      else
      {
        // convert can't do this yet
        __m128i zeroes = _mm_setzero_si128();

        auto shorts = [&]() -> as_wide_t<std::uint16_t, N> {
          if constexpr ( N() <= 8 ) return _mm_unpacklo_epi8(v, zeroes);
          else
          {
            using half = as_wide_t<std::uint16_t, eve::fixed<8>>;
            return { half{_mm_unpacklo_epi8(v, zeroes)},
                     half{_mm_unpackhi_epi8(v, zeroes)} };
          }
        }();

        shorts = reverse(shorts);

        if constexpr ( N() <= 8 ) return _mm_packus_epi16(shorts, zeroes);
        else
        {
          auto [l, h] = shorts.slice();
          return _mm_packus_epi16(l, h);
        }
      }
    }
    else if constexpr ( eve::current_api == eve::avx )
    {
      auto [l, h] = v.slice();
      l = reverse(l);
      h = reverse(h);
      return {h, l};
    }
    else if constexpr ( std::same_as<abi_t<T, N>, eve::x86_256_> )
    {
           if constexpr ( sizeof(T) == 8 ) return _mm256_permute4x64_epi64(v, _MM_SHUFFLE(0, 1, 2, 3));
      else if constexpr ( sizeof(T) == 4 ) return _mm256_permutevar8x32_epi32(v, _mm256_set_epi32(0, 1, 2, 3, 4, 5, 6, 7));
      else if constexpr ( eve::current_api >= eve::avx512 && sizeof(T) == 2)
      {
        __m256i idx = _mm256_set_epi16(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
        return _mm256_permutexvar_epi16(idx, v);
      }
      else
      {
        __m128i mask128 = (sizeof(T) == 2) ? reverse_8_shorts :
                          _mm_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
        __m256i mask   = _mm256_set_m128i(mask128, mask128);
        __m256i halves = _mm256_shuffle_epi8(v, mask);
        return _mm256_permute4x64_epi64(halves, _MM_SHUFFLE(1, 0, 3, 2));
      }
    }
    else if constexpr ( std::same_as<abi_t<T, N>, eve::x86_512_> )
    {
      if constexpr ( sizeof(T) >= 2 )
      {
        // spelling out the indexes will be a lot.
        wide<T, N, ABI> idx([](int i, int size) { return size - i - 1; });
             if constexpr ( sizeof(T) == 8 ) return _mm512_permutexvar_epi64(idx, v);
        else if constexpr ( sizeof(T) == 4 ) return _mm512_permutexvar_epi32(idx, v);
        else                                 return _mm512_permutexvar_epi16(idx, v);
      }
      else
      {
        auto [l, h] = v.slice();
        l = reverse(l);
        h = reverse(h);
        return {h, l};
      }
    }
  }
}
