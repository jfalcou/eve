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
    swizzle_matcher < zero_match  , broadcast_match
                    , slide_left  , unpack_match
                    , identity_match
                    , slide_right , mov_match
                    , ssse3_match , shuffle_16, sse2_match
                    , any_match
                    > match_with;

    return match_with(p, v);
  }

  //================================================================================================
  // Binary shuffle
  //================================================================================================
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto shuffle_ (  EVE_SUPPORTS(sse2_)
                                , wide<T,N,x86_128_> const& a, wide<T,N,x86_128_> const& b
                                , Pattern p
                                ) noexcept
  {
    swizzle_matcher < mov_binary_match
                    , ssse3_match, sse2_binary_match
                    , any_match
                    > match_with;

    return match_with(p, a, b);
  }

//   template<typename T, typename N, typename P, int Size>
//   EVE_FORCEINLINE auto swizzle( avx_ const&
//                               , wide<T,N,x86_256_> const& v, swizzler_t<P,Size> p
//                               ) noexcept
//   {
/*
    swizzle_matcher < zero_match  , broadcast_match
                    , slide_left  , unpack_match
                    , identity_match
                    , slide_right , mov_match
                    , ssse3_match , shuffle_16, sse2_match
                    , any_match
                    > match_with;

    return match_with(p, v);
*/
//  }
}
