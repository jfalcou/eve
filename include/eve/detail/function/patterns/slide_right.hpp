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

#include <eve/patterns.hpp>

namespace eve::detail
{
  //================================================================================================
  // Slide data right
  //================================================================================================
  struct slide_right
  {
    template<std::ptrdiff_t... I>
    static constexpr auto find_slide(pattern_<I...> const& p)  noexcept
    {
      std::ptrdiff_t c = sizeof...(I);
      std::ptrdiff_t i = 0;

      while(p(i,c)==-1 && i<c) i++;

      return i;
    }

    template<std::ptrdiff_t... I, typename Wide>
    static constexpr auto check(pattern_<I...> const& p, as_<Wide> const&)  noexcept
    {
      constexpr auto c = cardinal_v<Wide>;
      if(c==1) return false;

      // Find where the -1 streak ends
      int i = find_slide(p), res = i;

      // Check we have partial identity afterward
      for(;i<c;++i)
        if( p(i,c) != i-res)
          return false;

      return c <= expected_cardinal_t<element_type_t<Wide>>::value;
    }
  };

}
