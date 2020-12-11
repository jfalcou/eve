//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <bitset>

namespace eve::detail
{
  //================================================================================================
  // Logical to Bitmap - use movemask variant
  //================================================================================================
  template<typename T, typename N, x86_abi ABI> EVE_FORCEINLINE
  std::bitset<N::value> to_bitmap(sse2_ const&, logical<wide<T, N, ABI>> const& p ) noexcept
  {
    if constexpr( !ABI::regular_logical_register )
    {
      return p.storage().value;
    }
    else if constexpr( std::same_as<ABI,x86_128_>)
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
    else if constexpr( std::same_as<ABI,x86_256_>)
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
          return  (h.bitmap().to_ullong() << h.size()) | l.bitmap().to_ullong() ;
        }
      }
    }
  }
}
