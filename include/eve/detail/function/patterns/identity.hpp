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
#include <eve/detail/swizzle.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/element_type.hpp>

#include <cstddef>

namespace eve::detail
{
  // Match any pattern of the form [0 1 2 ... N-1]
  struct identity
  {
    template<typename Pattern, typename Wide>
    static constexpr auto check(Pattern const& p, as_<Wide> const&)  noexcept
    {
      constexpr auto c = cardinal_v<Wide>;
      if(c > expected_cardinal_t<element_type_t<Wide>>::value) return false;

      for(int i=0;i<c;++i)
      {
        if(p(i,c) != i && p(i,c) != -1)
          return false;
      }

      return true;
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(cpu_), identity const&
                                  , Pattern const& p, Wide const& v
                                  )
  {
    constexpr auto sz = Pattern::size(cardinal_v<Wide>);
    using that_t      = as_wide_t<Wide,fixed<sz>>;

    if constexpr(sz >= cardinal_v<Wide>)
    {
      return process_zeros(that_t(v.storage()),p);
    }
    else if constexpr(cardinal_v<Wide>/sz == 2)
    {
      return process_zeros(that_t(v.slice(lower_).storage()),p);
    }
    else
    {
      return do_swizzle(EVE_RETARGET(cpu_), identity{}, p, v.slice(lower_));
    }
  }
}
