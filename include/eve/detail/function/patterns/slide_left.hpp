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
  //
  //  [ a b c d ] : sz elements taken from wide of N cardinal
  //
  //  [ k (k+1<N ? k+1 : -1) .. (k+sz-1<N ? k+sz-1 : -1) ]  1 <= k <= N-1
  //
  //================================================================================================
  struct slide_left
  {
    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      constexpr std::ptrdiff_t c  = cardinal_v<In>;
      constexpr std::ptrdiff_t sz = cardinal_v<Out>;
      constexpr pattern_<I...> p;

      if(c==1) return false;

      // Valid pattern
      // [ k (k+1<N ? k+1 : -1) .. (k+sz-1<N ? k+sz-1 : -1) ]  1 <= k <= N-1
      auto p0 = p(0,c);

      // We must starts with at least 1
      if(p0 < 1) return false;

      int  i  = 1;
      while(i<sz && p(i,c) != -1)
      {
        auto q = p(i,c);
        if(q != p0+i)  return false;
        i++;
      }
      if(i != sz)
      {
        if(c ==sz)
        {
          while( i<sz )
          {
            auto q = p(i,c);
            if(q!=-1) return false;
            i++;
          }
        }
        else
        {
          return false;
        }
      }

      return true;
    }
  };
}
