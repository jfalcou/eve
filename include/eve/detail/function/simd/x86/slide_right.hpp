//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N> slide_right_ ( EVE_SUPPORTS(sse2_)
                                            , wide<T,N> v, index_t<Shift>
                                            ) noexcept
  requires(Shift <= N::value) && x86_abi<abi_t<T, N>>
  {
          if constexpr(Shift == 0)        return v;
    else  if constexpr(Shift == N::value) return wide<T,N>{0};
    else
    {
      if constexpr( std::same_as<abi_t<T, N>,x86_128_>)
      {
        constexpr auto shift = Shift*sizeof(T);
        using i_t = as_integer_t<wide<T,N>, unsigned>;

        auto const b  = bit_cast(v, as<i_t>());
        return bit_cast(i_t(_mm_bslli_si128( b, shift)), as(v));
      }
      else if constexpr( std::same_as<abi_t<T, N>,x86_256_>)
      {
        if constexpr( current_api >= avx2)
        {
          using i_t = as_integer_t<wide<T,N>>;
          constexpr auto offset = Shift * sizeof(T);

          i_t vi  = bit_cast(v, as<i_t>{});
          i_t bvi = _mm256_permute2x128_si256(vi, vi, 0x08);

          if constexpr(offset == 16)
          {
            return bit_cast(bvi,as(v));
          }
          else  if constexpr(offset <  16)
          {
            return bit_cast(i_t(_mm256_alignr_epi8 (vi, bvi, 16 - offset)) , as(v));
          }
          else
          {
            return bit_cast(i_t(_mm256_bslli_epi128(bvi, offset - 16)), as(v));
          }
        }
        else
        {
          constexpr auto shifted_bytes = sizeof(T)* Shift;
          using f_t = typename wide<T,N>::template rebind<float>;
          auto const w  = bit_cast(v, as<f_t>{});
          auto const s0 = _mm256_permute2f128_ps(w,w,0x08 );

          if constexpr(shifted_bytes == 4 * 7)
          {
            return bit_cast(f_t(_mm256_permute_ps(_mm256_blend_ps(s0, f_t(0), 0xef), 0x39)),as(v));
          }
          else if constexpr(shifted_bytes == 4 * 6)
          {
            return bit_cast(f_t( _mm256_shuffle_ps(f_t{0}, s0, 0x40) ), as(v));
          }
          else  if constexpr(shifted_bytes == 4 * 5)
          {
            return bit_cast(f_t(_mm256_permute_ps(_mm256_blend_ps(s0, f_t(0), 0x8f), 0x93)),as(v));
          }
          else  if constexpr(shifted_bytes == 4 * 4)
          {
            return bit_cast(f_t(s0), as(v));
          }
          else  if constexpr(shifted_bytes == 4 * 3)
          {
            return bit_cast(f_t(_mm256_permute_ps(_mm256_blend_ps(s0, w, 0x11), 0x39)), as(v));
          }
          else  if constexpr(shifted_bytes == 4 * 2 )
          {
            return bit_cast(f_t(_mm256_shuffle_ps(s0, w, 0x4e)), as(v));
          }
          else  if constexpr(shifted_bytes == 4 )
          {
            return bit_cast(f_t(_mm256_permute_ps(_mm256_blend_ps(s0, w, 0x77), 0x93)), as(v));
          }
          else
          {
            if constexpr(shifted_bytes > 16 )
            {
              // generates [ 0 .. v0 <0 .. 0> ]
              wide<T,N> h = _mm256_zextsi128_si256( _mm_bslli_si128 ( v.slice(lower_)
                                                                        , shifted_bytes - 16
                                                                        )
                                                      );

              // permutes so we have [ <0 .. 0> 0 .. v0 ]
              auto g = bit_cast(h, as<f_t>{});
              return bit_cast(_mm256_permute2f128_ps(g,g,0x01), as(v));
            }
            else
            {
              using byte_t = typename wide<T,N>::template rebind<std::uint8_t,fixed<16>>;
              using tgt_t  = as<byte_t>;

              // Slide lower parts as normal
              auto [l,h] = v.slice();
              auto l0 = slide_right(l, index<Shift>);

              // Compute how many bytes to realign
              constexpr auto sz = sizeof(T) * (N::value/2-Shift);

              // Slide lower parts using _mm_alignr_epi8
              byte_t bytes = _mm_alignr_epi8(bit_cast(h,tgt_t{}), bit_cast(l,tgt_t{}), sz);
              return wide<T,N>{l0,bit_cast(bytes, as(l0))};
            }
          }
        }
      }
      else if constexpr( std::same_as<abi_t<T, N>,x86_512_>)
      {
        // Generates vperm + pand, good enough for now
        return basic_swizzle(v, slide_right_pattern<Shift,N::value>);
      }
    }
  }

  template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N> slide_right_ ( EVE_SUPPORTS(sse2_)
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
        return eve::combine(slide_right(xh, yl, s), slide_right(yl, yh, s));
      }
      else
      {
        auto s = index<Shift - N{}() / 2>;
        auto [xl, xh] = x.slice();
        auto yl       = y.slice(lower_);
        return eve::combine(slide_right(xl, xh, s), slide_right(xh, yl, s));
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

  template<simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE logical<Wide>
  slide_right_(EVE_SUPPORTS(avx512_), logical<Wide> v, index_t<Shift>) noexcept
  requires(Shift <= Wide::size() )
  {
          if constexpr(Shift == 0)            return v;
    else  if constexpr(Shift == Wide::size()) return logical<Wide>{false};
    else
    {
      // We use << for slide_right due to x86 endianness of SIMD register
      auto mask = v.bitmap();
      mask <<= Shift;

      using s_t = typename logical<Wide>::storage_type;
      return s_t{static_cast<typename s_t::type>(mask.to_ulong())};
    }
  }

  template<simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE logical<Wide>
  slide_right_(EVE_SUPPORTS(avx512_), logical<Wide> x, logical<Wide> y, index_t<Shift>) noexcept
  requires(Shift <= Wide::size() )
  {
         if constexpr ( Shift == 0            ) return y;
    else if constexpr ( Shift == Wide::size() ) return x;
    else
    {
      auto xmask = x.bitmap();
      auto ymask = y.bitmap();

      // Shifts invert due to the endianness
      xmask >>= Wide::size() - Shift;
      ymask <<= Shift;

      using s_t = typename logical<Wide>::storage_type;
      return s_t{static_cast<typename s_t::type>((xmask | ymask).to_ulong())};
    }
  }
}
