//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/function/simd/x86/specifics.hpp>
#include <eve/conditional.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N,ABI> slide_left_ ( EVE_SUPPORTS(sse2_)
                                            , wide<T,N,ABI> v, index_t<Shift>
                                            ) noexcept
  requires(Shift <= N::value)
  {
          if constexpr(Shift == 0)        return v;
    else  if constexpr(Shift == N::value) return wide<T,N,ABI>{0};
    else
    {
      if constexpr( std::same_as<ABI,x86_128_>)
      {
        constexpr auto shift = Shift*sizeof(T);
        using i_t = as_integer_t<wide<T,N,ABI>, unsigned>;

        auto const b  = bit_cast(v, as_<i_t>());
        auto result = bit_cast(i_t(_mm_bsrli_si128( b, shift)), as(v));

        // Mask noises from smaller sized registers
        if constexpr(N::value < expected_cardinal_v<T,x86_128_>)
        {
          result &= keep_first(N::value-Shift).mask(as(result)).bits();
        }

        return result;
      }
      else if constexpr( std::same_as<ABI,x86_256_>)
      {
        if constexpr( current_api >= avx2)
        {
          constexpr auto offset = Shift * sizeof(T);
          __m256i bv = _mm256_permute2x128_si256(v, v, 0x83);
                if constexpr(offset == 16)  return bv;
          else  if constexpr(offset <  16)  return _mm256_alignr_epi8(bv, v, offset);
          else                              return _mm256_bsrli_epi128(bv, offset - 16);
        }
        else if constexpr(sizeof(T) == 8)
        {
          // Three optimal shuffles for sliding left by 1->3 - The last one will shock you!
          using f_t = as_floating_point_t<wide<T,N,ABI>>;
          auto const w = bit_cast(v, as_<f_t>{});

          if constexpr(Shift == 1)
          {
            return bit_cast(f_t(_mm256_shuffle_pd(w,_mm256_permute2f128_pd(w,w,0x81),0x5)), as(v));
          }
          else if constexpr(Shift == 2)
          {
            return bit_cast(f_t(_mm256_permute2f128_pd(w, w, 0x81)), as(v));
          }
          else if constexpr(Shift == 3)
          {
            auto const s0 = _mm256_permute2f128_pd(w,w,0x81);
            return bit_cast(f_t(_mm256_shuffle_pd(s0,f_t(0),1)), as(v));
          }
        }
        else if constexpr(sizeof(T) == 4)
        {
          // Seven optimal shuffles for sliding left by 1->7 doctors want you to not know about
          using f_t = as_floating_point_t<wide<T,N,ABI>>;
          auto const w = bit_cast(v, as_<f_t>{});

          if constexpr(Shift == 1)
          {
            auto const s0 = _mm256_blend_ps(w, _mm256_permute2f128_ps(w,w,0x81), 0x11);
            return bit_cast(f_t(_mm256_permute_ps(s0, 0x39)), as(v));
          }
          else if constexpr(Shift == 2)
          {
            auto const s0 = _mm256_permute2f128_ps(w, w, 0x81);
            return bit_cast(f_t(_mm256_shuffle_ps(w, s0, 0x4e)), as(v));
          }
          else if constexpr(Shift == 3)
          {
            auto const s0 = _mm256_blend_ps(w, _mm256_permute2f128_ps(w,w,0x81), 0x77);
            return bit_cast(f_t(_mm256_permute_ps( s0, 0x93)), as(v));
          }
          else if constexpr(Shift == 4)
          {
            return bit_cast(f_t( _mm256_permute2f128_ps(w,w,0x81)),as(v));
          }
          else if constexpr(Shift == 5)
          {
            auto const s0 = _mm256_blend_ps(f_t(0), _mm256_permute2f128_ps(w,w,0x81), 0xe);
            return bit_cast(f_t(_mm256_permute_ps(s0, 0x39)),as(v));
          }
          else if constexpr(Shift == 6)
          {
            auto const s0 = _mm256_permute2f128_ps(w,w,0x81 );
            return bit_cast(f_t( _mm256_shuffle_ps(s0, f_t(0), 0xe)), as(v));
          }
          else if constexpr(Shift == 7)
          {
            auto const s0 = _mm256_blend_ps(f_t(0), _mm256_permute2f128_ps(w,w,0x81), 0x8);
            return bit_cast(f_t(_mm256_permute_ps(s0, 0x93)), as(v));
          }
        }
        else
        {
          // Small integers can be done with partial slide after slicing
          auto[l,h] = slice(v);

          // Slide higher parts as normal
          auto h0 = slide_left(h, index<(Shift>(N::value/2)) ? N::value/2 : Shift>);

          // Slide lower parts using _mm_alignr_epi8
          constexpr auto sz = sizeof(T)* Shift;
          using byte_t = typename wide<T,N,ABI>::template rebind<std::uint8_t,fixed<16>>;

          byte_t bytes = _mm_alignr_epi8(bit_cast(h,as_<byte_t>{}), bit_cast(l,as_<byte_t>{}), sz);

          // Shift everything in place
          return wide<T,N,ABI>{bit_cast(bytes, as(h0)),h0};
        }
      }
      else if constexpr( std::same_as<ABI,x86_512_>)
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
