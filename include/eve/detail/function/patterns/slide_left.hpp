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

#include <eve/detail/swizzle.hpp>
#include <eve/patterns.hpp>

namespace eve::detail
{
  //================================================================================================
  // Slide data left
  //================================================================================================
  struct slide_left
  {
    template<std::ptrdiff_t... I>
    static constexpr auto find_slide(pattern_<I...> const& p)  noexcept
    {
      std::ptrdiff_t c = sizeof...(I);
      std::ptrdiff_t i = c-1;

      while(p(i,c)==-1 && i>0) i--;

      return i;
    }

    template<typename Wide, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...> const& p, as_<Wide> const&)  noexcept
    {
      constexpr std::ptrdiff_t c = cardinal_v<Wide>;
      if(c==1) return false;

      // Find where the -1 streak ends
      std::ptrdiff_t i = find_slide(p), res = i;
      std::ptrdiff_t d = c-1;

      // Check we have partial identity afterward
      for(;i>=0;--i)
        if( p(i,c) != d+(i-res))
          return false;

      return c <= expected_cardinal_t<element_type_t<Wide>>::value;
    }
  };
}
