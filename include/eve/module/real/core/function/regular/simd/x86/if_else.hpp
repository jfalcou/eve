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
#include <eve/detail/function/to_logical.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <type_traits>

namespace eve::detail
{
  //================================================================================================
  // X86 if_else
  template<scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> if_else_( EVE_SUPPORTS(sse4_1_)
                                          , logical<wide<T, N>> const &v0
                                          , wide<T, N> const &v1
                                          , wide<T, N> const &v2
                                          ) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T,N>>();

    if constexpr( !abi_t<T, N>::is_wide_logical )
    {
      auto const msk =v0.storage().value;
      auto const s1 =v1.storage();
      auto const s2 =v2.storage();

            if constexpr( c == category::float64x8    ) return _mm512_mask_blend_pd(msk,s2,s1);
      else  if constexpr( c == category::float64x4    ) return _mm256_mask_blend_pd(msk,s2,s1);
      else  if constexpr( c == category::float64x2    ) return _mm_mask_blend_pd(msk,s2,s1);
      else  if constexpr( c == category::float32x16   ) return _mm512_mask_blend_ps(msk,s2,s1);
      else  if constexpr( c == category::float32x8    ) return _mm256_mask_blend_ps(msk,s2,s1);
      else  if constexpr( c == category::float32x4    ) return _mm_mask_blend_ps(msk,s2,s1);
      else  if constexpr( c == category::int64x8    ) return _mm512_mask_blend_epi64(msk,s2,s1);
      else  if constexpr( c == category::uint64x8   ) return _mm512_mask_blend_epi64(msk,s2,s1);
      else  if constexpr( c == category::int64x4    ) return _mm256_mask_blend_epi64(msk,s2,s1);
      else  if constexpr( c == category::uint64x4   ) return _mm256_mask_blend_epi64(msk,s2,s1);
      else  if constexpr( c == category::int64x2    ) return _mm_mask_blend_epi64(msk,s2,s1);
      else  if constexpr( c == category::uint64x2   ) return _mm_mask_blend_epi64(msk,s2,s1);
      else  if constexpr( c == category::int32x16   ) return _mm512_mask_blend_epi32(msk,s2,s1);
      else  if constexpr( c == category::uint32x16  ) return _mm512_mask_blend_epi32(msk,s2,s1);
      else  if constexpr( c == category::int32x8    ) return _mm256_mask_blend_epi32(msk,s2,s1);
      else  if constexpr( c == category::uint32x8   ) return _mm256_mask_blend_epi32(msk,s2,s1);
      else  if constexpr( c == category::int32x4    ) return _mm_mask_blend_epi32(msk,s2,s1);
      else  if constexpr( c == category::uint32x4   ) return _mm_mask_blend_epi32(msk,s2,s1);
      else  if constexpr( c == category::int16x32   ) return _mm512_mask_blend_epi16(msk,s2,s1);
      else  if constexpr( c == category::uint16x32  ) return _mm512_mask_blend_epi16(msk,s2,s1);
      else  if constexpr( c == category::int16x16   ) return _mm256_mask_blend_epi16(msk,s2,s1);
      else  if constexpr( c == category::uint16x16  ) return _mm256_mask_blend_epi16(msk,s2,s1);
      else  if constexpr( c == category::int16x8    ) return _mm_mask_blend_epi16(msk,s2,s1);
      else  if constexpr( c == category::uint16x8   ) return _mm_mask_blend_epi16(msk,s2,s1);
      else  if constexpr( c == category::int8x64    ) return _mm512_mask_blend_epi8(msk,s2,s1);
      else  if constexpr( c == category::uint8x64   ) return _mm512_mask_blend_epi8(msk,s2,s1);
      else  if constexpr( c == category::int8x32    ) return _mm256_mask_blend_epi8(msk,s2,s1);
      else  if constexpr( c == category::uint8x32   ) return _mm256_mask_blend_epi8(msk,s2,s1);
      else  if constexpr( c == category::int8x16    ) return _mm_mask_blend_epi8(msk,s2,s1);
      else  if constexpr( c == category::uint8x16   ) return _mm_mask_blend_epi8(msk,s2,s1);
    }
    else
    {
      auto msk = bit_cast(v0.bits(),as(v2));

            if constexpr( c == category::float64x4   ) return _mm256_blendv_pd(v2, v1, msk);
      else  if constexpr( c == category::float64x2   ) return _mm_blendv_pd   (v2, v1, msk);
      else  if constexpr( c == category::float32x8   ) return _mm256_blendv_ps(v2, v1, msk);
      else  if constexpr( c == category::float32x4   ) return _mm_blendv_ps   (v2, v1, msk);
      else
      {
        if constexpr( std::same_as<abi_t<T, N>, x86_128_> ) return _mm_blendv_epi8(v2, v1, msk);
        else if constexpr(current_api >= avx2)
        {
          using a_t = wide<as_integer_t<T>, N>;
          return _mm256_blendv_epi8(v2, v1, bit_cast(v0.bits(),as_<a_t>()));
        }
        else
        {
                if constexpr(sizeof(T) <= 2)      return aggregate(if_else, v0, v1, v2);
          else  if constexpr(sizeof(T) >= 4)
          {
            using f_t = wide<as_floating_point_t<T>, N>;
            return bit_cast( if_else( v0, bit_cast(v1,as_<f_t>()), bit_cast(v2,as_<f_t>())), as(v2));
          }
        }
      }
    }
  }

  //================================================================================================
  // Full logical if_else
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(sse2_)
                                , logical<wide<T, N>> const &v0
                                , logical<wide<T, N>> const &v1
                                , logical<wide<T, N>> const &v2
                                ) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    if constexpr( !abi_t<T, N>::is_wide_logical )
    {
      using s_t = typename logical<wide<T,N>>::storage_type;
      auto    r = bit_select(v0.storage().value,v1.storage().value,v2.storage().value);
      return logical<wide<T,N>>( s_t{r} );
    }
    else
    {
      return bit_cast(if_else(v0, v1.mask(), v2.mask()), as(v0));
    }
  }
}
