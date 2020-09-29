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
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/meta.hpp>
#include <bitset>

namespace eve::detail
{
  //================================================================================================
  // Logical to Bitmap - use movemask variant
  //================================================================================================
  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto to_bitmap( sse2_ const&, logical<wide<T, N, ABI>> const& p ) noexcept
  {
    using type = std::bitset<N::value>;

    if constexpr( std::is_same_v<ABI, x86_128_>)
    {
            if constexpr( std::is_same_v<T, float > ) return type(_mm_movemask_ps(p.mask()));
      else  if constexpr( std::is_same_v<T, double> ) return type(_mm_movemask_pd(p.mask()));
      else  if constexpr( std::is_integral_v<T> )
      {

              if constexpr( sizeof(T) == 1 ) return type(_mm_movemask_epi8(p.mask()));
        else  if constexpr( sizeof(T) == 2 )
        {
          if constexpr( current_api >= ssse3 )
          {
            __m128i mask =  _mm_setr_epi8 ( 0x01,0x03,0x05,0x07,0x09,0x0B,0x0D,0x0F
                                          , -128,-128,-128,-128,-128,-128,-128,-128
                                          );

            return type( _mm_movemask_epi8(_mm_shuffle_epi8(p.storage(),mask)) );
          }
          else
          {
            return type(_mm_movemask_epi8(_mm_packs_epi16(p.storage(), _mm_setzero_si128())));
          }
        }
        else  if constexpr( sizeof(T) >= 4 )
        {
          using tgt = logical<wide<as_floating_point_t<T>, N>>;
          return bit_cast(p,as_<tgt>()).bitmap();
        }
      }
    }
    else if constexpr( std::is_same_v<ABI, x86_256_>)
    {
            if constexpr( std::is_same_v<T, float > ) return type(_mm256_movemask_ps(p.mask()));
      else  if constexpr( std::is_same_v<T, double> ) return type(_mm256_movemask_pd(p.mask()));
      else  if constexpr( sizeof(T) >= 4 )
      {
        using type = logical<wide<as_floating_point_t<T>, N>>;
        return bit_cast(p,as_<type>()).bitmap();
      }
      else if constexpr( sizeof(T) == 2 )
      {
        auto [l, h] = p.slice();
        return type( _mm_movemask_epi8(_mm_packs_epi16(l, h)) );
      }
      else if constexpr( sizeof(T) == 1 )
      {
        if constexpr( current_api >= avx2 )
        {
          return type(_mm256_movemask_epi8(p.mask()));
        }
        else
        {
          auto [l, h] = p.slice();
          return type( (h.bitmap().to_ullong() << h.size()) | l.bitmap().to_ullong() );
        }
      }
    }
  }
}
