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
    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      constexpr std::ptrdiff_t c  = cardinal_v<In>;
      constexpr std::ptrdiff_t sz = cardinal_v<Out>;
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
