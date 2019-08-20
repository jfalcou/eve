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
  // Match any pattern of the form [k k ... k k]
  struct broadcast
  {
    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const& p, as_<Wide> const&)  noexcept
    {
      constexpr auto c = cardinal_v<Wide>;

      auto ref = p(0,c);
      for(int i=1;i<c;++i)
      {
        if(p(i,c) != ref)
          return false;
      }

      return true;
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(cpu_), broadcast const&
                                  , Pattern const& p, Wide const& v
                                  )
  {
    constexpr auto sz = Pattern::size(cardinal_v<Wide>);
    using that_t      = as_wide_t<Wide,fixed<sz>>;

    return that_t(v[p(0,cardinal_v<Wide>)]);
  }
}
