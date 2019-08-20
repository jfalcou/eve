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
#include <eve/forward.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Unary swizzle - arithmetic
  template<typename T, typename N, typename P, int Size>
  EVE_FORCEINLINE auto swizzle( sse2_ const&
                              , wide<T,N,sse_> const& v, swizzler_t<P,Size> p
                              ) noexcept
  {
    swizzle_matcher < detail::zeroing
                    , detail::unpack_hi   , detail::unpack_lo
                    , detail::identity
                    , detail::slide_right , detail::slide_left
                    , detail::movlh       , detail::movhl
                    , detail::any_ssse3
                    , detail::shuffle_16/*,shuffle_8*/
                    , detail::any_sse2
                    , detail::any_pattern
                    > that;

    return that(p, v);
  }

//   template<typename T, typename N, typename P, int Size>
//   EVE_FORCEINLINE auto swizzle( avx_ const&
//                               , wide<T,N,sse_> const& v, swizzler_t<P,Size> p
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
//       return swizzle(sse_{},v,p);
//     }
//  }
}
