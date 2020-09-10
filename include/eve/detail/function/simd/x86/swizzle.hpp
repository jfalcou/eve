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

#include <eve/detail/implementation.hpp>
#include <eve/detail/function/simd/x86/patterns.hpp>
#include <eve/detail/function/patterns/matcher.hpp>

namespace eve::detail
{
  //================================================================================================
  // Unary swizzle
  //================================================================================================
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle( sse2_ const&, wide<T,N,x86_128_> const& v, Pattern p ) noexcept
  {
    swizzle_matcher < zero_match  , unpack_match , identity_match
                    , slide_right , slide_left   , mov_match
                    , ssse3_match , shuffle_16   , sse2_match
                    , any_match
                    > that;

    return that(p, v);
  }

//   template<typename T, typename N, typename P, int Size>
//   EVE_FORCEINLINE auto swizzle( avx_ const&
//                               , wide<T,N,x86_128_> const& v, swizzler_t<P,Size> p
//                               ) noexcept
//   {
//     constexpr auto sz = swizzler_t<P,Size>::size(N::value);
//     using that_t      = wide<T,fixed<sz>>;

//     static_assert ( is_valid_pattern<N::value>(p)
//                   , "[eve::swizzle x86::avx] - Out of range pattern index"
//                   );

//     //----------------------------------------------------------------------------------------------
//     // Handle common basic cases
//     if constexpr( !std::is_void_v<decltype(basic_swizzle(v,p))> )
//     {
//       return basic_swizzle(v,p);
//     }
//     //----------------------------------------------------------------------------------------------
//     // Handle 64 bits AVX style
//     else if constexpr(sizeof(T) == 8)
//     {
//       return swizzle_f64(v,p);
//     }
//     //----------------------------------------------------------------------------------------------
//     // Handle 32 bits AVX style
//     else if constexpr(sizeof(T) == 4)
//     {
//       return swizzle_f32(v, p, []{});
//     }
//     //----------------------------------------------------------------------------------------------
//     // Go back to SSSE3
//     else
//     {
//       return swizzle(x86_128_{},v,p);
//     }
//  }
}
