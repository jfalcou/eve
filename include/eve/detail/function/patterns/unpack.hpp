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
#include <eve/detail/swizzle.hpp>
#include <eve/traits/element_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // Pattern based on UNPACKHI/UNPACKLO with partial zeroing
  //================================================================================================
  struct unpack_match
  {
    template<typename Wide, typename Pattern>
    static constexpr auto is_low(Pattern const& p, as_<Wide> const&)  noexcept
    {
      auto p0 = p(0,cardinal_v<Wide>);
      auto p1 = p(1,cardinal_v<Wide>);
      auto s = cardinal_v<Wide>/2;

      return p0 == -1 ? (p1<s) : (p0<s);
    }

    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      constexpr pattern_<I...> p{};

      /*
        32 bits case has a more optimal shuffleps for missing cases
        16 bits case has a more optimal shuffle16 for missing cases
        8  bits case requires the most variants
      */
      // check for 32 bits unpacks
      constexpr bool  u32 =   sizeof(element_type_t<Out>) == 4
                      &&  (   p.is_similar(pattern< 2, 2, 3, 3>)
                          ||  p.is_similar(pattern< 2,-1, 3,-1>)
                          ||  p.is_similar(pattern<-1, 2,-1, 3>)
                          ||  p.is_similar(pattern< 1, 1, 2, 2>)
                          ||  p.is_similar(pattern< 1,-1, 2,-1>)
                          ||  p.is_similar(pattern<-1, 1,-1, 2>)
                          ||  p.is_similar(pattern< 0, 0, 1, 1>)
                          ||  p.is_similar(pattern< 0,-1, 1,-1>)
                          ||  p.is_similar(pattern<-1, 0,-1, 1>)
                          );

      // check for 16 bits unpacks
      constexpr bool  u16 =   sizeof(element_type_t<Out>) == 2
                      &&  (   p.is_similar(pattern< 4, 4, 5, 5, 6, 6, 7, 7>)
                          ||  p.is_similar(pattern< 4,-1, 5,-1, 6,-1, 7,-1>)
                          ||  p.is_similar(pattern<-1, 4,-1, 5,-1, 6,-1, 7>)
                          ||  p.is_similar(pattern< 3, 3, 4, 4, 5, 5, 6, 6>)
                          ||  p.is_similar(pattern<-1, 3,-1, 4,-1, 5,-1, 6>)
                          ||  p.is_similar(pattern< 3,-1, 4,-1, 5,-1, 6,-1>)
                          ||  p.is_similar(pattern< 2, 2, 3, 3, 4, 4, 5, 5>)
                          ||  p.is_similar(pattern<-1, 2,-1, 3,-1, 4,-1, 5>)
                          ||  p.is_similar(pattern< 2,-1, 3,-1, 4,-1, 5,-1>)
                          ||  p.is_similar(pattern< 1, 1, 2, 2, 3, 3, 4, 4>)
                          ||  p.is_similar(pattern<-1, 1,-1, 2,-1, 3,-1, 4>)
                          ||  p.is_similar(pattern< 1,-1, 2,-1, 3,-1, 4,-1>)
                          ||  p.is_similar(pattern< 0, 0, 1, 1, 2, 2, 3, 3>)
                          ||  p.is_similar(pattern< 0,-1, 1,-1, 2,-1, 3,-1>)
                          ||  p.is_similar(pattern<-1, 0,-1, 1,-1, 2,-1, 3>)
                          );

      // check for 8 bits unpacks
      constexpr bool  u8  =   sizeof(element_type_t<Out>) == 1
                      &&  (   p.is_similar(pattern< 8, 8, 9, 9,10,10,11,11,12,12,13,13,14,14,15,15>)
                          ||  p.is_similar(pattern< 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1,14,-1,15,-1>)
                          ||  p.is_similar(pattern<-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1,14,-1,15>)
                          ||  p.is_similar(pattern< 7, 7, 8, 8, 9, 9,10,10,11,11,12,12,13,13,14,14>)
                          ||  p.is_similar(pattern< 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1,14,-1>)
                          ||  p.is_similar(pattern<-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1,14>)
                          ||  p.is_similar(pattern< 6, 6, 7, 7, 8, 8, 9, 9,10,10,11,11,12,12,13,13>)
                          ||  p.is_similar(pattern< 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1>)
                          ||  p.is_similar(pattern<-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13>)
                          ||  p.is_similar(pattern< 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10,11,11,12,12>)
                          ||  p.is_similar(pattern< 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1>)
                          ||  p.is_similar(pattern<-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12>)
                          ||  p.is_similar(pattern< 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10,11,11>)
                          ||  p.is_similar(pattern< 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1>)
                          ||  p.is_similar(pattern<-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11>)
                          ||  p.is_similar(pattern< 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10>)
                          ||  p.is_similar(pattern< 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1>)
                          ||  p.is_similar(pattern<-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10>)
                          ||  p.is_similar(pattern< 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9>)
                          ||  p.is_similar(pattern< 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1>)
                          ||  p.is_similar(pattern<-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9>)
                          ||  p.is_similar(pattern< 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8>)
                          ||  p.is_similar(pattern< 1,-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1>)
                          ||  p.is_similar(pattern<-1, 1,-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8>)
                          ||  p.is_similar(pattern< 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7>)
                          ||  p.is_similar(pattern< 0,-1, 1,-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1>)
                          ||  p.is_similar(pattern<-1, 0,-1, 1,-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7>)
                          ||  p.is_similar(pattern< 9, 9,10,10,11,11,12,12>)
                          ||  p.is_similar(pattern< 9,-1,10,-1,11,-1,12,-1>)
                          ||  p.is_similar(pattern<-1, 9,-1,10,-1,11,-1,12>)
                          ||  p.is_similar(pattern<10,10,11,11,12,12,13,13>)
                          ||  p.is_similar(pattern<10,-1,11,-1,12,-1,13,-1>)
                          ||  p.is_similar(pattern<-1,10,-1,11,-1,12,-1,13>)
                          ||  p.is_similar(pattern<11,11,12,12,13,13,14,14>)
                          ||  p.is_similar(pattern<11,-1,12,-1,13,-1,14,-1>)
                          ||  p.is_similar(pattern<-1,11,-1,12,-1,13,-1,14>)
                          ||  p.is_similar(pattern<12,12,13,13,14,14,15,15>)
                          ||  p.is_similar(pattern<12,-1,13,-1,14,-1,15,-1>)
                          ||  p.is_similar(pattern<-1,12,-1,13,-1,14,-1,15>)
                          ||  p.is_similar(pattern<13,13,14,14>)
                          ||  p.is_similar(pattern<13,-1,14,-1>)
                          ||  p.is_similar(pattern<-1,13,-1,14>)
                          ||  p.is_similar(pattern<14,14,15,15>)
                          ||  p.is_similar(pattern<14,-1,15,-1>)
                          ||  p.is_similar(pattern<-1,14,-1,15>)
                          ||  p.is_similar(pattern<15,15>)
                          ||  p.is_similar(pattern<15,-1>)
                          ||  p.is_similar(pattern<-1,15>)
                          );

      return (cardinal_v<Out> > 1) && (u32 || u16 || u8);
    }
  };
}
