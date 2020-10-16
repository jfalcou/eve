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
    template<typename Wide, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<Wide> const&)  noexcept
    {
      constexpr std::ptrdiff_t c  = cardinal_v<Wide>;
      constexpr std::ptrdiff_t sz = pattern_<I...>::size(c);
      constexpr pattern_<I...> p;

      if(c==1) return false;

      // Consume consecutive -1
      int i = 0;
      while(i<sz && p(i,c)==-1)
      {
        i++;
      }

      // Check for partial identity
      int j = 0;
      while( i<sz )
      {
        auto q = p(i,c);
        if(q!=j) return false;
        i++;
        j++;
      }

      return true;
    }
  };
}
