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
#include <ostream>

namespace eve::detail
{
  //================================================================================================
  // Helpers for detecting patterns
  //================================================================================================

  // Detects <N,...,N> as a broadcast
  template<int I0, int... I> inline constexpr bool is_broadcast = ((I0 !=-1) && ... && (I0==I));

  // Detects <-1,...,-1> as zeroing
  template<int... I> inline constexpr bool is_zero = ((I==-1) && ...);

  // Detects <0,1,...,N-1> as identity
  template<int... I> inline constexpr bool is_identity = []()
  {
    int idx[] = {I...};
    bool ok = true;
    for(int i=0;i<sizeof...(I);++i) ok = ok && (idx[i]==i);
    return ok;
  }();

  //================================================================================================
  // Local silly helper that doesn't warrant an actual functor
  //================================================================================================
  struct perform_identity
  {
    friend std::ostream& operator<<(std::ostream& os, perform_identity)
    {
      return os << "eve::perform_identity";
    }

    template<typename Wide, typename Pattern>
    EVE_FORCEINLINE auto operator()(Wide v, Pattern p) const
    {
      constexpr auto cd = cardinal_v<Wide>;
      constexpr auto sz = Pattern::size(cd);
      using that_t      = as_wide_t<Wide,fixed<sz>>;

            if constexpr(sz     >= cd ) return that_t(v.storage());
      else  if constexpr(cd/sz  == 2  ) return that_t(v.slice(lower_).storage());
      else                              return v.slice(lower_)[p];
    }
  };
}
