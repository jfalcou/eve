//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve ::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> bit_notand_ ( EVE_SUPPORTS(sse2_)
                                              , wide<T, N, ABI> const &v0
                                              , wide<T, N, ABI> const &v1
                                              ) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr bool i = c && category::integer_;

          if constexpr( c == category::float64x8 )            return _mm512_andnot_pd(v0,v1);
    else  if constexpr( c == category::float64x4 )            return _mm256_andnot_pd(v0,v1);
    else  if constexpr( c == category::float64x2 )            return _mm_andnot_pd(v0,v1);
    else  if constexpr( c == category::float32x16)            return _mm512_andnot_ps(v0,v1);
    else  if constexpr( c == category::float32x8 )            return _mm256_andnot_ps(v0,v1);
    else  if constexpr( c == category::float32x4 )            return _mm_andnot_ps(v0,v1);
    else  if constexpr( i && std::same_as<ABI,x86_128_> )     return _mm_andnot_si128(v0,v1);
    else  if constexpr( i && std::same_as<ABI,x86_256_> )
    {
      if constexpr( current_api >= avx2 ) return  _mm256_andnot_si256(v0,v1);
      else                                return  _mm256_castps_si256
                                                  ( _mm256_andnot_ps( _mm256_castsi256_ps(v0)
                                                                    , _mm256_castsi256_ps(v1)
                                                                    )
                                                  );
    }
    else  if constexpr( i && std::same_as<ABI,x86_512_> )     return _mm512_andnot_si512(v0,v1);
  }
}
