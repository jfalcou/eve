//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/patterns.hpp>

#include <cstddef>

namespace eve::detail
{
  // Match any pattern of the form [-1 -1 ... -1 -1]
  struct zeroing
  {
    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const& p, as_<Wide> const&)  noexcept
    {
      constexpr auto c = cardinal_v<Wide>;

      for(int i=0;i<c;++i)
      {
        if(p(i,c) != -1)
          return false;
      }

      return true;
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(cpu_), zeroing const&
                                  , Pattern const&, Wide const&
                                  )
  {
    return as_wide_t<Wide,fixed<Pattern::size(cardinal_v<Wide>)>>(0);
  }
}
