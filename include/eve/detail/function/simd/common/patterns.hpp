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

#include <eve/traits/cardinal.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/pattern.hpp>
#include <ostream>

namespace eve::detail
{
  //================================================================================================
  // Detects <-1,...,-1> as zeroing
  template<int... I> inline constexpr bool is_zero = ((I == na_) && ...);

  //================================================================================================
  // Detects <0,1,...,N-1> as identity
  template<int... I> inline constexpr bool is_identity = []()
  {
    int   idx[] = {I...};
    int   c     = sizeof...(I);
    bool ok     = true;

    for(int i=0;i<c;++i) ok = ok && (idx[i]==i);

    return ok;
  }();

  //================================================================================================
  // Local silly helper that doesn't warrant an actual functor
  //================================================================================================
  struct identity_swizzle
  {
    friend std::ostream& operator<<(std::ostream& os, identity_swizzle)
    {
      return os << "identity_swizzle";
    }

    template<typename Wide, typename Cardinal>
    EVE_FORCEINLINE auto operator()(Wide v, Cardinal) const
    {
      constexpr auto cd = cardinal_v<Wide>;
      constexpr auto sz = Cardinal::value;
      using that_t      = as_wide_t<Wide,Cardinal>;

            if constexpr(sz     >= cd ) return that_t(v.storage());
      else  if constexpr(cd/sz  == 2  ) return that_t(v.slice(lower_).storage());
      else                              return v.slice(lower_)[p];
    }
  };

  struct zero_swizzle
  {
    friend std::ostream& operator<<(std::ostream& os, zero_swizzle)
    {
      return os << "zero_swizzle";
    }

    template<typename Wide, typename Cardinal>
    EVE_FORCEINLINE auto operator()(Wide, Cardinal) const
    {
      return as_wide_t<Wide,Cardinal>{0};
    }
  };
}
