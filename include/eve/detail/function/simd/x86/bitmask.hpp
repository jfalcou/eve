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

    if constexpr( std::is_same_v<ABI, sse_>)
    {
            if constexpr( std::is_same_v<T, float > ) return type(_mm_movemask_ps(p.mask()));
      else  if constexpr( std::is_same_v<T, double> ) return type(_mm_movemask_pd(p.mask()));
      else                                            return type(_mm_movemask_epi8(p.mask()));
    }
    else if constexpr( std::is_same_v<ABI, avx_>)
    {
            if constexpr( std::is_same_v<T, float > ) return type(_mm256_movemask_ps(p.mask()));
      else  if constexpr( std::is_same_v<T, double> ) return type(_mm256_movemask_pd(p.mask()));
      else  if constexpr( current_api >= avx2       ) return type(_mm256_movemask_epi8(p.mask()));
      else
      {
        auto [l, h] = p.slice();
        return type( (h.bitmap().to_ullong() << h.size()) | l.bitmap().to_ullong() );
      }
    }
  }
}
