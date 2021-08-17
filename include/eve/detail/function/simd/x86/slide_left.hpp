//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/function/simd/x86/specifics.hpp>
#include <eve/conditional.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N> slide_left_ ( EVE_SUPPORTS(sse2_)
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
        auto result = bit_cast(i_t(_mm_bsrli_si128( b, shift)), as(v));

        return result;
      }
      else if constexpr( std::same_as<abi_t<T, N>,x86_256_>)
      {
        if constexpr( current_api >= avx2)
        {
          using i_t = as_integer_t<wide<T,N>>;
          constexpr auto offset = Shift * sizeof(T);

          i_t vi  = bit_cast(v, as<i_t>{});
          i_t bvi = _mm256_permute2x128_si256(vi, vi, 0x83);

          if constexpr(offset == 16)
          {
            return bit_cast(bvi,as(v));
          }
          else  if constexpr(offset <  16)
          {
            return bit_cast(i_t(_mm256_alignr_epi8 (bvi, vi, offset)) , as(v));
          }
          else
          {
            return bit_cast(i_t(_mm256_bsrli_epi128(bvi, offset - 16)), as(v));
          }
        }
        else
        {
          constexpr auto shifted_bytes = sizeof(T)* Shift;
          using f_t = typename wide<T,N>::template rebind<float>;
          auto const w  = bit_cast(v, as<f_t>{});
          auto const s0 = _mm256_permute2f128_ps(w,w,0x81 );

          if constexpr(shifted_bytes == 4 * 7)
          {
            return bit_cast(f_t(_mm256_permute_ps(_mm256_blend_ps(f_t(0), s0, 0x8), 0x93)), as(v));
          }
          else if constexpr(shifted_bytes == 4 * 6)
          {
            return bit_cast(f_t( _mm256_shuffle_ps(s0, f_t(0), 0xe)), as(v));
          }
          else  if constexpr(shifted_bytes == 4 * 5)
          {
            return bit_cast(f_t(_mm256_permute_ps(_mm256_blend_ps(f_t(0), s0, 0xe), 0x39)),as(v));
          }
          else  if constexpr(shifted_bytes == 4 * 4)
          {
            return bit_cast(f_t(s0), as(v));
          }
          else  if constexpr(shifted_bytes == 4 * 3)
          {
            return bit_cast(f_t(_mm256_permute_ps(_mm256_blend_ps(w, s0, 0x77), 0x93)), as(v));
          }
          else  if constexpr(shifted_bytes == 4 * 2 )
          {
            return bit_cast(f_t(_mm256_shuffle_ps(w, s0, 0x4e)), as(v));
          }
          else  if constexpr(shifted_bytes == 4 )
          {
            return bit_cast(f_t(_mm256_permute_ps(_mm256_blend_ps(w, s0, 0x11), 0x39)), as(v));
          }
          else
          {
            if constexpr(shifted_bytes > 16 )
            {
              auto h = _mm256_extractf128_si256(v, 0x1);
              h = _mm_bsrli_si128(h, shifted_bytes - 16);
              return _mm256_zextsi128_si256(h);
            }
            else
            {
              // Small integers can be done with partial slide after slicing
              auto[l,h] = slice(v);

              // Slide higher parts as normal
              auto h0 = slide_left(h, index<Shift>);

              // Slide lower parts using _mm_alignr_epi8
              using byte_t = typename wide<T,N>::template rebind<std::uint8_t,fixed<16>>;

              byte_t bytes = _mm_alignr_epi8( bit_cast(h,as<byte_t>{})
                                            , bit_cast(l,as<byte_t>{})
                                            , shifted_bytes
                                            );

              // Shift everything in place
              return wide<T,N>{bit_cast(bytes, as(h0)),h0};
            }
          }
        }
      }
      else if constexpr( std::same_as<abi_t<T, N>,x86_512_>)
      {
        // Generates vperm + pand, good enough for now
        return basic_swizzle(v, slide_left_pattern<Shift,N::value>);
      }
    }
  }

  template<simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE logical<Wide>
  slide_left_(EVE_SUPPORTS(avx512_), logical<Wide> v, index_t<Shift>) noexcept
  requires(Shift <= Wide::size() )
  {
          if constexpr(Shift == 0)            return v;
    else  if constexpr(Shift == Wide::size()) return logical<Wide>{false};
    else
    {
      // We use >> for slide_left due to x86 endianness of SIMD register
      auto mask = v.bitmap();
      mask >>= Shift;

      using s_t = typename logical<Wide>::storage_type;
      return s_t{static_cast<typename s_t::type>(mask.to_ulong())};
    }
  }
}
