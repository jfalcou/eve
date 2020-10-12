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
//#include <eve/detail/function/simd/ppc/patterns.hpp>
#include <eve/detail/function/patterns/matcher.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Unary swizzle - arithmetic
  template<typename T, typename N, ppc_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle( ppc_ const&, wide<T,N,ABI> const& v, Pattern p ) noexcept
  {
    swizzle_matcher < zero_match, identity_match, broadcast_match
                    , slide_left, slide_right
                    , merge_match
                    , any_match
                    > that;

    return that(p, v);
  }
//   //------------------------------------------------------------------------------------------------
//   // Unary swizzle - arithmetic
//   template<typename T, typename N, typename P, int Size>
//   EVE_FORCEINLINE auto swizzle( ppc_ const&
//                               , wide<T,N,ppc_> const& v, swizzler_t<P,Size> p
//                               ) noexcept
//   {
//     //----------------------------------------------------------------------------------------------
//     // Check for slide right swizzle
//     else if constexpr( constexpr auto s = match_slide_right<sz>(p); s != -1 )
//     {
//       constexpr auto offset = (s * sizeof(T)) << 3;
//       __vector unsigned char shift = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,offset};
//       return that_t( vec_sro(v.storage(), shift) );
//     }
//     //----------------------------------------------------------------------------------------------
//     // Check for slide left swizzle
//     else if constexpr( constexpr auto s = match_slide_left<sz>(p); s != -1 )
//     {
//       constexpr auto offset = (s * sizeof(T)) << 3;
//       __vector unsigned char shift = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,offset};
//       return that_t( vec_slo(v.storage(), shift) );
//     }
//     //----------------------------------------------------------------------------------------------
//     // Check for self-merge-high swizzle
//     else if constexpr( match_pattern<sz>(p, merger<1,1,0>) )
//     {
//       return that_t( vec_mergeh(v.storage(), v.storage()) );
//     }
//     //----------------------------------------------------------------------------------------------
//     // Check for self-merge-low swizzle
//     else if constexpr( match_pattern<sz>(p, merger<1,1,sz/2>) )
//     {
//       return that_t( vec_mergel(v.storage(), v.storage()) );
//     }
//   }
// }
