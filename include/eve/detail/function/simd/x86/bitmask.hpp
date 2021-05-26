//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <bitset>

namespace eve::detail
{
  //================================================================================================
  // Logical to Bits
  //================================================================================================
  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto to_bits( sse2_ const&, logical<wide<T, N, ABI>> const& p ) noexcept
  {
    using type = typename logical<wide<T, N, ABI>>::bits_type;
    return bit_cast(p.mask(), as_<type>{});
  }

  //================================================================================================
  // Logical to Mask
  //================================================================================================
  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> to_mask(sse2_ const&, logical<wide<T, N, ABI>> const& p ) noexcept
  {
    if constexpr( current_api >= avx512 )
    {
      auto z = wide<T, N, ABI>(0);
      auto a = allbits(as_<wide<T, N, ABI>>());
      auto m = p.storage().value;

      if constexpr( std::same_as<abi_t<T, N>,x86_128_>)
      {
              if constexpr( std::same_as<T,double > ) return _mm_mask_blend_pd(m,z,a);
        else  if constexpr( std::same_as<T,float  > ) return _mm_mask_blend_ps(m,z,a);
        else  if constexpr( sizeof(T) == 8          ) return _mm_mask_blend_epi64(m,z,a);
        // g++ intrinsics for those two behaves strangely in O0
        else  if constexpr( sizeof(T) == 4          )
        {
          return _mm_mask_blend_epi32(m,z.storage(),a.storage());
        }
        else  if constexpr( sizeof(T) == 2          )
        {
          return _mm_mask_blend_epi16(m,z.storage(),a.storage());
        }
        else  if constexpr( sizeof(T) == 1          )
        {
          return _mm_mask_blend_epi8(m,z.storage(),a.storage());
        }
      }
      else if constexpr( std::same_as<abi_t<T, N>,x86_256_>)
      {
              if constexpr( std::same_as<T,double > ) return _mm256_mask_blend_pd(m,z,a);
        else  if constexpr( std::same_as<T,float  > ) return _mm256_mask_blend_ps(m,z,a);
        else  if constexpr( sizeof(T) == 8          ) return _mm256_mask_blend_epi64(m,z,a);
        // g++ intrinsics for those two behaves strangely in O0
        else  if constexpr( sizeof(T) == 4          )
        {
          return _mm256_mask_blend_epi32(m,z.storage(),a.storage());
        }
        else  if constexpr( sizeof(T) == 2          )
        {
          return _mm256_mask_blend_epi16(m,z.storage(),a.storage());
        }
        else  if constexpr( sizeof(T) == 1          )
        {
          return _mm256_mask_blend_epi8(m,z.storage(),a.storage());
        }
      }
      else if constexpr( std::same_as<abi_t<T, N>,x86_512_>)
      {
              if constexpr( std::same_as<T,double > ) return _mm512_mask_blend_pd(m,z,a);
        else  if constexpr( std::same_as<T,float  > ) return _mm512_mask_blend_ps(m,z,a);
        else  if constexpr( sizeof(T) == 8          ) return _mm512_mask_blend_epi64(m,z,a);
        else  if constexpr( sizeof(T) == 4          ) return _mm512_mask_blend_epi32(m,z,a);
        // g++ intrinsics for those two behaves strangely in O0
        else  if constexpr( sizeof(T) == 2          )
        {
          return _mm512_mask_blend_epi16(m,z.storage(),a.storage());
        }
        else  if constexpr( sizeof(T) == 1          )
        {
          return _mm512_mask_blend_epi8(m,z.storage(),a.storage());
        }
      }
    }
    else
    {
      return p.storage();
    }
  }

  //================================================================================================
  // Logical to Bitmap - use movemask variant
  //================================================================================================
  template<typename T, typename N, x86_abi ABI> EVE_FORCEINLINE
  std::bitset<N::value> to_bitmap(sse2_ const&, logical<wide<T, N, ABI>> const& p ) noexcept
  {
    if constexpr( !abi_t<T, N>::is_wide_logical )
    {
      return p.storage().value;
    }
    else if constexpr( std::same_as<abi_t<T, N>,x86_128_>)
    {
            if constexpr(std::is_same_v<T, float >) return _mm_movemask_ps(p.storage());
      else  if constexpr(std::is_same_v<T, double>) return _mm_movemask_pd(p.storage());
      else  if constexpr(sizeof(T) == 8)            return _mm_movemask_pd((__m128d)p.storage());
      else  if constexpr(sizeof(T) == 4)            return _mm_movemask_ps((__m128)p.storage());
      else  if constexpr(sizeof(T) == 2)
      {
        return _mm_movemask_epi8(_mm_packs_epi16(p.storage(), _mm_setzero_si128()));
      }
      else  if constexpr(sizeof(T) == 1)            return _mm_movemask_epi8(p.storage());
    }
    else if constexpr( std::same_as<abi_t<T, N>,x86_256_>)
    {
            if constexpr(std::is_same_v<T, float >) return _mm256_movemask_ps(p.storage());
      else  if constexpr(std::is_same_v<T, double>) return _mm256_movemask_pd(p.storage());
      else  if constexpr(sizeof(T) == 8)            return _mm256_movemask_pd((__m256d)p.storage());
      else  if constexpr(sizeof(T) == 4)            return _mm256_movemask_ps((__m256)p.storage());
      else  if constexpr(sizeof(T) == 2)
      {
        auto [l, h] = p.slice();
        return  _mm_movemask_epi8(_mm_packs_epi16(l, h)) ;
      }
      else  if constexpr( sizeof(T) == 1 )
      {
        if constexpr( current_api >= avx2 )
        {
          return _mm256_movemask_epi8(p.mask());
        }
        else
        {
          auto [l, h] = p.slice();
          return (h.bitmap().to_ullong() << h.size()) | l.bitmap().to_ullong();
        }
      }
    }
  }
}
