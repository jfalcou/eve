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
    template<typename In, typename Out, std::ptrdiff_t I0, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I0,I...>, as_<In>, as_<Out>)  noexcept
    {
      std::ptrdiff_t c  = cardinal_v<In>;
      std::ptrdiff_t sz = cardinal_v<Out>;
      pattern_<I0,I...> p;

      // No slide of 1
      if(c==1 || sz ==1) return false;

      // We must starts with at least 1
      auto p0 = p(0,sz);
      if(p0 < 1) return false;

      // Valid pattern
      // [ k (k+1<N ? k+1 : -1) .. (k+sz-1<N ? k+sz-1 : -1) ]  1 <= k <= N-1
      int  i  = 1;
      while(i<sz && p(i,sz) != -1)
      {
        if(p(i,sz) != p0+i)  return false;
        i++;
      }

      if( i<sz && p(i,sz) == -1 )
      {
        // -1 means we ran out of original cardinal indexing
        if(p(i-1,sz) != c-1) return false;

        while( i<sz )
        {
          if(p(i,sz) != -1) return false;
          i++;
        }

        return true;
      }
      else
      {
        return true;
      }
    }
  };
}
