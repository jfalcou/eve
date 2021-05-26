//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/value.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve ::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> bit_andnot_ ( EVE_SUPPORTS(sse2_)
                                              , wide<T, N, ABI> const &v0
                                              , wide<T, N, ABI> const &v1
                                              ) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr bool i = c && category::integer_;

          if constexpr( c == category::float64x8 )            return _mm512_andnot_pd(v1, v0);
    else  if constexpr( c == category::float64x4 )            return _mm256_andnot_pd(v1, v0);
    else  if constexpr( c == category::float64x2 )            return _mm_andnot_pd(v1, v0);
    else  if constexpr( c == category::float32x16)            return _mm512_andnot_ps(v1, v0);
    else  if constexpr( c == category::float32x8 )            return _mm256_andnot_ps(v1, v0);
    else  if constexpr( c == category::float32x4 )            return _mm_andnot_ps(v1, v0);
    else  if constexpr( i && std::same_as<abi_t<T, N>,x86_128_> )     return _mm_andnot_si128(v1, v0);
    else  if constexpr( i && std::same_as<abi_t<T, N>,x86_256_> )
    {
      if constexpr( current_api >= avx2 ) return  _mm256_andnot_si256(v1, v0);
      else                                return  _mm256_castps_si256
                                                  ( _mm256_andnot_ps( _mm256_castsi256_ps(v1)
                                                                    , _mm256_castsi256_ps(v0)
                                                                    )
                                                  );
    }
    else  if constexpr( i && std::same_as<abi_t<T, N>,x86_512_> )     return _mm512_andnot_si512(v1, v0);
  }
}
