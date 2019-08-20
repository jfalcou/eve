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

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Slide data right
  //------------------------------------------------------------------------------------------------
  struct slide_right
  {
    template<typename F, int Size>
    static constexpr auto find_slide(swizzler_t<F,Size> const& p, int c)  noexcept
    {
      int i = 0;
      while(p(i,c)==-1 && i<c) i++;
      return i;
    }

    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const& p, as_<Wide> const&)  noexcept
    {
      constexpr auto c = cardinal_v<Wide>;

      // Find where the -1 streak ends
      int i = find_slide(p,c), res = i;

      // Check we have partial identity afterward
      for(;i<c;++i)
        if( p(i,c) != i-res)
          return false;

      return c <= expected_cardinal_t<element_type_t<Wide>>::value;
    }
  };

}
